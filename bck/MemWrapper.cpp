/*
 * MemWrapper.cpp
 *
 *  Created on: Sep 11, 2014
 *      Author: root
 */

#include "MemWrapper.h"

MemWrapper* MemWrapper::inst = NULL;

MemWrapper::MemWrapper(bool toCreate): toCreate(toCreate), shmStore(NULL), memStore(NULL), qs(NULL)
{
	init(toCreate);


	cells = memStore->cells;
	blocks = memStore->blocks;
	qs = memStore->qs;
}

MemWrapper::~MemWrapper()
{
	if(toCreate)
	{
		memStore->MemStorage::~MemStorage();
		delete memStore;
		memStore = NULL;

		delete shmStore;
		shmStore = NULL;
	}
	//TODO: else
}

void MemWrapper::init(bool toCreate)
{
	//TODO: unmap or unlink in destruction of ShmStore
	shmStore = new ShmStore(sizeof(MemStorage), MemStorage::ShmName, toCreate);

	if(!shmStore->init())
	{
		throw MemInitException("Failed to deal with SHM \n");
	}

	void* shmPtr = shmStore->getShmPtr();

	if(!toCreate)
	{
		memStore = static_cast<MemStorage*>(shmPtr);
	}else
	{
		memStore = new(shmPtr)MemStorage();
	}
}

//MemWrapper& MemWrapper::GetInstance()
//{
//	static MemWrapper instance;
//
//	return instance;
//}

int MemWrapper::GetInitSeqNum()
{
	static atomic_int seqNum(0);
	return seqNum.fetch_add(1);
}

int MemWrapper::GetNewTid()
{
	static atomic_int tid;

	int newTid = tid.fetch_add(1);

	while(newTid == FREETID || newTid == INVALIDTID)
	{
		newTid = tid.fetch_add(1);
	}
	return newTid;
}

MemWrapper* MemWrapper::GetInstance()
{
	return inst;
}

void MemWrapper::InitInstance(bool toCreate)
{
	inst = new MemWrapper(true);
}

void MemWrapper::InitInstance()
{
	inst = new MemWrapper(false);
}
