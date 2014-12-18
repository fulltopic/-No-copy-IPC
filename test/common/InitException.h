/*
 * InitException.h
 *
 *  Created on: Oct 13, 2014
 *      Author: root
 */

#ifndef INITEXCEPTION_H_
#define INITEXCEPTION_H_

#include <exception>
#include <string>

using namespace std;

class InitException : public exception
{
private:
	const string cause;
public:
	InitException();
	InitException(string myCause);
	virtual ~InitException() throw();

	virtual const char* what() const throw();
};

#endif /* INITEXCEPTION_H_ */
