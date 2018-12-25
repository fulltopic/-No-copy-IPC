/*
 * MemStorage.h
 *
 *  Created on: Sep 8, 2014
 *      Author: root
 */

#ifndef MEMSTORAGE_H_
#define MEMSTORAGE_H_

#include "utils/ShmStore.h"
#include "GlobalConfig.h"
#include "Cell.h"
#include "freelist/CellBlock.h"
#include "freelist/GlobalFreeList.h"
#include "CmmQAlocException.h"
#include "comm/CmmQueue.h"
#include "TransitDataAllocException.h"
#include "freelist/SimpleFreeList.h"

#include <sys/types.h>

struct MemBlock
{
friend class MemStorage;

private:
	int myIndex;
	void setMyIndex(int index) { myIndex = index;}

public:
	const int magicNum;
	unsigned char data[CELLLEN];
	MemBlock();
	inline int getMyIndex() { return myIndex;}
};


struct AppInfo
{
	int appId;
	uint tid;
	pid_t pid;
	int qId;
};

//TODO: Make shmstore as a tool instead of parent. So as to construct globalStorage on the shmptr
class MemStorage
{
friend class CmmQueue;
friend class GlobalFreeList;
friend class Monitor;
friend class FreeListChecker;

private:
	Cell cells[TOTALBLOCKSIZE];
	GlobalFreeList freeList;
	CmmQueue qs[GLOBALQUESIZE];
	SimpleFreeList<GLOBALQUESIZE> qFreeList;

	TransitMemData transitCells[GLOBALLOCALINDXNUM];
	SimpleFreeList<GLOBALLOCALINDXNUM> transitCellsFreeList;
	uint suspectAllocCellIds[SUSPECTALLOCTIDSNUM];
	uint suspectAllocTids[SUSPECTALLOCTIDSNUM];

	MemBlock blocks[TOTALBLOCKSIZE];

	AppInfo appIdInfoMap[GLOBALAPPSIZE];
//	int appId2CmmQMap[GLOBALAPPSIZE];
//	pid_t appId2Pid[GLOBALAPPSIZE];

	atomic_uint tidSeq;
	ShmStore* shmStore;

	inline void setShmStore(ShmStore* mem) {shmStore = mem; };

	void clearTransitCell(const uint tid);
	void clearCmmQ(const uint tid);

	void stopCmmQRcv(const int appId);
	int findAppIdByTid(const uint tid);
	int findTcIndexByTid(const uint tid);

	bool putSuspectAllocCell(const uint cellId, const uint tid);
	uint getSuspectAllocCell(const uint tid);

public:
//	atomic_short GlobalTid; //TODO: What's this for?
	MemStorage(const MemStorage& copied) = delete;
	MemStorage& operator=(const MemStorage& copied) = delete;

	static const string ShmName;// = "MEMSTORESHM";

	//TODO: Exception expected
	CmmQueue& allocCmmQueue(const uint myTid) throw(CmmQAlocException, exception);
	bool releaseCmmQueue(CmmQueue& q);
	int getTmpRsId();

	TransitMemData& allocTransitMemCell(uint myTid) throw(TransitDataAllocException, exception);

	bool isInAllocTransit(int cellId) const;
	bool isInDetailAllocTransit(int cellId) const;
	bool isInRelTransit(int cellId) const;

	bool isFlying(uint dstTid, int cellId) const;

	bool registerApp(int appId, int cmmQId, uint tid);
	bool unregisterApp(int appId);

	bool getQIdByAppId(int appId, int& cmmQId);

//	static void InitInstance();
	inline bool release(volatile uint &cellId) { return freeList.push(cellId);};
	inline bool alloc(volatile uint& cellId) {return freeList.pop(cellId);};
//
	inline Cell *getCells() { return cells;}
	inline MemBlock *  getBlocks() { return blocks; }
	bool sendMsg(const int cellId, const int dstAppId);

	static MemStorage& GetInstance();
	static int GetInitSeqNum();
	uint getNewTid();

	static MemStorage* GenerateInst(bool toCreate);

	bool findTidByPid(pid_t pid, uint& tid);

	/**************************** DEBUG *****************************/
	 void printCells();
	 void printTransitCells();
	 void printGlobalFreeList();

	inline bool checkNoDup() {return freeList.checkNoDup();};
	inline bool checkNoMiss() {return freeList.checkNoMiss();};

protected:
	MemStorage();
	~MemStorage();

	void* operator new(size_t, void* loc);

	//TODO: Invoke the destruction in some proxy
	void operator delete(void*, void* loc);

	bool getTransitCell(uint tid, uint& toDelCellId, uint& toAlocCellId);
	inline CmmQueue* getQs() { return qs; }
	inline GlobalFreeList& getFreeList() { return freeList; }

	static MemStorage& GetInstance(bool);

//	void clearAppResource(const int appId);
	void clearAppResource(const uint tid);
};

#endif /* MEMSTORAGE_H_ */
