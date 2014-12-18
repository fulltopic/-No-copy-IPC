/*
 * CommQueue.cpp
 *
 *  Created on: Sep 7, 2014
 *      Author: root
 */

#include "CmmQueue.h"
#include "MemStorage.h"

#include <string.h>

#ifdef OLDCPP
#include <cstdatomic>
#else
#include <atomic>
#endif

#include <iostream>
#include <string>

//TODO: To set const tid at allocation register
CmmQueue::CmmQueue(): head(0), tail(0), myTid(FREETID), myIndex(-1)
{
	memset(slots, FREESLOT, sizeof(slots));
}

CmmQueue::~CmmQueue()
{
}

//head first
bool CmmQueue::isFull() const
{
	int localHead = head;
	int localTail = tail;

	if(localTail - localHead >= GLOBALQUECAP)
	{
//		cout << "Queue is full " << localTail << " , " << localHead << endl;
		return true;
	}

	return false;
}

bool CmmQueue::push(int cellId)
{
	if(!GlobalConfig::IsValidCell(cellId))
	{
		cout << "Invalid cellId " << cellId << endl;
		return false;
	}
//	getchar();

	Cell *const cells = MemStorage::GetInstance().getCells();
//	cout << "Cell id before store dstTid " << cellId << ":" << cells[cellId].myTid << endl;

	cells[cellId].dstTid.store(myTid);

	while(true)
	{
		uint localHead = head;
		uint localTail = tail;
		if(localTail - localHead >= GLOBALQUECAP)
		{
//			cout << "Queue is full "<< endl;
			return false;
		}

		int localCellId = cellId & DATAMASK;
		//TODO: Seemed no duplicate case
		if((uint)(cells[localCellId].myTid & CELLCURRTIDMASK) == myTid)
		{
			//It is a duplicated cell that had been pushed into the queue and popped by receiver
			cout <<  __FILE__ << ":" << __LINE__ << " The cell had unexpected owner " << myTid << "," << myIndex << endl;
			return true;
		}
//		cout <<  __FILE__ << ":" << __LINE__ << " The cell had EXPECTED owner " << myTid << endl;

		if(localTail != tail)
		{
			continue;
		}

		uint nextTail = localTail + 1;
		int localIndex = localTail & GLOBALQUEMASK;
		ulong tCellId = slots[localIndex];

//		cout << "Get newValue " << newValue << endl;
		if(GlobalConfig::IsEmptySlot(tCellId))
		{
			ulong newValue = (ulong)cellId | GlobalConfig::NextCounter(tCellId);
			if(slots[localIndex].compare_exchange_strong(tCellId, newValue))
			{
				tail.compare_exchange_strong(localTail, nextTail);
//				cout << "Get new tail after push " << tail << endl;
				return true;
			}
		}

		tail.compare_exchange_strong(localTail, nextTail);
	}

	//in-reachable
	return false;
}

//TODO: The duplicate cell pushed may cause sequence inversion of messages from the same sender.
//Cells can only short cut in stack
bool CmmQueue::pop(volatile ulong& cellId)
{
	Cell *const cells = MemStorage::GetInstance().getCells();
	while(true)
	{
		uint localHead = head;
//		cout << "Is empty? " << tail << " " << localHead << endl;
		if(localHead == tail)
		{
//			cout << "Empty queue " << endl;
			return false;
		}

		int localIndex = localHead & GLOBALQUEMASK;

		ulong rawCellId = slots[localIndex];
//		cout << "tCellId = " << tCellId << endl;

		//One pop user supposed, so no case the index refers to unexpected FREESLOT



		//TODOED: THE DSTTID STILL FACES ABA
		//Then, it not ABA, its duplicate cell in list. Then cellTid of the cell could be
		//A: original TID. It is OK. Even if the cell had been recycled, it contains the fresh content.
		//FREETID: Had been retired. Do not use.
		//myTid: The Cell had been received. Then it may be re-cycled. To be continued.
		//C: Others. That is OK. If the dstTid is not myTid, failed; else, it contains the fresh content.
		//	Then, if cell had been received then re-cycled. The status is corresponding to another cycle of above 4 cases

		//Monitor set dstTid as FREETID after CAS owner TID as FREETID.
		//Then, there is no case that the de-queuer gets the dirty dstTID and new owner id.
		//That is, SET of dstTid is enough, not necessary of CAS
		if(GlobalConfig::IsEmptySlot(rawCellId))
//		if(cellTid == FREETID || dstTid != myTid)
		{
			continue;
		}

		int tCellId = (int)(rawCellId & DATAMASK);
		uint cellTid = cells[tCellId].myTid;
		uint dstTid = cells[tCellId].dstTid;
		if(dstTid != myTid)
		{
			cout << "Fatal error " << endl;
			abort();
//			head = localHead + 1;
//			continue;
		}
		if(cellTid == myTid) //Impossible
		{
			head = localHead + 1;
			//obey programming sequence in single core
			continue;
		}else
		{
			//TODOED: Reduce chance of CAS as corruption happens rarely
			//Seemed not necessary to CAS as if monitor detected scale cell,
			//it leaves the ownership to receiver although not executed yet.
			cells[tCellId].myTid.store(myTid);
			cells[tCellId].dstTid = FREETID;
			slots[localIndex] = FREESLOT | GlobalConfig::NextCounter(rawCellId);
			cellId = (ulong)tCellId;
			head = localHead + 1;
			return true;
//			if(cells[tCellId].myTid.compare_exchange_strong(cellTid, myTid))
//			{
//				cellId = tCellId;
//				head = localHead + 1;
//				cells[tCellId].dstTid = FREETID;
//				return true;
//			}else
//			{
//				continue;
//			}
		}
	}

	//Unreachable
	return false;
}

