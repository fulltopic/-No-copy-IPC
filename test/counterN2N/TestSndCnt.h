/*
 * TestSndCnt.h
 *
 *  Created on: Nov 10, 2014
 *      Author: zf
 */

#ifndef TESTSNDCNT_H_
#define TESTSNDCNT_H_

#include <TestAppInterface.h>
#include <utils/ShmStore.h>
#include <TestConfig.h>

class TestSndCnt :public TestAppInterface
{
private:
	ShmStore counterStore;
	CounterType* allCounters;
	ulong* counters;
	int rcvNum;

public:
	TestSndCnt(int appId, int myRcvNum);
	virtual ~TestSndCnt();

	virtual void routine();
};
#endif /* TESTSNDCNT_H_ */
