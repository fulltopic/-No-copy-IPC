/*
 * TestConfig.h
 *
 *  Created on: Sep 29, 2014
 *      Author: root
 */

#ifndef TESTCONFIG_H_
#define TESTCONFIG_H_

#include<string>

enum APPIDS
{
	SENDER = 1,
	RECEIVER = 10,
};

enum TESTCOUNTER
{
	COUNTERNUM = 1 << 6,
	SLEEPCOUNTER = 1000,
	TESTPROCNUM = 16,
	TESTTOTAL = 1024 * 16 * 1024,
	CPUHZ = 2600,
	TESTAPPNUM = 32,
};

struct CounterType
{
	ulong rcvCounters[TESTAPPNUM][COUNTERNUM];
	ulong sncCounters[TESTAPPNUM][COUNTERNUM];
//	int sncCounters2[COUNTERNUM];
	bool stopped[TESTPROCNUM];
};

class TestConfig
{
private:
	TestConfig() = delete;
	TestConfig(const TestConfig&) = delete;
	TestConfig& operator= (const TestConfig&) = delete;
public:
	static std::string GetCounterFileName();
	static void CountCounter(ulong* const counters, int counter);
};
#endif /* TESTCONFIG_H_ */
