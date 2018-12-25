/*
 * TestRcvCnt.h
 *
 *  Created on: Nov 10, 2014
 *      Author: zf
 */

#ifndef TESTRCVCNT_H_
#define TESTRCVCNT_H_

#include <TestAppInterface.h>
#include <utils/ShmStore.h>
#include <TestConfig.h>

class TestRcvCnt :public TestAppInterface
{
private:
	ShmStore counterStore;
	CounterType* allCounters;
	ulong* counters;

public:
	TestRcvCnt(int appId);
	virtual ~TestRcvCnt();

	virtual void routine();
};

#endif /* TESTRCVCNT_H_ */
