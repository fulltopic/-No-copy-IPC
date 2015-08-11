/*
 * LocalFreeList.h
 *
 *  Created on: Sep 7, 2014
 *      Author: root
 */

#ifndef LOCALFREELIST_H_
#define LOCALFREELIST_H_

#include "Cell.h"
#include "GlobalConfig.h"

class LocalFreeList
{
private:
	int blocks[BLOCKSIZE];
//	const uint capacity;
	const int myTid; //To move into thread local storage
//	GlobalFreeList& globalFreeList;
	Cell * const cells;

	//Should they be atomic variables?
	volatile uint& toDelCellId;
	volatile uint& toAllocCellId;

	int32_t blocksIndex;
	int32_t sibIndex;

	bool init(int initBlocks);
	bool fetch();
	bool release();

public:
	LocalFreeList(uint tid, Cell *myCells, volatile uint& delCellId, volatile uint& allocCellId);
	LocalFreeList(uint tid, Cell *myCells, volatile uint& delCellId, volatile uint& allocCellId, int initBlocks);
	~LocalFreeList();
	LocalFreeList(const LocalFreeList& copied) = delete;
	LocalFreeList& operator=(const LocalFreeList& copied) = delete;

	bool alloc(int& cellId);
	bool free(int cellId);

	inline int getTid() const { return myTid; }
};

#endif /* LOCALFREELIST_H_ */
