/*
 * TestSndCnt.cpp
 *
 *  Created on: Nov 10, 2014
 *      Author: zf
 */

#include "TestSndCnt.h"
#include "TestConfig.h"
#include <iostream>
#include <string>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include <CrashPoints.h>

TestSndCnt::TestSndCnt(int appId): TestAppInterface(appId),
			counterStore(sizeof(CounterType), TestConfig::GetCounterFileName(), false),
			allCounters(NULL)
{
	allCounters = (CounterType*)counterStore.getShmPtr();
	counters = allCounters->sncCounters[appId];
//	if(appId == 1)
//	{
//		cout << "Sender 1" << endl;
//		counters = allCounters->sncCounters1;
//	}else
//	{
//		cout << "Sender 2" << endl;
//		counters = allCounters->sncCounters2;
//	}
	memset(counters, 0, sizeof(int) * COUNTERNUM);
}

TestSndCnt::~TestSndCnt()
{
	// TODO Auto-generated destructor stub
}

void TestSndCnt::routine()
{
	srand((uint)time(NULL));
	uint64_t begin = rte_rdtsc();
	int index = 0;
	int max = 0;
	int min = INT_MAX;
	int maxIndex = -1;
	int maxBefore = 0;
	uint64_t maxBeforeIndex = 0;
	cout << "Sender get mytid " << proxy.myTid << endl;

//	int stopIndex = rand() % TESTTOTAL;
//	cout << "!!!!!!!!!!!!! To crash at " << stopIndex << " total " << TESTTOTAL << endl;

	while(index < TESTTOTAL)
	{
		int volatile sleepGap = 0;
		for(; sleepGap < SLEEPCOUNTER; sleepGap ++)
		{

		}

		uint64_t singleBegin = rte_rdtsc();
		index ++;
		void* buff = proxy.allocMem();
		if(buff == NULL)
		{
			cout << "Failed to allocate buffer " << index << endl;
//			abort();
			getchar();
			continue;
		}

		int counter = rand() % COUNTERNUM;
		int *stamp = (int*)buff;
		*stamp = counter;
		uint64_t singleBeforeSend = rte_rdtsc();
		int beforeDelta = singleBeforeSend - singleBegin;
		if(beforeDelta > maxBefore)
		{
			maxBefore = beforeDelta;
			maxBeforeIndex = index;
		}

		if(CrashPoints::GetInstance()->StopAllFlag)
		{
			CrashPoints::GetInstance()->StopAllBarrier.fetch_sub(1);
			while(CrashPoints::GetInstance()->StopAllFlag)
			{
				sleep(1);
			}
		}
		if(!proxy.send(stamp, RECEIVER))
		{
//			cout << "Failed to send message " << endl;
			proxy.releaseMem(buff);
			continue;
		}else
		{
			TestConfig::CountCounter(counters, counter);
//			cout << "Send a message to receiver " << endl;
		}



		uint64_t singleEnd = rte_rdtsc();
		int singleDelta = (singleEnd - singleBegin) / 2600;
		if(singleDelta > max)
		{
			max = singleDelta;
			maxIndex = index;
		}
		if(singleDelta < min)
		{
			min = singleDelta;
		}
	}
	uint64_t end = rte_rdtsc();
	uint64_t delta = (end - begin);
	uint64_t deltaUs = delta / CPUHZ;
	uint64_t ave = (deltaUs / index);
	cout << "Roundtrip " << index << " in " << delta << " --> " << deltaUs  << endl;
	cout << "Average = " << ave << " min " << min << " max " << max << " in " << maxIndex << endl;
	cout << "Max before " << (maxBefore / CPUHZ) << ":" << maxBeforeIndex << endl;

	stopped = true;

	allCounters->stopped[proxy.myAppId] = true;
	cout << "Set stopped " << proxy.myAppId << endl;
}


TestSndCnt *tester = NULL;

void stopSig(int signum)
{
	cout << "To stop sender " << endl;
	tester->stop();
}

int main(int argc, char** argv)
{
	if(argc < 3)
	{
		cout << "More arguments " << endl;
		return -1;
	}

	int appId = atoi(argv[1]);
	int coreId = atoi(argv[2]);

	signal(SIGUSR1, stopSig);
	CrashPoints::Init(false);

	tester = new TestSndCnt(appId);
	TestAppInterface::Start(tester, coreId);

	cout << "End of sender" << endl;

	return 0;
}

