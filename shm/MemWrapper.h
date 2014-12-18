/*
 * MemWrapper.h
 *
 *  Created on: Sep 11, 2014
 *      Author: root
 */

#ifndef MEMWRAPPER_H_
#define MEMWRAPPER_H_

#include "ShmStore.h"
#include "MemStorage.h"

class MemWrapper
{
private:
	const bool toCreate;
	ShmStore* shmStore;
	Cell * const cells;
	MemBlock *const blocks;

	void init(bool toCreate);

//	MemWrapper();
	~MemWrapper();
	MemWrapper(bool toCreate);
	MemStorage* memStore;
	CmmQueue* qs;

	static MemWrapper* inst;


protected:
	static void InitInstance(bool toCreate);
	inline CmmQueue * const getCmmQs() { return qs; }

public:

	MemWrapper(const MemWrapper& copied) = delete;
	MemWrapper& operator=(const MemWrapper& copied) = delete;

	static void InitInstance();
	static MemWrapper* GetInstance();

	inline Cell *getCells() { return cells;}
	inline MemBlock * const getBlocks() { return blocks; }

	static int GetInitSeqNum();
	static int GetNewTid();

	inline bool release(int &cellId) { return memStore->freeList.push(cellId);};
	inline bool alloc(int cellId) {return memStore->freeList.pop(cellId);};
};
#endif /* MEMWRAPPER_H_ */
