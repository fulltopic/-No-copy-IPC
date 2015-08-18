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
		string warns = "NORMAL";
		if(currLoad > CRITICALLOAD)
		{
			warns = "CRITICAL";
		}else if(currLoad > MAJORLOAD)
		{
			warns = "MAJOR";
		}else if(currLoad > MINORLOAD)
		{
			warns = "MINOR";
		}else
		{
			return;
		}

		cout << warns << ": Too many dead processes: " << currLoad << endl;

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

void Monitor::cleanBlockCells(const uint tid)
{
	Cell *cells = MemStorage::GetInstance(true).getCells();
	int mergeCellId = INVALIDCELL;
	int sibIndex = 0;
	volatile uint tmpI;

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
				cells[sibCellId].myTid = FREETID;
			}
			cells[i].myTid = FREETID;

			tmpI = i;
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
				cells[tCellId].myTid = FREETID;
				mergeCell(mergeCellId, sibIndex, tCellId);
			}
			cells[i].myTid = FREETID;
			mergeCell(mergeCellId, sibIndex, i);
		}

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
						cells[i].myTid = FREETID;
						cells[i].dstTid = FREETID;
					}else
					{
						continue;
					}
				}
			}else
			{
				cells[i].myTid = FREETID;
				cells[i].dstTid = FREETID;
			}
			mergeCell(mergeCellId, sibIndex, i);
		}
	}
}


void Monitor::cleanTransitCell(const uint cellId, const uint tid)
{
	Cell* cells = MemStorage::GetInstance(true).getCells();

	if(cellId == INVALIDCELL)
	{
		return;
	}

	if(cells[cellId].myTid != FREETID)
	{
		return;
	}

	uint oldV = FREETID;
	uint newV = FREETID | DIRTYTID;
	if(!cells[cellId].myTid.compare_exchange_strong(oldV, newV))
	{
		return;
	}

	if(MemStorage::GetInstance(true).isInRelTransit(cellId))
	{
		return;
	}else if(!GlobalConfig::IsDirtyTid(cells[cellId].myTid))
	{
		return;
	}

	if(MemStorage::GetInstance(true).freeList.contains(cellId))
	{
		return;
	}else if(!GlobalConfig::IsDirtyTid(cells[cellId].myTid))
	{
		return;
	}

	if(MemStorage::GetInstance(true).isInAllocTransit(cellId))
	{
		return;
	}else if(!GlobalConfig::IsDirtyTid(cells[cellId].myTid))
	{
		return;
	}


	cells[cellId].myTid = tid;
	return;
}

void Monitor::cleanTransitCells(const uint tid)
{
	uint toDelCellId = INVALIDCELL;
	uint toAllocCellId = INVALIDCELL;

	if(!MemStorage::GetInstance(true).getTransitCell(tid, toDelCellId, toAllocCellId))
	{
		cout << "Failed to get transitcells for tid " << tid << endl;
		return;
	}

	cleanTransitCell(toAllocCellId, tid);
	cleanTransitCell(toDelCellId, tid);
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
			volatile uint tBlockId = blockId;
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


