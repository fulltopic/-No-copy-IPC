/*
 * LocalFreeList.cpp
 *
 *  Created on: Sep 7, 2014
 *      Author: root
 */

#include "LocalFreeList.h"
#include "MemStorage.h"

#include "CrashPoints.h"

#include <iostream>
#include <string>

LocalFreeList::LocalFreeList(uint tid, Cell *myCells, volatile ulong& delCellId, volatile ulong& allocCellId)
	: myTid(tid),
	  cells(myCells),
	  toDelCellId(delCellId),
	  toAllocCellId(allocCellId),
	  blocksIndex(BLOCKSIZE - 1),
	  sibIndex(-2)
{

}

LocalFreeList::LocalFreeList(uint tid, Cell *myCells, volatile ulong& delCellId, volatile ulong& allocCellId, int initBlocks)
: myTid(tid),
  cells(myCells),
  toDelCellId(delCellId),
  toAllocCellId(allocCellId),
  blocksIndex(BLOCKSIZE - 1),
  sibIndex(-2)
{
	if(!init(initBlocks))
	{
		cout << "Failed to init memory blocks " << endl;
	}
	cout << "---------------------> Allocated localfreelist " << myTid << endl;
}

LocalFreeList::~LocalFreeList()
{
}

bool LocalFreeList::alloc(int& cellId)
{
//	if(sibIndex < 0)
//	{
//		blocksIndex ++;
//		sibIndex = SIBLINGSIZE - 1;
//	}
//
//	//TODO: To initial blocksIndex as BLOCKSIZE
//	if(blocksIndex >=BLOCKSIZE)
//	{
//		if(!fetch())
//		{
//			return false;
//		}
//	}
//
//	//TODOED:Suppose all allocated cells had been set FREE in release, so no CAS for cell's Tid;
//	int blockCellId = blocks[blocksIndex];
//	cellId = cells[blockCellId].siblings[sibIndex];
//
//	//TODOED: Corrupt between these 2 lines?
//	//TODOED: Should sibling be atomic_int to fetch_and_set? YES
//	cells[blockCellId].siblings[sibIndex] = INVALIDCELL;
//
//	sibIndex --;

	int blockCellId = INVALIDCELL;
	if(sibIndex < -1)
	{
		blocksIndex ++;

		if(blocksIndex >= BLOCKSIZE)
		{
			if(!fetch())
			{
				cout << "Failed to fetch " << endl;
				return false;
			}
		}else
		{
			sibIndex =  SIBLINGSIZE - 1;
			blockCellId = blocks[blocksIndex];

			while((uint)cells[blockCellId].siblings[sibIndex] == INVALIDCELL
					&& sibIndex >= 0)
			{
				sibIndex --;
			}
		}

	}
	blockCellId = blocks[blocksIndex];
//	cout << "blockIndex " << blocksIndex << " blockCellId " << blockCellId << " sibIndex " << sibIndex << endl;

	if(sibIndex == -1)
	{
		cellId = blockCellId;
		if(!GlobalConfig::IsValidCell(cellId))
		{
			cout << "Invalid cellId " << cellId << endl;
//			return NULL;
		}

	}else
	{
		//Exchange is not necessary as the index is in the APP.
		//If the monitor recycle block before cell, the individual cell can not be duplicated
//		cellId = cells[blockCellId].siblings[sibIndex].exchange(INVALIDCELL);
		cellId = cells[blockCellId].siblings[sibIndex];
		if(!GlobalConfig::IsValidCell(cellId))
		{
			cout << "Invalid cellId " << cellId << endl;
			return NULL;
		}
		cells[blockCellId].siblings[sibIndex] = INVALIDCELL;
	}
	sibIndex --;

//	cout << "Allocated mem " << cellId << "with tid " << cells[cellId].myTid << endl;

	return true;
}

//sibIndex refers to index that's readable
bool LocalFreeList::free(int cellId)
{
	sibIndex ++;
	if(sibIndex >= SIBLINGSIZE)
	{
		blocksIndex --;

		if(blocksIndex < 0)
		{
			if(!release())
			{
				return false;
			}
		}

		blocks[blocksIndex] = cellId;
	}else
	{
		//TODOED: Ensure that leaf cell has all siblings as INVALIDCELL
		int blockCellId = blocks[blocksIndex];
		cells[blockCellId].siblings[sibIndex] = cellId;
	}
	return true;
}

