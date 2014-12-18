/*
 * TestSnder.cpp
 *
 *  Created on: Sep 29, 2014
 *      Author: root
 */

#include "TestSnder.h"
#include "TestConfig.h"
#include <iostream>
#include <string>
#include <signal.h>

TestSnder::TestSnder(int appId): TestAppInterface(appId)
{
	// TODO Auto-generated constructor stub

}

TestSnder::~TestSnder()
{
	// TODO Auto-generated destructor stub
}

void TestSnder::routine()
{
	uint64_t begin = rte_rdtsc();
	int index = 0;
	int max = 0;
	int min = INT_MAX;
	int maxIndex = -1;
	while(isRunning)
	{
		uint64_t singleBegin = rte_rdtsc();
		index ++;
		void* buff = proxy.allocMem();
		if(buff == NULL)
		{
			cout << "Failed to allocate buffer " << endl;
			getchar();
			continue;
		}
		int *stamp = (int*)buff;
		*stamp = index;
		*(stamp + 1) = proxy.myAppId;

		if(!proxy.send(stamp, RECEIVER))
		{
			cout << "Failed to send message " << endl;
			continue;
		}else
		{
//			cout << "Send a message to receiver " << endl;
		}

		int* rcvStamp = NULL;
		while(rcvStamp == NULL)
		{
			rcvStamp = (int*)proxy.recv();
			if(!isRunning)
			{
				break;
			}
		}
//		cout << "Received roundtrip message " << endl;

//		long roundStamp = 2;


		if(rcvStamp == NULL)
		{
			continue;
		}
		if(*(rcvStamp + 1) != index)
		{
			cout << "Get unexpected message " << endl;
			getchar();
		}

		proxy.releaseMem((void*)rcvStamp);
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
	uint64_t deltaUs = delta / 2600;
	uint64_t ave = (deltaUs / index);
	cout << "Roundtrip " << index << " in " << delta << " --> " << deltaUs  << endl;
	cout << "Average = " << ave << " min " << min << " max " << max << " in " << maxIndex << endl;
}


TestSnder *tester = NULL;

void stopSig(int signum)
{
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

	tester = new TestSnder(appId);
	TestAppInterface::Start(tester, coreId);

	cout << "End of sender" << endl;

	return 0;
}

