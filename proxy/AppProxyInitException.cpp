/*
 * AppProxyInitException.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: root
 */

#include "AppProxyInitException.h"

AppProxyInitException::AppProxyInitException(): reason("")
{
	// TODO Auto-generated constructor stub
}

AppProxyInitException::AppProxyInitException(string r): reason(r)
{

}


AppProxyInitException::~AppProxyInitException() throw()
{
	// TODO Auto-generated destructor stub
}

const char* AppProxyInitException::what() const throw()
{
	return reason.c_str();
}

