/*
 * CommQueue.h
 *
 *  Created on: Sep 7, 2014
 *      Author: root
 */

#ifndef COMMQUEUE_H_
#define COMMQUEUE_H_

#include "GlobalConfig.h"

#ifdef OLDCPP
#include <cstdatomic>
#else
#include <atomic>
#endif

class CmmQueue
{
friend class Monitor;
friend class MemStorage;

private:
	atomic_ulong slots[GLOBALQUECAP];

	//TODO: atomic type has property of volatile?
	atomic_uint head;
	atomic_uint tail;

	//TODO: Set the tid;
	atomic_uint myTid;

	int myIndex;
	//TODO: Set as global reference
//	MemStorage& globalMem;
//	Cell *const cells;
public:
	virtual ~CmmQueue();

	CmmQueue(const CmmQueue& copied) = delete;
	CmmQueue& operator=(const CmmQueue& copied) = delete;

	//TODO： Ensure reference is not necessary
	bool pop(volatile ulong& cellId);
	bool push(int cellId);

	//TODO: Reorganize sequence
//	inline bool isFull() const {return (tail - head) >= GLOBALQUECAP;}
	bool isFull() const;
	inline bool isEmpty() const { return head == tail; }

	inline uint getMyTid() const { return myTid;}

	bool contains(int cellId) const;

	inline int getMyIndex() { return myIndex;}

protected:
	CmmQueue();

	//Guaranteed no race
	void cleanup();
};

#endif /* COMMQUEUE_H_ */
