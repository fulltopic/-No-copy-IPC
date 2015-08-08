/*
 * GlobalFreeList.cpp
 *
 *  Created on: Sep 7, 2014
 *      Author: root
 */

#include <GlobalConfig.h>
#include "GlobalFreeList.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "Cell.h"
#include "MemStorage.h"


using namespace std;

__thread uint GlobalFreeList::userId(0);
//Another solution is make global free list a stack
//Then monitor could work exclusively
GlobalFreeList::GlobalFreeList(): freeListTail(0), freeListHead(0)
{
	// TODO Auto-generated constructor stub
	srand((uint)time(NULL));

	init();
}

GlobalFreeList::~GlobalFreeList()
{
	// TODO Auto-generated destructor stub
}

//TODO: Cache needs no protection of counter
bool GlobalFreeList::init()
{
//	int cellIndex = 0;
	for(int i = 0; i < GLOBALBLOCKSIZE; i ++)
	{
		freeList[i] = i * BLOCKSIZE;
//		cout << "freeList[" << i << "] = " << freeList[i] << endl;
	}
	freeListTail = GLOBALBLOCKSIZE;

	for(int i = GLOBALBLOCKSIZE; i < GLOBALFREELISTSIZE; i ++)
	{
		freeList[i] = FREESLOT;
	}


	for(int i = 0; i < CACHESIZE; i ++)
	{
		caches[i] = FREESLOT;
	}
	return true;
}

bool GlobalFreeList::push(volatile ulong& cellId)
{
	Cell *cells = MemStorage::GetInstance().getCells();

	//TODO: The reset of tid may be postponed to the end of push
	//That depends on pop: If it requires a FREETID.
	cells[cellId].myTid.store(FREETID);

	bool rc = false;
	do
	{
		uint localHead = freeListHead;
		uint localTail = freeListTail;

		if((localTail - localHead) >= GLOBALFREELISTSIZE)
		{
			abort();
			//FATAL ERROR; Should be impossible
		}
		int localIndex = localTail & GLOBALFREELISTMASK;
		ulong oldVal = freeList[localIndex].load();

		if(localTail != freeListTail)
		{
			continue;
		}

		uint nextTail = localTail + 1;
		if(GlobalConfig::IsEmptySlot(oldVal))
		{
			ulong oldCounter = oldVal & COUNTERMASK;

			//TODO: To make a next counter function
			ulong newVal = cellId | (oldCounter + COUNTERSTEP);

			rc = freeList[localIndex].compare_exchange_strong(oldVal, newVal);
		}
		freeListTail.compare_exchange_strong(localTail, nextTail);

	}while(!rc);


	//TODOED: Check it
	cellId = INVALIDCELL;
	return true;
}

//Monitor has no knowledge of local list. Just collect garbage in cells. That is, cellId input would not be collected
//A cell with tid == A would be released by only one thread once, the A thread(alive) or the monitor(A thread dead)
//Monitor to clean free list before clean cells.
//cellId from SHM local list tmp result

bool GlobalFreeList::pop(volatile ulong& cellId)
{
	if(freeListTail == freeListHead)
	{
		return false;
	}

	//Monitor may release cell with tid = FREETID

	//It is an error
	Cell *cells = MemStorage::GetInstance().getCells();

	bool rc = false;
	do
	{
		uint localHead = freeListHead;

		if(localHead == freeListTail)
		{
			//TODO: How if died at this point?
			cellId = FREEDATA;
			return false;
		}
		int localIndex = localHead & GLOBALFREELISTMASK;

		//TODO: Prove monitor.clean toAllocCellId
		cellId = freeList[localIndex];
//		cout << "----------------> Get cellID " << localIndex << ":" << (cellId & DATAMASK) << endl;
		if(localHead != freeListHead)
		{
			continue;
		}

		uint nextHead = localHead + 1;
		if(!GlobalConfig::IsEmptySlot(cellId))
		{
			int cellIndex = cellId & DATAMASK;
			uint oldTid = cells[cellIndex].myTid;
			ulong newValue = FREEDATA | ((cellId & COUNTERMASK) + COUNTERSTEP);

			ulong oldValue = cellId;
			if(freeList[localIndex].compare_exchange_strong(oldValue, newValue))
			{
				if(GlobalConfig::IsFreeTid(oldTid))
				{
					rc = cells[cellIndex].myTid.compare_exchange_strong(oldTid, userId);
				}else
				{
					cellId = INVALIDCELL;
				}
			}
/*
			if(oldTid == FREETID)
			{
				ulong oldValue = cellId;
				if(freeList[localIndex].compare_exchange_strong(oldValue, newValue))
				{
//					cout << "GlobalFreeList pop get cellId " << cellId << endl;
					//TODO: How if died at this point?
					//Do not store all local list into SHM, but the transit vars (popCellId, pushCellId) into SHM
					rc = cells[cellIndex].myTid.compare_exchange_strong(oldTid, userId);

					//How if re-used?
					//Monitor would CAS tid in freelist from A to FREETID, if it's FREETID, to pop it
					//Do not re-use the FRED cell as the monitor is busying inserting it into free list
					//				if(!rc && oldTid == FREETID)
					//				{
					//					rc = cells[cellId].myTid.store(userId);
					//				}
				}else
				{
					//Update head index
				}
			}else
			{
				//TODOED: If continue to push tail = nextTail is OK?
				//Should recalculate head tail index
				continue;
			}
*/
		}
		freeListHead.compare_exchange_strong(localHead, nextHead);

//		if(cellId == 1248)
//		{
//			;
//		}
	}while(!rc);

	if(cells[cellId].myTid != FREETID)
	{
		abort();
	}

	//TODO: The cellId popped had to be accessible to avoid leak. The monitor would
	// Assert oldTid == FREETID and CAS to MonitorTid then go on.
//	cout << "GlobalFreeList pop return " << cellId << endl;
	return true;
}

