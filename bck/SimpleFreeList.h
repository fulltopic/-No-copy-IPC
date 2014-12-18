/*
 * SimpleFreeList.h
 *
 *  Created on: Nov 22, 2014
 *      Author: root
 */

#ifndef SIMPLEFREELIST_H_
#define SIMPLEFREELIST_H_

#ifdef OLDCPP
#include <cstdatomic>
#else
#include <atomic>
#endif

#include <climits>
#include <GlobalConfig.h>

template<int LISTSIZE>
class SimpleFreeList
{
private:
	atomic_ulong list[LISTSIZE];
	atomic_ulong head;
	atomic_ulong tail;
	const ulong mask;

	void init();
	inline bool isEmptySlot(ulong value) {return ((value & DATAMASK) == FREESLOT);}
public:
	SimpleFreeList();
	~SimpleFreeList();

	bool pushSingle(uint item);
	bool pushMul(uint item);
	bool popSingle(uint& item);
	bool popMul(uint& item);

	inline bool isEmpty() {return head == tail;}
	inline bool isFull() { return (tail - head) >= LISTSIZE; }
};

#endif /* SIMPLEFREELIST_H_ */
