/*
 * TestRcvCnt.cpp
 *
 *  Created on: Nov 10, 2014
 *      Author: zf
 */

#include "TestRcvCnt.h"
#include "TestConfig.h"

#include <iostream>
#include <string>
#include <signal.h>
#include <string.h>

using namespace std;


TestRcvCnt::TestRcvCnt(int appId): TestAppInterface(appId),
					counterStore(sizeof(CounterType), TestConfig::GetCounterFileName(), false),
					allCounters(NULL)
{
	allCounters = (CounterType*)counterStore.getShmPtr();
	counters = allCounters->rcvCounters[appId];
	memset(counters, 0, sizeof(int) * COUNTERNUM);
}

TestRcvCnt::~TestRcvCnt()
{
	// TODO Auto-generated destructor stub
}

void TestRcvCnt::routine()
{
	cout << "Is running " << isRunning << endl;
	while(isRunning)
	{
		int counter = COUNTERNUM;

		while(counter == COUNTERNUM)
		{
			if(!isRunning)
			{
				break;
			}
			void* buf = proxy.recv();
			if(buf != NULL)
			{
				counter = *((int*)buf);
			}

			proxy.releaseMem(buf);
		}

//		if(counter != NULL)
//		{
//			int senderIndex = *(counter + 1);
			TestConfig::CountCounter(counters, counter);
//		}
	}
	allCounters->stopped[proxy.myAppId] = true;
}

TestRcvCnt *tester = NULL;

void stopSig(int signum)
{
	tester->stop();
	cout << "To stop receiver " << endl;
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

	cout << "Receiver get appId " << appId << " coreId " << coreId << endl;
	tester = new TestRcvCnt(appId);
	TestAppInterface::Start(tester, coreId);

	cout << "End of receiver" << endl;

	return 0;
}