//TODO: caches
bool GlobalFreeList::contains(const int cellId)
{
	int snapTail = freeListTail;
	int snapHead = freeListHead;

	int localTailIndex = snapTail & GLOBALBLOCKMASK;

	//TODO: To prove the block is wait-free
	while(!GlobalConfig::IsEmptySlot(freeList[localTailIndex]))
	{
		snapTail ++;
	}

	for(int i = snapHead; i < snapTail; i ++)
	{
		int localIndex = i & GLOBALBLOCKMASK;
		if((int)(freeList[localIndex] & DATAMASK) == cellId)
		{
			return true;
		}
	}

	return false;
}

bool GlobalFreeList::containsInDetail(const int cellId)
{
	if(!GlobalConfig::IsValidCell(cellId))
	{
		return false;
	}

	int localTail = freeListTail;
	int localHead = freeListHead;
	Cell *cells = MemStorage::GetInstance().getCells();

	for(int i = localHead; i < localTail; i ++)
	{
		int blockCellIndex = GlobalConfig::GetFreeListCellIndex(freeList[i]);
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

bool GlobalFreeList::checkList4Dup(vector<bool>& checkList)
{
	Cell *cells = MemStorage::GetInstance().getCells();

	for(int i = 0; i < GLOBALFREELISTSIZE; i ++)
	{
		if(GlobalConfig::IsEmptySlot(freeList[i]))
		{
			continue;
		}else
		{
			int cellIndex = freeList[i] & DATAMASK;
			if(checkList[cellIndex])
			{
				cout << "Repeated in " << cellIndex << endl;
				return false;
			}else
			{
				checkList[cellIndex] =  true;
				for(int j = 0; j < SIBLINGSIZE; j ++)
				{
					int otherCellId = cells[cellIndex].siblings[j];
					if(otherCellId == INVALIDCELL)
					{
						break;
					}else
					{
						if(checkList[otherCellId])
						{
							cout << "Duplicated in " << otherCellId << endl;
							return false;
						}else
						{
							checkList[otherCellId] = true;
						}
					}
				}
			}
		}
	}

	return true;
}

bool GlobalFreeList::checkList4Miss(vector<bool>& checkList)
{
	Cell *cells = MemStorage::GetInstance().getCells();

	for(int i = 0; i < GLOBALFREELISTSIZE; i ++)
	{
		if(GlobalConfig::IsEmptySlot(freeList[i]))
		{
			continue;
		}else
		{
			int cellIndex = freeList[i] & DATAMASK;
			checkList[cellIndex] = true;

			for(int j = 0; j < SIBLINGSIZE; j ++)
			{
				int otherCellId = cells[cellIndex].siblings[j];
				if(otherCellId == INVALIDCELL)
				{
					break;
				}else
				{
					checkList[otherCellId] = true;
				}
			}
		}
	}

	for(int i = 0; i < TOTALBLOCKSIZE; i ++)
	{
		if(!checkList[i])
		{
			cout << i << "Missed" << endl;
			return false;
		}
	}

	return true;
}

bool GlobalFreeList::checkNoDupInList()
{
	vector<bool> checkList(TOTALBLOCKSIZE);

	for(int i = 0; i < TOTALBLOCKSIZE; i ++)
	{
		checkList[i] = false;
	}

	return checkList4Dup(checkList);
}

bool GlobalFreeList::checkNoMissInList()
{
	vector<bool> checkList(TOTALBLOCKSIZE);

	for(int i = 0; i < TOTALBLOCKSIZE; i ++)
	{
		checkList[i] = false;
	}

	return checkList4Miss(checkList);
}

bool GlobalFreeList::checkNoDup()
{
	vector<bool> checkList(TOTALBLOCKSIZE);
	Cell *cells = MemStorage::GetInstance().getCells();

	for(int i = 0; i < TOTALBLOCKSIZE; i ++)
	{
		checkList[i] = false;
	}

	for(int i = 0; i < TOTALBLOCKSIZE; i ++)
	{
		if(!GlobalConfig::IsFreeTid(cells[i].myTid))
		{
			checkList[i] = true;
		}
	}

	return checkList4Dup(checkList);
}

bool GlobalFreeList::checkNoMiss()
{
	vector<bool> checkList(TOTALBLOCKSIZE);

	Cell *cells = MemStorage::GetInstance().getCells();
	for(int i = 0; i < TOTALBLOCKSIZE; i ++)
	{
		checkList[i] = false;
	}

	for(int i = 0; i < TOTALBLOCKSIZE; i ++)
	{
		if(!GlobalConfig::IsFreeTid(cells[i].myTid))
		{
			checkList[i] = true;
		}
	}

	return checkList4Miss(checkList);
}
