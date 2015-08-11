/*
 * Monitor.cpp
 *
 *  Created on: Sep 7, 2014
 *      Author: root
 */

#include "Monitor.h"
#include "MemStorage.h"

//#ifndef __GXX_EXPERIMENTAL_CXX0X__
//#define __GXX_EXPERIMENTAL_CXX0X__
//#endif

#include <iostream>
#include <string>
#include <unistd.h>
#include <thread>

using namespace std;
Monitor::Monitor(): isRunning(true), collector(NULL)
{
	MemStorage::GetInstance(true); //To init instance
}

Monitor::~Monitor()
{
	// TODO To clean up SHM
}

void Monitor::toCleanDeadPid(const pid_t pid)
{
	uint tid = INVALIDTID;

	if(MemStorage::GetInstance(true).findTidByPid(pid, tid))
	{
		deadTids.push(tid);

		int currLoad = deadTids.size();
		string warns = NULL;
		if(currLoad > CRITICALLOAD)
		{
			warns = "CRITICAL";
		}else if(currLoad > MAJORLOAD)
		{
			warns = "MAJOR";
		}else if(currLoad > MINORLOAD)
		{
			warns = "MINOR";
		}

		if(warns)
		{
			cout << warns << ": Too many dead processes: " << currLoad << endl;
		}
	}
}

//TODO:
void Monitor::cleanDeadTid(const uint tid)
{
	cout << "To clean tid " << tid << endl;
	cleanTransitCells(tid);
	cleanCmmQs(tid);
	cleanCells(tid);
	clearAppResource(tid);
	cout << "End of cleaning tid " << tid << endl;
}

void Monitor::cleanCmmQs(const uint tid)
{
	CmmQueue *qs = MemStorage::GetInstance(true).getQs();

	for(int i = 0; i < GLOBALQUESIZE; i ++)
	{
		if(qs[i].getMyTid() == tid)
		{
			qs[i].cleanup();
		}
	}
}

//Ensure the en-listed sequence, so that there is no roll-back to cause huge big O
//That is, less the earlier
//TODOED: Ensure the cell eliminated by cleanTransitCells would not be released by this function
//cleanCmmQ had nothing to do with cells clean.
//For transit release cell, if the cell.tid == myTid, the cell released by cleanTransitCells;
//	if the cell.tid != myTid, cleanCells can not detect the cell.
//For transit allocated cell, if the cell.tid = myTid, the cell released by cleanTransitCells;
//	if the cell.tid != myTid, the cell.tid would be CASed as myTid and released or remain others that can not be detected by cleanCells
void Monitor::cleanCells(const uint tid)
{
	//If the single cell is still attached on a block cell, the cell is impossible in transit or in flying
	cleanBlockCells(tid);
	cleanSingleCells(tid);
}

