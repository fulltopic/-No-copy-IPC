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
#include <string.h>

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
		uint nextTail = localTail + 1;
		int localIndex = localTail & GLOBALQUEMASK;
		ulong tCellId = slots[localIndex];

		if(localTail != tail)
		{
			continue;
		}

//		cout << "Get newValue " << newValue << endl;
		if(GlobalConfig::IsEmptySlot(tCellId))
		{
			ulong newValue = GlobalConfig::NextValue(cellId, tCellId);
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
			return false;
		}

		int localIndex = localHead & GLOBALQUEMASK;

		ulong rawCellId = slots[localIndex];

		//One pop user supposed, so no case the index refers to unexpected FREESLOT

		if(GlobalConfig::IsEmptySlot(rawCellId))
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
			cells[tCellId].dstTid = FREETID;
			cells[tCellId].myTid.store(myTid);
			slots[localIndex] = GlobalConfig::NextValue(FREESLOT, rawCellId);
			cellId = (ulong)tCellId;
			head = localHead + 1;
			return true;
		}
	}

	//Unreachable
	return false;
}

//Obviously, all cells in queue has no sibling

//TODOED: Pay attention to last enqueued one as. Seemed nothing special
//TODOED： To set the empty with new counter by CAS so that further push will fail
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
	uint myLocalTid = myTid;

	//TODOED: To prove
	//When queue had been set full, no matter how many producer are sending,
	//only one of them can push successfully, while the timing of value set/read is an issue
	//It is OK, as producer gets old value before tail updated to full
	//And when empty slot CAS succeeded, producer must fail
	volatile uint tCellIndex = INVALIDCELL;
	for(int i = 0; i < GLOBALQUEMASK; i ++)
	{
		ulong slotV = slots[currIndex];
		ulong nextV = GlobalConfig::NextValue(FREESLOT, slotV);

		if(GlobalConfig::IsEmptySlot(slotV))
		{
			if(slots[currIndex].compare_exchange_strong(slotV, nextV))
			{
				continue;
			}else
			{
				slotV = slots[currIndex];
				nextV = GlobalConfig::NextValue(FREESLOT, slotV);
			}
		}

		slots[currIndex] = nextV;
		uint freeCellIndex = GlobalConfig::CurrValue(slotV);
		cells[freeCellIndex].myTid = myLocalTid;
		cells[freeCellIndex].dstTid = FREETID;

		sibIndex = (sibIndex + 1) & SIBLINGMASK;
		currIndex  = (currIndex + i) & GLOBALQUEMASK;

		if(sibIndex == 0)
		{
			//Initial cellIndex
			if(cellIndex != (int)INVALIDCELL)
			{
				tCellIndex = cellIndex;
				MemStorage::GetInstance().release(tCellIndex);
			}
			cellIndex = freeCellIndex;
		}else
		{
			cells[cellIndex].siblings[sibIndex - 1] = freeCellIndex;
		}
	}

	//Deal with the remaining.
	if(cellIndex == (int)INVALIDCELL)
	{
		return;
	}else
	{
		tCellIndex = cellIndex;
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

		if(GlobalConfig::CurrValue(slots[index]) == cellId)
		{
			return true;
		}
	}

	return false;
}
