/*
 * TestRcver.cpp
 *
 *  Created on: Sep 29, 2014
 *      Author: root
 */

#include "TestRcver.h"
#include "TestConfig.h"

#include <iostream>
#include <string>
#include <signal.h>

using namespace std;

TestRcver::TestRcver(int appId): TestAppInterface(appId)
{
	// TODO Auto-generated constructor stub

}

TestRcver::~TestRcver() {
	// TODO Auto-generated destructor stub
}

void TestRcver::routine()
{
	cout << "Is running " << isRunning << endl;
	while(isRunning)
	{
		int *stamp = NULL;

		while(stamp == NULL)
		{
			if(!isRunning)
			{
				break;
			}
			void* buf = proxy.recv();
			if(buf != NULL)
			{
				stamp = (int*)buf;
			}
		}

		if(stamp != NULL)
		{
			int senderIndex = *(stamp + 1);
			*(stamp + 1) = *stamp;

			proxy.send((void*)stamp, senderIndex);
		}
	}
}

TestRcver *tester = NULL;

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

	cout << "Receiver get appId " << appId << " coreId " << coreId << endl;
	tester = new TestRcver(appId);
	TestAppInterface::Start(tester, coreId);

	cout << "End of receiver" << endl;

	return 0;
}
