/*
 * MemInitException.h
 *
 *  Created on: Sep 11, 2014
 *      Author: root
 */

#ifndef MEMINITEXCEPTION_H_
#define MEMINITEXCEPTION_H_

#include <exception>
#include <string>

using namespace std;

class MemInitException: public exception
{
private:
	const string reason;
public:
	MemInitException();
	MemInitException(const string cause);
	virtual ~MemInitException() throw();

	virtual const char* what() const throw();
};

#endif /* MEMINITEXCEPTION_H_ */
