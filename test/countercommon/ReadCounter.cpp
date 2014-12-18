/*
 * ReadCounter.cpp
 *
 *  Created on: Nov 15, 2014
 *      Author: zf
 */



#include <ShmStore.h>
#include <TestConfig.h>
#include <iostream>
#include <string.h>

using namespace std;

int main()
{
	ShmStore counterStore(sizeof(CounterType), TestConfig::GetCounterFileName(), false);
	CounterType *counters = (CounterType*)counterStore.getShmPtr();

	ulong totalRcvsPerApp[TESTAPPNUM] = {0};
	ulong totalSndsPerApp[TESTAPPNUM] = {0};
//	memset(totalSndsPerApp, 0, sizeof(totalSndsPerApp));
//	ulong totalSnd2 = 0;
	bool allMatched = true;
	for(int i = 0; i < COUNTERNUM; i ++)
	{
//		totalRcv += counters->rcvCounters[i];
		ulong totalSndCounter = 0;
		ulong totalRcvCounter = 0;
		for(int j = 0; j < TESTAPPNUM; j ++)
		{
			totalSndsPerApp[j] += counters->sncCounters[j][i];
			totalSndCounter += counters->sncCounters[j][i];

			totalRcvsPerApp[j] += counters->rcvCounters[j][i];
			totalRcvCounter += counters->rcvCounters[j][i];
//			totalSnd2 += counters->sncCounters2[i];
		}

		if(totalRcvCounter != totalSndCounter
				//(counters->sncCounters1[i] + counters->sncCounters2[i])
				)
		{
			cout << "Unmatched counter " << i << " "
					<< totalRcvCounter << "!= "
					<< totalSndCounter
//					<< counters->sncCounters1[i]
					<< endl;

			allMatched = false;
		}
	}

//	cout << "Total sent " << (totalSnd1 + totalSnd2) << " total received " << totalRcv << endl;
//	cout << "Sent by 1 " << totalSnd1 << " sent by 2 " << totalSnd2 << endl;
	if(allMatched)
	{
		cout << "All counters matched " << endl;
	}
	ulong totalSnd = 0;
	ulong totalRcv = 0;
	for(int i = 0; i < TESTAPPNUM; i ++)
	{
		cout << "Sent by " << i << ": " << totalSndsPerApp[i] << endl;
		totalSnd += totalSndsPerApp[i];
	}
	for(int i = 0; i < TESTAPPNUM; i ++)
	{
		cout << "Received by " << i << ": " << totalRcvsPerApp[i] << endl;
		totalRcv += totalRcvsPerApp[i];
	}
	cout << "Totally sent " << totalSnd << " and received " << totalRcv << endl;
}
