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
#include <vector>

class GlobalFreeList
{
friend class MemWrapper;
friend class MemStorage; //For debug

private:
	atomic_ulong freeList[GLOBALFREELISTSIZE];

	//TODO: Make use of cashes
	atomic_uint caches[CACHESIZE];
//	int availList[GLOBALBLOCKSIZE];

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

	bool push(volatile uint& cellId);
	bool pop(volatile uint& cellId);


	bool contains(const int cellId);
	bool containsInDetail(const int cellId);

	GlobalFreeList(const GlobalFreeList& copied) = delete;
	GlobalFreeList& operator=(const GlobalFreeList& copied) = delete;

	bool checkList4Dup(std::vector<bool>& checkList);
	bool checkList4Miss(std::vector<bool>& checkList);
	bool checkNoDupInList();
	bool checkNoMissInList();
	bool checkNoDup();
	bool checkNoMiss();
};

#endif /* GLOBALFREELIST_H_ */
