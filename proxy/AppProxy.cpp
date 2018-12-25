/*
 * AppProxy.cpp
 *
 *  Created on: Sep 26, 2014
 *      Author: root
 */

#include "AppProxy.h"
#include "shm/MemStorage.h"
#include "AppProxyInitException.h"

#include <iostream>
#include <string>
#include <sys/prctl.h>
#include <sys/signal.h>

//TODO: Guarantee every item in constructor cause no leak if construction failed in between
//While even if it failed, it has nothing to do with collector
AppProxy::AppProxy(int appId): myAppId(appId),
					myTid(MemStorage::GetInstance().getNewTid()),
					cmmQ(MemStorage::GetInstance().allocCmmQueue(myTid)),
					blocks(MemStorage::GetInstance().getBlocks()),
//					myTransitCell(MemStorage::GetInstance().allocTransitMemCell(myTid)),
					memPool(myTid, MemStorage::GetInstance().getCells(),
							MemStorage::GetInstance().allocTransitMemCell(myTid), BLOCKSIZE / 2)
{
	if(!MemStorage::GetInstance().registerApp(myAppId, cmmQ.getMyIndex(), myTid))
	{
		throw AppProxyInitException("Failed to register ");
	}

	if(prctl(PR_SET_PDEATHSIG, SIGHUP))
	{
		cout << "Failed to bind child process with monitor " << endl;
	}
}

//TODO: Ensure nothing to be released actively
AppProxy::~AppProxy()
{
}

void* AppProxy::cellId2Data(int cellId)
{
	if(!GlobalConfig::IsValidCell(cellId))
	{
		cout << "Invalid cellId " << cellId << endl;
		return NULL;
	}else
	{
		return (void*)(blocks[cellId].data);
	}
}

int AppProxy::data2CellId(void* data)
{
	if(data < blocks || data >= (blocks + sizeof(MemBlock) * TOTALBLOCKSIZE))
	{
		return INVALIDCELL;
	}
	MemBlock* block = static_cast<MemBlock*>((void*)((unsigned char*)data - BLOCKHEADLEN));
	if(block == NULL)
	{
		return INVALIDCELL;
	}else if(block->magicNum != BLOCKMAGICNUM)
	{
		return INVALIDCELL;
	}else
	{
		return block->getMyIndex();
	}
}

void* AppProxy::allocMem()
{
	int cellId = INVALIDCELL;
	if(memPool.alloc(cellId))
	{
//		cout << "alloc cellId " << cellId << endl;
		return cellId2Data(cellId);
	}else
	{
		return NULL;
	}
}

bool AppProxy::releaseMem(void* mem)
{
	int cellId = data2CellId(mem);
	if(GlobalConfig::IsValidCell(cellId))
	{
		return memPool.free(cellId);
	}else
	{
		return false;
	}
}

bool AppProxy::send(void* mem, int dstAppId)
{
	int cellId = data2CellId(mem);
	if(!GlobalConfig::IsValidCell(cellId))
	{
		cout << "Invalid cell " << cellId << endl;
		return false;
	}
//	cout << "----------------> To push cellId " << cellId << endl;
	//TODO: Assert liveness of dstTid and a routing system
	return MemStorage::GetInstance().sendMsg(cellId, dstAppId);
}

void* AppProxy::recv()
{
	uint cellId = INVALIDCELL;
	if(cmmQ.pop(cellId))
	{
		return cellId2Data(cellId);
	}else
	{
		return NULL;
	}
}
