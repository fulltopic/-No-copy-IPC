/*
 * CrashPoints.h
 *
 *  Created on: Dec 20, 2014
 *      Author: zf
 */

#ifndef CRASHPOINTS_H_
#define CRASHPOINTS_H_

#include <atomic>

#include <stdlib.h>
#include <string>
#include "utils/ShmStore.h"



class CrashPoints
{
private:
	const static std::string fileName;
	static ShmStore *shm;
	static CrashPoints* instance;

	CrashPoints() = default;

public:
	static CrashPoints* GetInstance();
	static bool Init(bool toCreate);

//Release
	bool CrashInPoint21;
	bool CrashInPoint22;
	bool CrashInPoint23;
	bool CrashInPoint24;
	bool CrashInPoint25;
	bool CrashInPoint26;

//Allocation
	bool CrashInPoint11;
	bool CrashInPoint12;
	bool CrashInPoint13;
	bool CrashInPoint14;
	bool CrashInPoint15;
	bool CrashInPoint16;

	std::atomic_bool StopAllFlag;
	std::atomic_int StopAllBarrier;

	inline void Crash(bool flag)
	{
		if(flag)
		{
			abort();
		}
	}
};

#endif /* CRASHPOINTS_H_ */
