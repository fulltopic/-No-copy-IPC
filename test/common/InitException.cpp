/*
 * InitException.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: root
 */

#include "InitException.h"
#include <sstream>
#include <string.h>
#include <errno.h>

using namespace std;

InitException::InitException(): cause("")
{
	// TODO Auto-generated constructor stub

}
InitException::InitException(string myCause): cause(myCause)
{

}

InitException::~InitException() throw()
{
	// TODO Auto-generated destructor stub
}

const char* InitException::what() const throw()
{
	if(cause.length() <= 0)
	{
		stringstream buff;
		buff << "Failed to execute process as " << strerror(errno) << endl;
		return buff.str().c_str();
	}else
	{
		return cause.c_str();
	}
}