//TODOED: To fine the 2 functions
void Monitor::cleanBlockCells(const uint tid)
{
	Cell *cells = MemStorage::GetInstance(true).getCells();
	int mergeCellId = INVALIDCELL;
	int sibIndex = 0;
	for(int i = 0; i < GLOBALCELLSIZE; i ++)
	{
		uint currTid = cells[i].myTid;

		if(currTid != tid)
		{
			continue;
		}

		//TODOED: Ensure when node in list, there is no in-consistent status
		if(cells[i].siblings[SIBLINGSIZE - 1] != (int)INVALIDCELL)
		{
			for(int j = 0; j < SIBLINGSIZE; j ++)
			{
				int sibCellId = cells[i].siblings[j];
				cells[sibCellId].myTid = (currTid << CELLLASTTIDSHIFT);
			}
			cells[i].myTid = (currTid << CELLLASTTIDSHIFT);

			volatile ulong tmpI = i;
			MemStorage::GetInstance(true).release(tmpI);

			continue;
		}

		//TODOED: Ensure global list does not deal with single (or internal) cell. Instead, it only pushes external (or bash) cell
		if(cells[i].siblings[0] != (int)INVALIDCELL)
		{
			for(int j = 0; j < SIBLINGSIZE; j ++)
			{
				int tCellId = cells[i].siblings[j];
				if(tCellId == (int)INVALIDCELL)
				{
					break;
				}

				cells[i].siblings[j] = INVALIDCELL;
				cells[tCellId].myTid = (currTid << CELLLASTTIDSHIFT);
				mergeCell(mergeCellId, sibIndex, tCellId);
			}
			cells[i].myTid = ((currTid << CELLLASTTIDSHIFT) | FREETID);
			mergeCell(mergeCellId, sibIndex, i);
		}


//		if(mergeCellId == INVALIDCELL)
//		{
//			mergeCell(mergeCellId, sibIndex, i);
//		}
//		else
//		{
//			if(cells[i].siblings[0] == INVALIDCELL)
//			{
//				//To recycle block cell at first to avoid the case that
//				//a cell had been recycled as single cell and then as block cell
//				continue;
//			}
//			for(int j = SIBLINGSIZE - 1; j >= 0; j --)
//			{
//				if(cells[i].siblings[j] == INVALIDCELL)
//				{
//					continue;
//				}
//
//				int tCellId = cells[i].siblings[j];
//				cells[i].siblings[j] = INVALIDCELL;
//				cells[tCellId].myTid = FREETID;
//
//				mergeCell(mergeCellId, sibIndex, tCellId);
//			}
//			cells[i].myTid = FREETID;
//			mergeCell(mergeCellId, sibIndex, i);
//		}
	}
}


void Monitor::cleanSingleCells(const uint tid)
{
	Cell *cells = MemStorage::GetInstance(true).getCells();
	int mergeCellId = INVALIDCELL;
	int sibIndex = 0;
	for(int i = 0; i < GLOBALCELLSIZE; i ++)
	{
		uint currTid = cells[i].myTid;

		if(currTid != tid)
		{
			continue;
		}

		if(cells[i].siblings[0] == (int)INVALIDCELL)
		{
//			uint userTid = tid;

			uint dstTid = cells[i].dstTid;
			if(dstTid != FREETID)
			{
				//TODOED: If the cell in flying, do not recycle it. Leaving the job to receiver.
				if(MemStorage::GetInstance(true).isFlying(dstTid, i))
				{
					continue;
				}
				//TODOED: What's the status if it's not in fly?
				//The cell had been de-queued, so that myTid had changed.
				//Or the cell failed to pushed. Then to free
				else
				{
					//corresponding case:
					//M.R(myTid == A && dstTid == B) --> B.pop(cell) --> B.W(myTid = B && dstTid = FREETID)
					// --> M.R(isFlying == false) --> M to release the cell
					//In fact, as queue stores tid before update head index,
					//it is impossible that the cell is not in flying, and with myTid == tid
					//and then myTid != tid
					if(cells[i].myTid == tid)
					{
						cells[i].myTid = ((currTid << CELLLASTTIDSHIFT) | FREETID);
						cells[i].dstTid = FREETID;
					}else
					{
						continue;
					}
				}
			}else
			{
				cells[i].myTid = ((currTid << CELLLASTTIDSHIFT) | FREETID);
				cells[i].dstTid = FREETID;
			}
			mergeCell(mergeCellId, sibIndex, i);
		}
	}
}

