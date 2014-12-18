/*
 * AppProxyInitException.h
 *
 *  Created on: Oct 13, 2014
 *      Author: root
 */

#ifndef APPPROXYINITEXCEPTION_H_
#define APPPROXYINITEXCEPTION_H_

#include <exception>
#include <string>
using namespace std;

class AppProxyInitException: public exception
{
private:
	string reason;

public:
	AppProxyInitException();
	AppProxyInitException(string r);
	virtual ~AppProxyInitException() throw();

	virtual const char* what() const throw();
};

#endif /* APPPROXYINITEXCEPTION_H_ */
