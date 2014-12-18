/*
 * TestSndCnt.h
 *
 *  Created on: Nov 10, 2014
 *      Author: zf
 */

#ifndef TESTSNDCNT_H_
#define TESTSNDCNT_H_

#include <TestAppInterface.h>
#include <ShmStore.h>
#include <TestConfig.h>

class TestSndCnt :public TestAppInterface
{
private:
	ShmStore counterStore;
	CounterType* allCounters;
	ulong* counters;

public:
	TestSndCnt(int appId);
	virtual ~TestSndCnt();

	virtual void routine();
};
#endif /* TESTSNDCNT_H_ */