bool LocalFreeList::fetch()
{
//	cout << "To fetch for " << myTid << endl;
	//TODO: Check if toAllocCellId = INVALIDCELL automatically by global list allocation
	if(!MemStorage::GetInstance().alloc(toAllocCellId))
	{
		toAllocCellId = INVALIDCELL;
		return false;
	}

//	cout << "Get new bulk " << toAllocCellId << endl;
	int localBlockIndex = toAllocCellId & DATAMASK;
	blocks[BLOCKSIZE - 1] = localBlockIndex;
	toAllocCellId = INVALIDCELL;


	int num = 0;
	for(; num < SIBLINGSIZE; num ++)
	{
		int otherCellId = cells[localBlockIndex].siblings[num];
		if(otherCellId == (int)INVALIDCELL)
		{
			break;
		}
		cells[otherCellId].myTid.store(myTid);
	}
	//myTid had been set in GlobalFreeList.pop()
//	cells[localBlockIndex].myTid.store(myTid);

	//TODO: Ensure sibIndex >= 0;
	blocksIndex = BLOCKSIZE - 1;
	sibIndex = num - 1;

//	cout << "End of fetch " << toAllocCellId << endl;

	return true;
}

bool LocalFreeList::init(int initBlocks)
{
	cout << "Init free list " << initBlocks << " for tid " << myTid << endl;

	if(initBlocks > BLOCKSIZE)
	{
		initBlocks = BLOCKSIZE;
	}
//	initBlocks --;
	initBlocks = BLOCKSIZE - initBlocks;

//	for(int i = initBlocks; i >= 0; i --)
	for(int i = initBlocks; i < BLOCKSIZE; i ++)
	{
		toAllocCellId = INVALIDCELL;

		if(!MemStorage::GetInstance().alloc(toAllocCellId))
		{
			toAllocCellId = INVALIDCELL; //alloc returned. the tmp var could be reset
			return false;
		}

//		cout << "Get new bulk " << toAllocCellId << " for " << myTid << endl;
		blocks[i] = toAllocCellId;

		int num = 0;
		for(; num < SIBLINGSIZE; num ++)
		{
			int otherCellId = cells[toAllocCellId].siblings[num];
			if(otherCellId == (int)INVALIDCELL)
			{
				break;
			}
			cells[otherCellId].myTid.store(myTid);
//			cout << "-------------------------> Init cell " << otherCellId
//					<< " into " << myTid << ":" << cells[otherCellId].myTid << endl;
		}
		cells[toAllocCellId].myTid.store(myTid);
//		cout << "-------------------------> Init blockId" << toAllocCellId << endl;
//		cout << "Init fetch set " << cells[toAllocCellId].myTid << " to " << myTid << endl;

		toAllocCellId = INVALIDCELL;

		//TODO: Ensure sibIndex >= 0;
//		blocksIndex = blocksIndex = i;
		sibIndex = num - 1;
	}
	blocksIndex = initBlocks;

	return true;
}

bool LocalFreeList::release()
{
	if(!GlobalConfig::IsValidCell(blocks[0]))
	{
		abort();
	}

	//Dead point 1
	CrashPoints::GetInstance()->Crash(CrashPoints::GetInstance()->CrashInPoint21);

	toDelCellId = blocks[0];

	//Dead point 2
	CrashPoints::GetInstance()->Crash(CrashPoints::GetInstance()->CrashInPoint22);


	int num = 0;
	for(; num < SIBLINGSIZE; num ++)
	{
		int otherCellId = cells[toDelCellId].siblings[num];

		//Dead point 3
		CrashPoints::GetInstance()->Crash(CrashPoints::GetInstance()->CrashInPoint23);
		if(otherCellId == (int)INVALIDCELL)
		{
			break;
		}

		cells[otherCellId].myTid.store(FREETID);
	}

	//Dead point 4
	CrashPoints::GetInstance()->Crash(CrashPoints::GetInstance()->CrashInPoint24);


	MemStorage::GetInstance().release(toDelCellId);

	//Dead point 5
	CrashPoints::GetInstance()->Crash(CrashPoints::GetInstance()->CrashInPoint25);
	toDelCellId = INVALIDCELL;

	//Dead point 6
	CrashPoints::GetInstance()->Crash(CrashPoints::GetInstance()->CrashInPoint26);

	blocksIndex = 0;
	sibIndex = num - 1;
	return true;
}
