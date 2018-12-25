
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
#include <CrashPoints.h>

#include <string.h>
#include <errno.h>

#include "InitException.h"
#include <thread>

using namespace std;

#ifdef OLDCPP
const char* exePathes[] =
{
		"/mnt/nfs/home/zf/workspace/test_4/bin/test_rcvcnt",
		"/mnt/nfs/home/zf/workspace/test_4/bin/test_sndcnt",
		"/mnt/nfs/home/zf/workspace/test_4/bin/test_sndcnt",
		"/mnt/nfs/home/zf/workspace/test_4/bin/test_sndcnt",
		"/mnt/nfs/home/zf/workspace/test_4/bin/test_sndcnt",
		"/mnt/nfs/home/zf/workspace/test_4/bin/test_sndcnt",
//		"/mnt/nfs/home/zf/workspace/test_4/bin/test_sndcnt",
};
#else
const char* exePathes[] =
{
		"/home/zf/workspace_cpp/test_5/bin/test_rcvrelease",
		"/home/zf/workspace_cpp/test_5/bin/test_sndrelease",
//		"/home/zf/workspace_cpp/test_5/bin/test_sndcnt",
//		"/home/zf/workspace_cpp/test_4/bin/test_sndcnt",
};
#endif

char* argv[][4] =
{
		{"test_rcvrelease", "10", "3", NULL},
		{ "test_sndrelease", "1", "1", NULL},
		{ "test_sndrelease", "2", "2", NULL},
		{ "test_sndrelease", "3", "4", NULL},
		{ "test_sndrelease", "4", "5", NULL},
		{ "test_sndrelease", "5", "6", NULL},
//		{ "test_sndcnt", "3", "2", NULL},
};

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
	int pNum = sizeof(exePathes) / sizeof(const char*);

	for(int i = 0; i < pNum; i ++)
	{
		try
		{
			initProcess(exePathes[i], argv[i], pids[i]);
			cout << "----------------> " << "Init process " << i << " pid " << pids[i] << endl;
			if(i == 0)
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

	for(int i = 0; i < pNum; i ++)
	{
		cout << "===============> " << pids[i] << endl;
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

	CrashPoints::Init(true);
	return initProcesses();
}


int main()
{
//	if(daemon(1, 1) != 0)
//	{
//		cout << "Failed to set monitor as daemon" << endl;
//		return -1;
//	}

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

}
