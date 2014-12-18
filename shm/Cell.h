/*
 * Cell.h
 *
 *  Created on: Sep 7, 2014
 *      Author: root
 */

#ifndef CELL_H_
#define CELL_H_

#include <pthread.h>
#include <climits>

#ifdef OLDCPP
#include <cstdatomic>
#else
#include <atomic>
#endif

#include "GlobalConfig.h"

enum CELLDEFS
{
	RESERVESIZE = ((8 - 1) * sizeof(int)) - (sizeof(atomic_uint) * 2),
	CELLHEADSIZE = 8 * sizeof(int),
};

struct Cell
{
friend class MemStorage;

private:
	Cell(const Cell& copied) = delete;
	Cell operator=(const Cell& copied) = delete;

	bool inited;
	int myIndex;

	void init(int index);

public:
	atomic_uint myTid; //Has to be allocated by monitor
	atomic_uint dstTid;
	//Seemed in receiving T, CAS myTid is necessary
//TODO	char reserve[RESERVESIZE]; To false sharing
	//TODO: Barrier is better
	atomic_int siblings[SIBLINGSIZE];

	inline int getMyIndex() {return myIndex;}

//	Cell(int tMyIndex);
	Cell();
	~Cell();
};

#endif /* CELL_H_ */
