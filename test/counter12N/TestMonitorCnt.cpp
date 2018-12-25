
#include <monitor/Monitor.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <iostream>
#include <sys/wait.h>
#include <shm/MemStorage.h>
#include <TestConfig.h>
#include <utils/ShmStore.h>

#include <string.h>
#include <errno.h>

#include "InitException.h"
#include <thread>

#include "TestConfig.h"

using namespace std;

//#ifdef OLDCPP
//const char* exePathes[] =
//{
//		"/mnt/nfs/home/zf/workspace/test_4/bin/test_rcvcnt12n",
//		"/mnt/nfs/home/zf/workspace/test_4/bin/test_rcvcnt12n",
//		"/mnt/nfs/home/zf/workspace/test_4/bin/test_sndcnt12n",
////		"/mnt/nfs/home/zf/workspace/test_4/bin/test_sndcnt12n",
//};
//#else
//const char* exePathes[] =
//{
//		"/home/zf/workspace_cpp/test_5/bin/test_rcvcnt12n",
//		"/home/zf/workspace_cpp/test_5/bin/test_rcvcnt12n",
//		"/home/zf/workspace_cpp/test_5/bin/test_sndcnt12n",
////		"/home/zf/workspace_cpp/test_4/bin/test_sndcnt12n",
//};
//#endif
//
char* argv[][ARGNUM] =
{
		{ "test_rcvcnt12n", "10", "3", NULL},
		{ "test_rcvcnt12n", "11", "1", NULL},
		{ "test_sndcnt12n", "2", "2", NULL},
//		{ "test_sndcnt12n", "3", "2", NULL},
};

char exePathes[PROCARGNUM][PATHLEN];
//char* argv[TestConfig::PROCARGNUM][TestConfig::ARGNUM];
const char* rcvName = "test_rcvcnt12n";
const char* sndName = "test_sndcnt12n";

void initProcArgs()
{
	for(int i = 0; i < PROCARGNUM; i ++)
	{
		memset(exePathes[i], 0, PATHLEN);
	}

	snprintf(exePathes[0], PATHLEN, "%s%s", TESTHOME, rcvName);
	snprintf(exePathes[1], PATHLEN, "%s%s", TESTHOME, rcvName);
	snprintf(exePathes[2], PATHLEN, "%s%s", TESTHOME, sndName);

//	argv[0] = {rcvName, "10", "3", NULL};
//	argv[1] = {rcvName, "11", "1", NULL};
//	argv[2] = {sndName, "2", "2", NULL};
}



pid_t pids[sizeof(exePathes) / sizeof(const char*)] = {0};

void initProcess(const char* filePath, char* const pArgv[], pid_t& pid) throw(InitException)
{
	cout << "To init process " << filePath << "with args " ;
	for(int i = 0; i < 3; i ++)
	{
		cout << pArgv[i] << " ,";
	}
	cout << endl;
	int newProcess = fork();
	if(newProcess < 0)
	{
		throw InitException();
	}else if(newProcess == 0)
	{
		if(execv(filePath, pArgv) != 0)
		{
			throw InitException();
		}
	}
	cout << "Initiated process " << pArgv[0] << endl;
	pid = newProcess;
}

bool initProcesses()
{
	initProcArgs();
	for(int i = 0; i < PROCARGNUM; i ++)
	{
		if(argv[i][0] == NULL)
		{
			break;
		}

		cout << "---------------------> To init file path " << exePathes[i] << endl;
		try
		{
			initProcess(exePathes[i], argv[i], pids[i]);
			cout << "----------------> " << "Init process " << i << " pid " << pids[i] << endl;
			if(i == 1)
			{
				sleep(5);
			}
		}catch(InitException& e)
		{
			cout << e.what() << endl;
			return false;
			//TODO: Clean up
		}
	}

	return true;
}

Monitor *monitor = NULL;
void exitProcess(int sigNum)
{
	int status = 0;


	pid_t terminatedPid = waitpid(-1, &status, WNOHANG | WUNTRACED);
	while(terminatedPid > 0)
	{
		cout << "To clean pid " << terminatedPid << endl;
		monitor->toCleanDeadPid(terminatedPid);

		terminatedPid = waitpid(-1, &status, WNOHANG | WUNTRACED);
	}
}

bool init()
{
	if(signal(SIGCHLD, exitProcess) == SIG_ERR)
	{
		cout << "Failed to set SIGCHLD action as " << strerror(errno) << endl;
		return false;
	}
	return initProcesses();
}


int main()
{
//	if(daemon(1, 1) != 0)
//	{
//		cout << "Failed to set monitor as daemon" << endl;
//		return -1;
//	}

	cout << "==========================> TESTTESTTEST \n";
	ShmStore counterStore(sizeof(CounterType), TestConfig::GetCounterFileName(), true);
	CounterType *counters = (CounterType*)counterStore.getShmPtr();
	memset(counters, 0, sizeof(CounterType));
//	memset(counters->stopped, 0, sizeof(bool) * TESTPROCNUM);

	monitor = new Monitor();

	if(!init())
	{
		cout << "Failed to init test " << endl;
		return -1;
	}

	monitor->threadMain(monitor);
//	thread monitorT(Monitor::threadMain, monitor);
//
//	sleep(30);
//	int pNum = sizeof(exePathes) / sizeof(const char*);
//	for(int i = pNum - 1; i >= 0; i --)
//	{
//		int appId = atoi(argv[i][1]);
//		if(pids[i] > 0)
//		{
//			cout << "To kill " << pids[i] << endl;
//			kill(pids[i], SIGUSR1);
//			do
//			{
//				sleep(1);
//			}while(!counters->stopped[appId]);
//		}
//	}

//	while(1)
//	{
//		sleep(1);
//	}
}
