
#include <Monitor.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <iostream>
#include <sys/wait.h>
#include "MemStorage.h"

#include <string.h>
#include <errno.h>

#include "InitException.h"
#include <thread>

using namespace std;

const char* exePathes[] =
{
		"/home/zf/workspace_cpp/test_4/bin/test_rcv",
		"/home/zf/workspace_cpp/test_4/bin/test_snd",
		"/home/zf/workspace_cpp/test_4/bin/test_snd",
//		"/home/zf/workspace_cpp/test_4/bin/test_snd",
//		"/home/zf/workspace/test_4/bin/",
};

char* argv[][4] =
{
		{"test_rcv", "10", "2", NULL},
		{ "test_snd", "0", "1", NULL},
		{ "test_snd", "1", "3", NULL},
//		{ "test_snd", "2", "12", NULL},
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
			cout << "----------------> " << "Init process " << i << endl;
			initProcess(exePathes[i], argv[i], pids[i]);
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
	if(daemon(1, 1) != 0)
	{
		cout << "Failed to set monitor as daemon" << endl;
		return -1;
	}

	monitor = new Monitor();

	if(!init())
	{
		cout << "Failed to init test " << endl;
		return -1;
	}

	thread monitorT(Monitor::threadMain, monitor);

	sleep(10);
	int pNum = sizeof(exePathes) / sizeof(const char*);
	for(int i = pNum - 1; i >= 0; i --)
	{
		if(pids[i] > 0)
		{
			cout << "To kill " << pids[i] << endl;
			kill(pids[i], SIGUSR1);
		}
	}

	while(1)
	{
		sleep(1);
	}
}
