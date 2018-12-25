/*
 * ShowCells.cpp
 *
 *  Created on: Nov 15, 2014
 *      Author: zf
 */




#include <utils/ShmStore.h>
#include <shm/MemStorage.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	int cmd = atoi(argv[1]);

	ShmStore shmMemStore( sizeof(MemStorage), MemStorage::ShmName, false);
	void* ptr = shmMemStore.getShmPtr();
	MemStorage* memStorePtr = (MemStorage*)ptr;

	switch(cmd)
	{
	case 1:
		memStorePtr->printCells();
		break;
	case 2:
		memStorePtr->printTransitCells();
		break;
	case 3:
		memStorePtr->printGlobalFreeList();
		break;
	default:
		cout << "Invalid cmd " << endl;
		break;
	}

}
