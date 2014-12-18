/*
 * CmmQAlocException.cpp
 *
 *  Created on: Sep 11, 2014
 *      Author: root
 */

#include "CmmQAlocException.h"

CmmQAlocException::CmmQAlocException()
{
	// TODO Auto-generated constructor stub

}

CmmQAlocException::~CmmQAlocException() throw()
{
	// TODO Auto-generated destructor stub
}

const char* CmmQAlocException::what() const throw()
{
	return "No free communication queue available \n";
}
