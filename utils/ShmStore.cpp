/*
 * ShmStore.cpp
 *
 *  Created on: Sep 7, 2014
 *      Author: root
 */

#include "ShmStore.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <error.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>

ShmStore::ShmStore(int shmSize, const string& shmFileName, bool toCreate)
	: size(shmSize), fileName(shmFileName), fd(-1), shmPtr(NULL), created(toCreate)
{
	init();
}

ShmStore::~ShmStore()
{
	// TODO Auto-generated destructor stub
	if(!destroy())
	{
		//TO trace
	}
}

void ShmStore::initCreate() throw (MemInitException)
{
	int trial = 0;
	stringstream errSs;

	if(shm_unlink(fileName.c_str()))
	{
		cout << "Failed to unlink previous SHM as " << strerror(errno) << " " << errno << endl;
		if(errno != 2)
		{
			return;
		}
	}
    while(trial < 2)
    {
    	fd = shm_open(fileName.c_str(), O_CREAT | O_RDWR| O_EXCL| O_TRUNC, S_IRWXU| S_IRWXG | S_IRWXO);
    	if(fd > 0)
    	{
    		if(ftruncate(fd, size) != 0)
    		{
    			errSs << "Failed to create shared memory with size " << size << ": " << strerror(errno);
    			throw MemInitException(errSs.str());
    		}
    		cout << "Created shared memory " << fileName << endl;
    		break;
    	}else
    	{
    		cout << "Failed to create shm file as " << strerror(errno) << endl;
    		if(shm_unlink(fileName.c_str()))
    		{
    			errSs << "Failed to remove shm as " << strerror(errno);
    			trial = 2;
    		}else
    		{
    			cout << "Previous shm removed " << endl;
    		}
    	}
    	trial ++;
    }

    if(trial >= 2)
    {
            cout << "No create when force create required " << endl;
            throw MemInitException(errSs.str());
    }

    void *memPtr = mmap(NULL, size, PROT_READ| PROT_WRITE, MAP_SHARED, fd, 0);
    if(memPtr == (void*)(-1))
    {
    	errSs << "Failed to map as " << strerror(errno);
    	throw MemInitException(errSs.str());
    }

    shmPtr = memPtr;

    close(fd);
    fd = -1;
}

void ShmStore::initMap() throw(MemInitException)
{
	stringstream errSs;
    fd = shm_open(fileName.c_str(), O_RDWR, S_IRWXU| S_IRWXG | S_IRWXO);
    if(fd <= 0)
    {
            errSs << "Failed to open existing shared memory as " << strerror(errno);
            throw MemInitException(errSs.str());
    }else
    {
            cout << "Mapped to file " << fileName << endl;
    }

    void *memPtr = mmap(NULL, size, PROT_READ| PROT_WRITE, MAP_SHARED, fd, 0);
    if(memPtr == (void*)(-1))
    {
            errSs << "Failed to map as " << strerror(errno);
            throw MemInitException(errSs.str());
    }

    shmPtr = memPtr;
    close(fd);
    fd = -1;
}

void ShmStore::init() throw(MemInitException)
{
	try
	{
		if(!beforeInit())
		{
			throw MemInitException("Failed in beforeInit() \n");
		}

		if(created)
		{
			initCreate();
		}else
		{
			initMap();
		}

		if(!afterInit())
		{
			throw MemInitException("Failed in afterInit() \n");
		}

	}catch(MemInitException& e)
	{
		destroy();
		throw e;
	}

	return;
}

bool ShmStore::destroy()
{
	if(shmPtr != NULL)
	{
		if(created)
		{
			shm_unlink(fileName.c_str());
			shmPtr = NULL;
		}else
		{
			munmap(shmPtr, size);
		}
		shmPtr = NULL;
	}

	if(fd > 0)
	{
		close(fd);
		fd = -1;
	}

	return true;
}

bool ShmStore::beforeInit()
{
	return true;
}

bool ShmStore::afterInit()
{
	return true;
}
