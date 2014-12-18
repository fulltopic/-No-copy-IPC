/*
 * TestAppInterface.h
 *
 *  Created on: Sep 29, 2014
 *      Author: root
 */

#ifndef TESTAPPINTERFACE_H_
#define TESTAPPINTERFACE_H_

#include <AppProxy.h>

class TestAppInterface
{
protected:
	AppProxy proxy;
	bool isRunning;
	bool stopped;

public:
	TestAppInterface(int appId);
	virtual ~TestAppInterface();

	virtual void routine() = 0;

	inline void stop() {isRunning = false;};

	static void Start(TestAppInterface* app, const int coreId);

	inline int getMyAppId() const { return proxy.myAppId; }
	inline uint getMyTid() const { return proxy.myTid; }
	inline bool isStopped() const { return stopped; }
};

#endif /* TESTAPPINTERFACE_H_ */
