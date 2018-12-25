/*
 * AppProxy.h
 *
 *  Created on: Sep 26, 2014
 *      Author: root
 */

#ifndef APPPROXY_H_
#define APPPROXY_H_

//TODO: hide these definition in .h to application user

#include "freelist/LocalFreeList.h"
#include "comm/CmmQueue.h"
#include "shm/MemStorage.h"
#include <map>

using namespace std;

class AppProxy
{
public:
	const int myAppId;
	const uint myTid;

private:
	CmmQueue& cmmQ;
	MemBlock *blocks;
//	TransitMemData& myTransitCell;
	LocalFreeList memPool;
//	Cell *cells;

	void* cellId2Data(int cellId);
	int data2CellId(void* data);

public:
	AppProxy(int appId);
	virtual ~AppProxy();

	void* allocMem();
	bool releaseMem(void* mem);

	bool send(void* mem, int dstAppId);
	void* recv();
};

#endif /* APPPROXY_H_ */
