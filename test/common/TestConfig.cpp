/*
 * TestConfig.cpp
 *
 *  Created on: Nov 10, 2014
 *      Author: zf
 */


#include <TestConfig.h>
#include <iostream>

using namespace std;

string TestConfig::GetCounterFileName(void)
{
	return "TestConfigSHM";
}

void TestConfig::CountCounter(ulong* const counters, int counter)
{
	if(counter < 0 || counter >= COUNTERNUM)
	{
		cout << "Received unexpected counter " << counter << endl;
		return;
	}else
	{
		counters[counter] ++;
	}
}
