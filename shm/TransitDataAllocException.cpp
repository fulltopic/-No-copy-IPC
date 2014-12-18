/*
 * TransitDataAllocException.cpp
 *
 *  Created on: Sep 26, 2014
 *      Author: root
 */

#include "TransitDataAllocException.h"

TransitDataAllocException::TransitDataAllocException() {
	// TODO Auto-generated constructor stub

}

TransitDataAllocException::~TransitDataAllocException() throw()
{
	// TODO Auto-generated destructor stub
}

const char* TransitDataAllocException::what(void) const throw()
{
	return "No available transit data cell";
}