//No case that sibling is released and block had not
void Monitor::cleanSuspectCells(const uint tid, const int localDelCellId)
{
	uint suspectCellId = MemStorage::GetInstance(true).getSuspectAllocCell(tid);
	Cell *cells = MemStorage::GetInstance(true).getCells();
	GlobalFreeList& freeList = MemStorage::GetInstance(true).getFreeList();

	while(suspectCellId != INVALIDCELL)
	{
		bool toRelease = false;

		if((GlobalConfig::IsFreeTid(cells[suspectCellId].myTid) &&
				(cells[suspectCellId].myTid & CELLLASTTIDMASK) == (tid << CELLLASTTIDSHIFT)))
		{
			if(freeList.containsInDetail((int)suspectCellId))
			{
				toRelease = false;
			}else if(MemStorage::GetInstance(true).isInDetailAllocTransit(localDelCellId))
			{
				toRelease = false;
			}
			//TODO: a timely routine, go through the whole freelist and alloc list
			else if((uint)localDelCellId != INVALIDCELL)
			{
				if(suspectCellId != (uint)localDelCellId)
				{
					for(int i = 0; i < SIBLINGSIZE; i ++)
					{
						if((uint)cells[localDelCellId].siblings[i] == INVALIDCELL)
						{
							toRelease = true;
							break;
						}
						else if((uint)cells[localDelCellId].siblings[i] == suspectCellId)
						{
							//To recycle by tid
							toRelease = false;
							break;
						}
					}
				}else
				{
					//To recycled by tid
					toRelease = false;
				}
			}else
			{
				//Not recycled by tid
				toRelease = true;
			}
		}else
		{
			//Had been recycled
			toRelease = false;
		}


		if(toRelease)
		{
			if((GlobalConfig::IsFreeTid(cells[suspectCellId].myTid) &&
							(cells[suspectCellId].myTid & CELLLASTTIDMASK) == (tid << CELLLASTTIDSHIFT)))
			{
				uint oldTid = (tid << CELLLASTTIDSHIFT) | FREETID;
				uint newTid = (INVALIDTID << CELLLASTTIDSHIFT) | FREETID;

				cells[suspectCellId].myTid.compare_exchange_strong(oldTid, newTid);
				volatile ulong tmpCellId = suspectCellId;
				MemStorage::GetInstance(true).release(tmpCellId);
			}else
			{
				//Allocated by others
			}
		}

		suspectCellId = MemStorage::GetInstance(true).getSuspectAllocCell(tid);
	}
}

void Monitor::cleanTransitCells(const uint tid)
{
	ulong toDelCellId = INVALIDCELL;
	ulong toAllocCellId = INVALIDCELL;

	if(!MemStorage::GetInstance(true).getTransitCell(tid, toDelCellId, toAllocCellId))
	{
		cout << "Failed to get transitcells for tid " << tid << endl;
		return;
	}else
	{
		cout << "To clean delCellId " << toDelCellId << endl;
		cout << "To clean allocCellId " << toAllocCellId << endl;
	}
	int localDelCellId = toDelCellId & DATAMASK;
	cleanSuspectCells(tid, localDelCellId);

	GlobalFreeList& freeList = MemStorage::GetInstance(true).getFreeList();
	Cell* cells = MemStorage::GetInstance(true).getCells();


	if((uint)localDelCellId != (uint)INVALIDCELL)
	{
		if(cells[localDelCellId].myTid == tid) //Remove not began
		{
			for(int i = 0; i < SIBLINGSIZE; i ++)
			{
				int internalCellId = cells[localDelCellId].siblings[i];
				if((uint)internalCellId == (uint)INVALIDCELL)
				{
					break;
				}
				cells[internalCellId].myTid = FREETID;
			}
			cells[localDelCellId].myTid = FREETID;
			freeList.push(toDelCellId);
		}else if(GlobalConfig::IsFreeTid(cells[localDelCellId].myTid)) //Remove may not finished
		{
			//TODO: To prove it's correct
			//It may before recycle || recycled || recycled and recycled by others
			if(!freeList.contains(localDelCellId) && !MemStorage::GetInstance(true).isInAllocTransit(localDelCellId))
			{
				//TODO: Can distinguish //It may before recycle || before recycle by others
				if(cells[localDelCellId].myTid == ((tid << CELLLASTTIDSHIFT) |FREETID))
				{
					freeList.push(toDelCellId);
				}

				//Maybe duplicate items in freelist, while unique in-use
			}
		}else
		{
			//Had been reused
		}
	}

	int localAllocCellId = toAllocCellId & DATAMASK;

	//Allocation failed or not finished
	if((uint)localAllocCellId != INVALIDCELL)
	{
		//TODO: Check  the freelist and alllocTransit
		if(GlobalConfig::IsFreeTid(cells[localAllocCellId].myTid))
		{
			if(!freeList.contains(localAllocCellId) && !MemStorage::GetInstance(true).isInAllocTransit(localAllocCellId))
			{
//			uint expTid = FREETID;
//			if(cells[localAllocCellId].myTid.compare_exchange_strong(expTid, tid))
//			{
//				//Sibling had been reset before it's been pushed into global list
////				toAllocCellId = localAllocCellId;
////				freeList.push(toAllocCellId);
//				//To be released by cleanBlockCells()
//			}else
//			{
//				//Occupied by other TID
//			}
				uint suspectTid = (cells[localAllocCellId].myTid & CELLLASTTIDMASK);
				MemStorage::GetInstance(true).putSuspectAllocCell(localAllocCellId, suspectTid);
			}else
			{
				//Occupied by other TID
			}
		}else
		{
			//Occupied by other TID
		}
	}

	toDelCellId = INVALIDCELL;
	toAllocCellId = INVALIDCELL;
}