//Obviously, all cells in queue has no sibling

//TODOED: Pay attention to last enqueued one as. Seemed nothing special
//TODO： To set the empty with new counter by CAS so that further push will fail
void CmmQueue::cleanup()
{
	Cell * cells = MemStorage::GetInstance().getCells();

	int localHead = head;
	int localTail = tail;

	//To prevent further en-queue
	tail = localHead + GLOBALQUECAP;

	int tailIndex = localTail & GLOBALQUEMASK;
	int currIndex = localHead & GLOBALQUEMASK;
	//Do not touch head so that producer can detect full as soon as possible

	int sibIndex = -1;
	int cellIndex = INVALIDCELL;
	bool tailMet = false;


	while(true)
	{
		if(currIndex == tailIndex)
		{
			tailMet = true;
		}

		uint freeCellIndex = slots[currIndex] & DATAMASK;
		if(tailMet)
		{
			if(freeCellIndex == FREESLOT)
			{
				break;
			}
		}

//		int freeCellIndex = slots[currIndex] & DATAMASK;
		int cellTid = cells[freeCellIndex].myTid;

		//If
		if(!GlobalConfig::IsFreeTid(cellTid))
		{
			cells[freeCellIndex].myTid =
					((myTid) << CELLLASTTIDSHIFT);
			cells[freeCellIndex].dstTid = FREETID;
		}

		//Seemed no such case if no duplicate cells in global list
//		if(!(cellTid == FREETID || cells[freeCellIndex].dstTid != myTid || cells[freeCellIndex].myTid == myTid))
//		{
//			cells[freeCellIndex].myTid = FREETID;
//			cells[freeCellIndex].dstTid = FREETID;
//		}

		//TODO: Before tail met, just assign myTid and dstTid as FREETID
		//TODO: After tail, should wait the sender CAS these TIDS. How to guarantee?
		//TODO: If sender died, then deadlock
		//TODO: To make the queue full to prevent further push

		sibIndex = (sibIndex + 1) & SIBLINGMASK;
		currIndex  = (currIndex + 1) & GLOBALQUEMASK;

		if(sibIndex == 0)
		{
			//Initial cellIndex
			if(cellIndex != (int)INVALIDCELL)
			{
				volatile ulong tCellIndex = cellIndex;
				MemStorage::GetInstance().release(tCellIndex);
			}
			cellIndex = freeCellIndex;
		}else
		{
			cells[cellIndex].siblings[sibIndex - 1] = freeCellIndex;
		}
	}

	//TODOED: What's this for?
	//Deal with the remaining.
	volatile ulong tCellIndex = cellIndex;
	if(cellIndex == (int)INVALIDCELL)
	{
		return;
	}else
	{
		MemStorage::GetInstance().release(tCellIndex);
	}
}

bool CmmQueue::contains(int cellId) const
{
	int localTail = tail;
	int localHead = head;

	for(int i = localHead; i <= localTail; i ++)
	{
		int index = i & GLOBALQUEMASK;

		if(slots[index] == (ulong)cellId)
		{
			return true;
		}
	}

	return false;
}
