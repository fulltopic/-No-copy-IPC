/*
 * FreeListChecker.cpp
 *
 *  Created on: Dec 20, 2014
 *      Author: zf
 */

#include "FreeListChecker.h"
#include <CrashPoints.h>
#include <shm/MemStorage.h>

#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

void FreeListChecker::check(const int num)
{
	CrashPoints::GetInstance()->StopAllBarrier.fetch_add(num);
	CrashPoints::GetInstance()->StopAllFlag = true;

	while(CrashPoints::GetInstance()->StopAllBarrier != 0)
	{
		sleep(1);
	}

	MemStorage::GetInstance(false).checkNoDup();
	MemStorage::GetInstance(false).checkNoMiss();

	CrashPoints::GetInstance()->StopAllFlag = false;
}

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		cout << "Input participants number " << endl;
		return -1;
	}

	int num = atoi(argv[1]);

	CrashPoints::Init(false);
	FreeListChecker tester;
	tester.check(num);
}
