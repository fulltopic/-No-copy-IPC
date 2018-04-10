/*
 * CrashPoints.cc
 *
 *  Created on: Dec 20, 2014
 *      Author: zf
 */




#include <CrashPoints.h>
#include <ShmStore.h>

using namespace std;

const string CrashPoints::fileName("/CrashPointsSHM");
CrashPoints* CrashPoints::instance = NULL;
ShmStore* CrashPoints::shm = NULL;


bool CrashPoints::Init(bool toCreate)
{
	shm = new ShmStore(sizeof(CrashPoints), fileName, toCreate);
	instance = static_cast<CrashPoints*>(shm->getShmPtr());
	return true;
}

CrashPoints* CrashPoints::GetInstance()
{
	cout << "Return instance " << endl;
	return instance;
}


