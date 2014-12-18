/*
 * GlobalFreeList.h
 *
 *  Created on: Sep 7, 2014
 *      Author: root
 */

#ifndef GLOBALFREELIST_H_
#define GLOBALFREELIST_H_

#include "GlobalConfig.h"

#ifdef OLDCPP
#include <cstdatomic>
#else
#include <atomic>
#endif

#include <climits>

class GlobalFreeList
{
friend class MemWrapper;
friend class MemStorage; //For debug

private:
//	CellBlock blocks[GLOBALBLOCKSIZE]; //Should be moved into global storage
	atomic_ulong freeList[GLOBALFREELISTSIZE]; //TODO: SHould be volatile?
	//TODO: Confirm the atomic primitive operator"=" equals operator "load()"
	atomic_uint caches[CACHESIZE];
//	int availList[GLOBALBLOCKSIZE];
	//TODO: Add tmp result for local list

//	uint availListHead;
//	uint availListTail;

	//Would it be better by barrier?
	//head to block that is being filled in
	atomic_uint freeListTail;
	atomic_uint freeListHead;
	static __thread uint userId;

//	Cell * const cells;

	const static uint PushExp = FREECELL;
	bool init();

//	int currCellIndex;

public:
	GlobalFreeList();
	~GlobalFreeList();

	bool push(volatile ulong& cellId);
	bool pop(volatile ulong& cellId);


	bool contains(const int cellId);
	bool containsInDetail(const int cellId);

	GlobalFreeList(const GlobalFreeList& copied) = delete;
	GlobalFreeList& operator=(const GlobalFreeList& copied) = delete;
};

#endif /* GLOBALFREELIST_H_ */
