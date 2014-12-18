/*
 * CellBlock.cpp
 *
 *  Created on: Sep 7, 2014
 *      Author: root
 */

#include "CellBlock.h"
#include <string.h>

//TODO: Maybe the constructor is also prohibited as all memories had been initiated
CellBlock::CellBlock(int tMyIndex): myIndex(tMyIndex), myTid(FREETID), cellsIndex(0)
{
	// TODO Auto-generated constructor stub
	memset(cells, 0, sizeof(cells));
}

//Seemed can not define destructor as the memory is on SHM
CellBlock::~CellBlock()
{
	// TODO Auto-generated destructor stub
}

bool CellBlock::getMemIndex(int& memIndex)
{
	if(isEmpty())
	{
		return false;
	}else
	{
		memIndex = cells[cellsIndex];
		cellsIndex ++;
		return true;
	}
}

bool CellBlock::setMemIndex(int memIndex)
{
	if(isFull())
	{
		return false;
	}else
	{
		cellsIndex --;
		cells[cellsIndex] = memIndex;
		return true;
	}
}


