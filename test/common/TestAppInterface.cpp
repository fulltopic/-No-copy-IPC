/*
 * TestAppInterface.cpp
 *
 *  Created on: Sep 29, 2014
 *      Author: root
 */

#include "TestAppInterface.h"
//#define __USE_GNU
#include <sched.h>
#include <pthread.h>

TestAppInterface::TestAppInterface(int appId): proxy(appId), isRunning(true), stopped(false)
{
	// TODO Auto-generated constructor stub

}

TestAppInterface::~TestAppInterface()
{
	// TODO Auto-generated destructor stub
}

void TestAppInterface::Start(TestAppInterface* app, const int coreId)
{
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(coreId, &cpuset);
	pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
	app->routine();
}


