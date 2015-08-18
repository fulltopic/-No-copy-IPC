/*
 * MemStorage.cpp
 *
 *  Created on: Sep 8, 2014
 *      Author: root
 */

#include "MemStorage.h"
#include <string.h>
#include <unistd.h>
#include <iostream>

using namespace std;

const string MemStorage::ShmName = "MEMSTORESHM";

MemBlock::MemBlock(): myIndex(-1), magicNum(BLOCKMAGICNUM)
{
	memset(data, 0, sizeof(CELLLEN));
}

MemStorage::MemStorage(): tidSeq(1), shmStore(NULL)
{
	// TODO Auto-generated constructor stub
	for(int i = 0; i < TOTALBLOCKSIZE; i ++)
	{
		cells[i].init(i);
	}
	for(int i = 0; i < TOTALBLOCKSIZE; i ++)
	{
		blocks[i].setMyIndex(i);
	}
	for(int i = 0; i < GLOBALAPPSIZE; i ++)
	{
		appIdInfoMap[i].appId = INVALIDAPPID;
		appIdInfoMap[i].pid = 0;
		appIdInfoMap[i].qId = -1;
		appIdInfoMap[i].tid = INVALIDTID;
	}

	for(int i = 0; i < GLOBALQUESIZE; i ++)
	{
		qs[i].myIndex = i;
		qFreeList.pushSingle(i);
	}

	for(int i = 0; i < GLOBALLOCALINDXNUM; i ++)
	{
		transitCellsFreeList.pushSingle(i);
	}

	for(int i = 0; i < SUSPECTALLOCTIDSNUM; i ++)
	{
		suspectAllocCellIds[i] = INVALIDCELL;
		suspectAllocTids[i] = FREETID;
	}
}

MemStorage::~MemStorage()
{
	delete shmStore;
	shmStore = NULL;
}

//Suppose monitor initialize in single thread
int MemStorage::GetInitSeqNum()
{
	static int seqNum(0);
	return seqNum ++;
}

uint MemStorage::getNewTid()
{
	uint newTid = tidSeq.fetch_add(1);

	while(newTid == FREETID || newTid == INVALIDTID)
	{
		newTid = (tidSeq.fetch_add(1)) & TIDMASK;
	}

	cout << "---------------> For new tid " << newTid << endl;
	return newTid;
}

//TODO: More effective
MemStorage* MemStorage::GenerateInst(bool toCreate)
{
	ShmStore* mem = new ShmStore(sizeof(MemStorage), MemStorage::ShmName, toCreate);
	MemStorage* inst = NULL;

	if(toCreate)
	{
		inst = new(mem->shmPtr)MemStorage();
	}else
	{
		inst = static_cast<MemStorage*>(mem->shmPtr);
		if(inst == NULL)
		{
			throw MemInitException("Failed to cast mem into object \n");
		}
	}

	inst->setShmStore(mem);

	return inst;
}

MemStorage& MemStorage::GetInstance(bool)
{
//	static MemStorage(new(shmPtr)MemStorage())
	static MemStorage* memStore = GenerateInst(true);
	return *memStore;
}

MemStorage& MemStorage::GetInstance()
{
	static MemStorage* memStore = GenerateInst(false);
	return *memStore;
}

void* MemStorage::operator new(size_t, void* loc)
{
	return loc;
}

void MemStorage::operator delete(void*, void* )
{
	//Do nothing
}

bool MemStorage::isInAllocTransit(int cellId) const
{
	if(!GlobalConfig::IsValidCell(cellId))
	{
		return false;
	}
	for(int i = 0; i < (int)(sizeof(transitCells) / sizeof(TransitMemData));i ++)
	{
		if(transitCells[i].toAlocCellId == (ulong)cellId)
		{
			return true;
		}
	}

	return false;
}

bool MemStorage::isInRelTransit(int cellId) const
{
	if(!GlobalConfig::IsValidCell(cellId))
	{
		return false;
	}
	for(int i = 0; i < (int)(sizeof(transitCells) / sizeof(TransitMemData));i ++)
	{
		if(transitCells[i].toDelCellId == (ulong)cellId)
		{
			return true;
		}
	}

	return false;
}

