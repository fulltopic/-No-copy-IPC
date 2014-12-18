/*
 * Cell.cpp
 *
 *  Created on: Sep 7, 2014
 *      Author: root
 */

#include "Cell.h"
#include "MemStorage.h"

Cell::Cell() : inited(false), myIndex(0), myTid(FREETID), dstTid(FREETID)
{
//	if((myIndex & SIBLINGSIZE) == 0)
//	{
//		for(int i = 0; i < SIBLINGSIZE; i ++)
//		{
//			siblings[i] = (i + 1) + myIndex;
//		}
//	}else
//	{
//		for(int i = 0; i < SIBLINGSIZE; i ++)
//		{
//			siblings[i] = INVALIDCELL;
//		}
//	}
}

Cell::~Cell()
{
	// TODO Auto-generated destructor stub
}

void Cell::init(int index)
{
	if(inited)
	{
		return;
	}

	this->myIndex = index;
	if((myIndex & SIBLINGSIZE) == 0)
	{
		for(int i = 0; i < SIBLINGSIZE; i ++)
		{
			siblings[i] = (i + 1) + myIndex;
		}
	}else
	{
		for(int i = 0; i < SIBLINGSIZE; i ++)
		{
			siblings[i] = INVALIDCELL;
		}
	}

	inited = true;
	return;
}
