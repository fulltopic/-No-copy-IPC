/*
 * CellBlock.h
 *
 *  Created on: Sep 7, 2014
 *      Author: root
 */

#ifndef CELLBLOCK_H_
#define CELLBLOCK_H_

#include "GlobalConfig.h"

#ifdef OLDCPP
#include <cstdatomic>
#else
#include <atomic>
#endif
//Pre-declare
class Monitor;

//Set and get are supposed to be manipulated by single thread
class CellBlock
{
friend class Monitor;

private:
	const int myIndex;
	int cells[CELLSIZE];
	//If dead between append to app and assigned new tid, the myTid still shows free.
	//While monitor would not monitor free cell. And the attached cells would be collected in collection of local free list
	atomic_int myTid;
	int cellsIndex; //points to cell which readable

	CellBlock(const CellBlock& copied) = delete;
	CellBlock& operator=(const CellBlock& copied) = delete;

public:
	CellBlock(int tMyIndex);
	~CellBlock();

	inline bool isEmpty() const {return cellsIndex >= CELLSIZE;}
	inline bool isFull() const {return cellsIndex == 0; }
	bool getMemIndex(int& memIndex);

protected:
	bool setMemIndex(int memIndex);
};

#endif /* CELLBLOCK_H_ */