bool MemStorage::isInDetailAllocTransit(int cellId) const
{
//	Cell *cells = MemStorage::GetInstance().getCells();

	if(!GlobalConfig::IsValidCell(cellId))
	{
		return false;
	}
	for(int i = 0; i < (int)(sizeof(transitCells) / sizeof(TransitMemData));i ++)
	{
		int blockCellIndex = GlobalConfig::GetFreeListCellIndex(transitCells[i].toAlocCellId);
		if(blockCellIndex == cellId)
		{
			return true;
		}else
		{
			for(int j = 0; j < SIBLINGSIZE; j ++)
			{
				if(cells[blockCellIndex].siblings[j] == cellId)
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool MemStorage::isFlying(uint dstTid, int cellId) const
{
	for(int i = 0; i < GLOBALQUESIZE; i ++)
	{
		if(qs[i].getMyTid() == dstTid)
		{
			//May have > 1 queue with same tid
			if(qs[i].contains(cellId))
			{
				return true;
			}
		}
	}

	return false;
}

//TODO: It's not OK. To replaced by some list
CmmQueue& MemStorage::allocCmmQueue(const uint myTid) throw(CmmQAlocException, exception)
{
//	uint exp = FREETID;
//	for(int i = 0; i < GLOBALQUESIZE; i ++)
//	{
//		if(qs[i].myTid == exp)
//		{
//			if(qs[i].myTid.compare_exchange_strong(exp, myTid))
//			{
//				cout << "Get free queue " << i << " for " << myTid << endl;
//				return qs[i];
//			}else
//			{
//				exp = FREETID;
//			}
//		}
//	}

	uint qUIndex = UINT_MAX;
	if(qFreeList.popMul(qUIndex))
	{
		int qIndex = (int)qUIndex;

		if(qs[qIndex].myTid != FREETID)
		{
			cout << "Fatal error " << endl;
			abort();
		}

		qs[qIndex].myTid.store(myTid);
		cout << "Get free queue " << (int)qIndex << " for " << myTid << endl;
		return qs[qIndex];
	}


//	abort();
	cout << "Current queue status " << endl;
	for(int i = 0; i < GLOBALQUESIZE; i ++)
	{
		cout << "qs[" << i << "] = " << qs[i].myTid << endl;
	}

	throw CmmQAlocException();
}

TransitMemData& MemStorage::allocTransitMemCell(uint myTid) throw(TransitDataAllocException, exception)
{
//	uint exp = FREETID;
//
//	for(int i = 0; i < GLOBALLOCALINDXNUM; i ++)
//	{
//		if(transitCells[i].myTid == exp)
//		{
//			if(transitCells[i].myTid.compare_exchange_strong(exp, myTid))
//			{
////				cout << "assign " << i << ":" << transitCells[i].toAlocCellId << endl;
//				return transitCells[i];
//			}
//		}
//	}
	uint tcUIndex = UINT_MAX;
	if(transitCellsFreeList.popMul(tcUIndex))
	{
		int tcIndex = (int)tcUIndex;
		if(transitCells[tcIndex].myTid != FREETID)
		{
			cout << "Fatal error " << endl;
			abort();
		}else
		{
			transitCells[tcIndex].myTid = myTid;
			cout << "Alloc transit cell " << tcIndex << " for " << myTid << endl;
		}

		return transitCells[tcIndex];
	}

	throw TransitDataAllocException();
}

//TODO: Unregister
bool MemStorage::registerApp(int appId, int cmmQId, uint tid)
{
	if(!GlobalConfig::IsValidAppId(appId))
	{
		cout << "Invalid app id " << appId << endl;
		return false;
	}

	if(appIdInfoMap[appId].appId != INVALIDAPPID)
	{
		cout << "The previous application had not been cleaned up" << endl;
		return false;
	}
	if(!(GlobalConfig::IsValidQId(cmmQId))
		|| GlobalConfig::IsValidQId(appIdInfoMap[appId].qId))
	{
		cout << "Invalid qId " << cmmQId << ", " << appIdInfoMap[appId].qId << endl;
		return false;
	}
	//TODO: Check original pid dead
	pid_t myPid = getpid();
	appIdInfoMap[appId].qId = cmmQId;
	appIdInfoMap[appId].pid = myPid;
	appIdInfoMap[appId].tid = tid;
	appIdInfoMap[appId].appId = appId;

	return true;
}

bool MemStorage::unregisterApp(int appId)
{
	if(!GlobalConfig::IsValidAppId(appId))
	{
		return false;
	}

	appIdInfoMap[appId].qId = -1;
	appIdInfoMap[appId].pid = 0;
	appIdInfoMap[appId].tid = INVALIDTID;
	appIdInfoMap[appId].appId = INVALIDAPPID;

	return true;
}

bool MemStorage::getQIdByAppId(int appId, int& cmmQId)
{
	if(GlobalConfig::IsValidAppId(appId))
	{
		cmmQId = appIdInfoMap[appId].qId;
//		cout << "Get qid " << cmmQId << " for " << appId << endl;
		if(GlobalConfig::IsValidQId(cmmQId))
		{
			return true;
		}
	}

	return false;
}

void MemStorage::stopCmmQRcv(const int appId)
{
	if(GlobalConfig::IsValidAppId(appId))
	{
		appIdInfoMap[appId].qId = INVALIDQID;
	}
}

void MemStorage::clearTransitCell(const uint tid)
{
	cout << "========================> Cleared " << tid << endl;
	for(int i = 0; i < GLOBALLOCALINDXNUM; i ++)
	{
		if(transitCells[i].myTid == tid)
		{
			transitCells[i].toAlocCellId = INVALIDCELL;
			transitCells[i].toDelCellId = INVALIDCELL;
			transitCells[i].myTid = FREETID;
			return;
		}
	}

	return;
}

void MemStorage::clearCmmQ(const uint tid)
{
	for(int i = 0; i < GLOBALQUESIZE; i ++)
	{
		if(qs[i].myTid == tid)
		{
			qs[i].head = 0;
			qs[i].tail = 0;
			qs[i].myTid = INVALIDTID;
			return;
		}
	}

	return;
}


int MemStorage::findAppIdByTid(const uint tid)
{
	for(int appId = 0; appId < GLOBALAPPNUM; appId ++)
	{
		if(appIdInfoMap[appId].tid == tid)
		{
			return appId;
		}
	}

	return INVALIDAPPID;
}

int MemStorage::findTcIndexByTid(const uint tid)
{
	for(int i = 0; i < GLOBALLOCALINDXNUM; i ++)
	{
		if(transitCells[i].myTid == tid)
		{
			return i;
		}
	}

	return UINT_MAX;
}

//void MemStorage::clearAppResource(const int appId)
void MemStorage::clearAppResource(const uint tid)
{
	int appId = findAppIdByTid(tid);
	if(!GlobalConfig::IsValidAppId(appId))
	{
		return;
	}

//	stopCmmQRcv(appId);
//
	int qId = appIdInfoMap[appId].qId;
	int tcIndex = findTcIndexByTid(tid);

	clearTransitCell(tid);
	clearCmmQ(tid);

	unregisterApp(appId);

	if(!qFreeList.pushMul((uint)qId))
	{
		cout << "Fatal error " << endl;
		abort();
	}
	if(GlobalConfig::IsValidTCIndex(tcIndex))
	{
		if(!transitCellsFreeList.pushMul((uint)tcIndex))
		{
			cout << "Fatal error " << endl;
			abort();
		}
	}else
	{
		abort();
	}

	return;
}

bool MemStorage::getTransitCell(uint tid, uint& toDelCellId, uint& toAlocCellId)
{
	for(int i = 0; i < GLOBALLOCALINDXNUM; i ++)
	{
		if(transitCells[i].myTid == tid)
		{
			toDelCellId = transitCells[i].toDelCellId;
			toAlocCellId = transitCells[i].toAlocCellId;
			cout << "===========> Get " << i << ":" << transitCells[i].toAlocCellId << endl;

			return true;
		}
	}

	return false;

}

bool MemStorage::sendMsg(const int cellId, const int dstAppId)
{
	int dstQId = INVALIDCELL;
	if(getQIdByAppId(dstAppId, dstQId))
	{
//		cout << "Get Qid " << dstQId << endl;
		return qs[dstQId].push(cellId);
	}else
	{
		cout << "Failed to get destination queue " << dstAppId << endl;
		return false;
	}
}

bool MemStorage::findTidByPid(pid_t pid, uint& tid)
{
	for(int i = 0; i < GLOBALAPPSIZE; i ++)
	{
		if(appIdInfoMap[i].pid == pid)
		{
			tid = appIdInfoMap[i].tid;
			return true;
		}
	}

	return false;
}

bool MemStorage::putSuspectAllocCell(const uint cellId, const uint tid)
{
	for(int i = 0; i < SUSPECTALLOCTIDSNUM; i ++)
	{
		if(suspectAllocCellIds[i] == INVALIDCELL)
		{
			suspectAllocCellIds[i] = cellId;
			suspectAllocTids[i] = tid;
			return true;
		}
	}

	fprintf(stderr, "No space for suspect alloc tid \n");
	return false;
}
uint MemStorage::getSuspectAllocCell(const uint tid)
{
	for(int i = 0; i < SUSPECTALLOCTIDSNUM; i ++)
	{
		if(suspectAllocTids[i] == tid)
		{
			uint rcCellId = suspectAllocCellIds[i];
			suspectAllocTids[i] = FREETID;
			suspectAllocCellIds[i] = INVALIDCELL;
			return rcCellId;
		}
	}

	fprintf(stderr, "No suspect cell bound to the tid %u \n", tid);
	return INVALIDCELL;
}

//TODO: To convert protected child element print into << function
void MemStorage::printCells()
{
	cout << "=========================> All cells " << endl;
	for(int i = 0; i < TOTALBLOCKSIZE; i ++)
	{
		cout << cells[i].myIndex << ":" << cells[i].myTid
				<< ":" << cells[i].dstTid
				<< ":";
		for(int j = 0; j < SIBLINGSIZE; j ++)
		{
			cout << cells[i].siblings[j] << ",";
		}
		cout << endl;
	}
}

void MemStorage::printTransitCells()
{
	cout << "===========================> All transit cells " << endl;
	for(int i = 0; i < GLOBALLOCALINDXNUM; i ++)
	{
		cout << transitCells[i].myTid << ":"
				<< transitCells[i].toAlocCellId << ":"
				<< transitCells[i].toDelCellId
				<< endl;
	}
	cout << "============================> End of transit cells " << endl;
}

void MemStorage::printGlobalFreeList()
{
	cout << "=========================> All slots in global frees list" << endl;
	cout << "head = " << freeList.freeListHead << " tail = " << freeList.freeListTail << endl;
	for(int i = 0; i < GLOBALFREELISTSIZE; i ++)
	{
		cout << i << ":" << (freeList.freeList[i] & DATAMASK) << endl;
	}
}
