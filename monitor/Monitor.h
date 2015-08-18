/*
 * Monitor.h
 *
 *  Created on: Sep 7, 2014
 *      Author: root
 */

#ifndef MONITOR_H_
#define MONITOR_H_

#include <queue>
#include <thread>
#include "GlobalConfig.h"
#include <sys/types.h>

using namespace std;

//Supposed single. Not wrapped by GetInstance to remove extra overhead
class Monitor
{
public:
	Monitor();
	~Monitor();

	Monitor(const Monitor& copied) = delete;
	Monitor& operator=(const Monitor& copied) = delete;

//	void toCleanDeadTid(const uint tid);
	void toCleanDeadPid(const pid_t pid);

	void runRoutine();
	void stopCollector();
	void startCollector();

	static void threadMain(Monitor* monitor);

private:
//	Cell *cells;
	queue<uint> deadTids;
//	queue<pid_t> deadPids;
	void cleanDeadTid(const uint tid);

	void cleanCmmQs(const uint tid);
	void cleanCells(const uint tid);
	void cleanTransitCell(const uint cellId, const uint tid);
	void cleanTransitCells(const uint tid);
	void cleanBlockCells(const uint tid);
	void cleanSingleCells(const uint tid);
	void mergeCell(int& blockId, int& sibIndex, int cellId);
	void clearAppResource(const uint tid);

	bool isInOverallAllocCell(const uint cellId);

	bool isRunning;

	class Collector
	{
	public:
		Collector(Monitor& m);
		~Collector();

		void operator()(void);
	private:
		Monitor& monitor;
	};

	thread *collector;
};

#endif /* MONITOR_H_ */
