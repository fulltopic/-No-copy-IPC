/*
 * MemInitException.cpp
 *
 *  Created on: Sep 11, 2014
 *      Author: root
 */

#include "MemInitException.h"

MemInitException::MemInitException(): reason("")
{
	// TODO Auto-generated constructor stub

}

MemInitException::MemInitException(const string cause): reason(cause)
{

}

MemInitException::~MemInitException() throw()
{
	// TODO Auto-generated destructor stub
}

const char* MemInitException::what() const throw()
{
	return reason.c_str();
}
