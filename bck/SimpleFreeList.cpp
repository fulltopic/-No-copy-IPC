/*
 * SimpleFreeList.cpp
 *
 *  Created on: Nov 22, 2014
 *      Author: root
 */

#include "SimpleFreeList.h"
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;
template<int LISTSIZE>
SimpleFreeList<LISTSIZE>::SimpleFreeList(): mask((ulong)(LISTSIZE - 1))
{
	init();
}

template<int LISTSIZE>
void SimpleFreeList<LISTSIZE>::init()
{
	memset(list, 0, sizeof(list));
}

template<int LISTSIZE>
bool SimpleFreeList<LISTSIZE>::pushSingle(uint item)
{
	if(isFull())
	{
		return false;
	}

	ulong localTail = tail;
	int tailIndex = localTail & mask;
	ulong oldValue = list[tailIndex];

	if(!isEmptySlot(oldValue))
	{
		cout << "Unexpected fault " << endl;
		abort();
	}

	ulong newValue = (GlobalConfig::NextCounter(oldValue)) | item;
	list[tailIndex] = newValue;

	tail = localTail + 1;

	return true;
}

template<int LISTSIZE>
bool SimpleFreeList<LISTSIZE>::popSingle(uint& item)
{
	if(isEmpty())
	{
		return false;
	}

	ulong localHead = head;
	int headIndex = localHead & mask;
	ulong oldValue = list[headIndex];

	if(isEmptySlot(oldValue))
	{
		cout << "Unexpected fault " << endl;
		abort();
	}

	ulong newValue = (GlobalConfig::NextCounter(oldValue)) | FREESLOT;
	item = oldValue & DATAMASK;

	list[headIndex] = newValue;

	return true;
}

template<int LISTSIZE>
bool SimpleFreeList<LISTSIZE>::pushMul(uint item)
{
	if(isFull())
	{
		return false;
	}

	bool rc = false;

	do
	{
		ulong localTail = tail;
		int tailIndex = localTail & mask;
		ulong oldValue = list[tailIndex];

		if(localTail != tail)
		{
			continue;
		}

		if(!isEmptySlot(oldValue))
		{
			continue;
		}

		ulong newValue = (GlobalConfig::NextCounter(oldValue)) | item;
		rc = list[tailIndex].compare_exchange_strong(oldValue, newValue);

		ulong nextTail = localTail + 1;
		tail.compare_exchange_strong(localTail, nextTail);
	}while(!rc);

	return true;
}

//TODO: When alloc cmmq failed in between this function
template<int LISTSIZE>
bool SimpleFreeList<LISTSIZE>::popMul(uint& item)
{
	if(isEmpty())
	{
		return false;
	}
	bool rc = false;

	do
	{
		ulong localHead = head;
		int headIndex = localHead & mask;
		ulong oldValue = list[headIndex];

		if(localHead != head)
		{
			continue;
		}
		if(isEmptySlot(oldValue))
		{
			continue;
		}

		ulong newValue = (GlobalConfig::NextCounter(oldValue)) | FREESLOT;
		item = oldValue & DATAMASK;

		rc = list[headIndex].compare_exchange_strong(oldValue, newValue);
		ulong nextHead = localHead + 1;
		head.compare_exchange_strong(localHead, nextHead);

	}while(!rc);

	return true;
}
