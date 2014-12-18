/*
 * TestRcver.h
 *
 *  Created on: Sep 29, 2014
 *      Author: root
 */

#ifndef TESTRCVER_H_
#define TESTRCVER_H_

#include "TestAppInterface.h"

class TestRcver :public TestAppInterface
{
public:
	TestRcver(int appId);
	virtual ~TestRcver();

	virtual void routine();
};

#endif /* TESTRCVER_H_ */
