/*
 * ShmStore.h
 *
 *  Created on: Sep 7, 2014
 *      Author: root
 */

#ifndef SHMSTORE_H_
#define SHMSTORE_H_

#include <string>
#include "shm/MemInitException.h"

using namespace std;

class ShmStore
{
friend class MemStorage;

private:
	const int size;
	const string fileName;
	int fd;
	void* shmPtr;
	const bool created;

	void initCreate() throw(MemInitException);
	void initMap() throw(MemInitException);
protected:
	int getFd();
	bool destroy();

public:
	ShmStore(int shmSize, const string& fileName, bool toCreate);
	virtual ~ShmStore();

	virtual bool beforeInit();
	void init() throw(MemInitException);
	virtual bool afterInit();

	inline void* getShmPtr() { return shmPtr;};
	inline int getSize() const {return size;};
	inline const string getFileName() const { return fileName;};
};

#endif /* SHMSTORE_H_ */
