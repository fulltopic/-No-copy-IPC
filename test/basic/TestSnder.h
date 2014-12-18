/*
 * TestSnder.h
 *
 *  Created on: Sep 29, 2014
 *      Author: root
 */

#ifndef TESTSNDER_H_
#define TESTSNDER_H_

#include "TestAppInterface.h"

class TestSnder: public TestAppInterface
{
public:
	TestSnder(int appId);
	virtual ~TestSnder();

	virtual void routine();
};

#endif /* TESTSNDER_H_ */