//TODO: Set valid cell id with last cell id
void Monitor::mergeCell(int& blockId, int& sibIndex, int cellId)
{
	Cell *cells = MemStorage::GetInstance(true).getCells();
	if(blockId == (int)INVALIDCELL)
	{
		blockId = cellId;

		int num = 0;
		for(; num < SIBLINGSIZE; num ++)
		{
			int tCellId = cells[cellId].siblings[num];
			if(tCellId == (int)INVALIDCELL)
			{
				break;
			}


			//Had been set by caller
//			cells[tCellId].myTid = FREETID;
		}
		sibIndex = num;
		cells[cellId].myTid = FREETID;
	}else
	{
		cells[blockId].siblings[sibIndex] = cellId;
		sibIndex ++;

		if(sibIndex == SIBLINGSIZE)
		{
			volatile ulong tBlockId = blockId;
			MemStorage::GetInstance(true).release(tBlockId);

			sibIndex = 0;
			blockId = INVALIDCELL;
		}
	}
}

void Monitor::clearAppResource(const uint tid)
{
	MemStorage::GetInstance(true).clearAppResource(tid);
}

void Monitor::runRoutine()
{
	while(isRunning)
	{
		if(deadTids.empty())
		{
			sleep(1);
		}else
		{
			uint toDelTid = deadTids.front();
			deadTids.pop();

			//TODO: It should be a queue of app info
			cleanDeadTid(toDelTid);
		}
	}

//	while(isRunning)
//	{
//		if(deadPids.empty())
//		{
//			sleep(1);
//		}else
//		{
//			pid_t toDelPid = deadPids.front();
//			deadPids.pop();
//			uint toDelTid = INVALIDTID;
//			if(MemStorage::GetInstance(true).findTidByPid(toDelPid, toDelTid))
//			{
//				cleanDeadTid(toDelTid);
//			}
//		}
//	}
}

void Monitor::startCollector()
{
	if(collector != NULL)
	{
		cout << "The routine is running " << collector->get_id() << endl;
		return;
	}
	collector = new thread(Monitor::Collector(*this));
	isRunning = true;
}

void Monitor::stopCollector()
{
	if(collector == NULL)
	{
		return;
	}
	collector->join();
	delete collector;
	collector = NULL;
}


Monitor::Collector::Collector(Monitor& m): monitor(m)
{
}

Monitor::Collector::~Collector() {}

void Monitor::Collector::operator ()(void)
{
	monitor.runRoutine();
}

void Monitor::threadMain(Monitor* monitor)
{
	monitor->runRoutine();
}


