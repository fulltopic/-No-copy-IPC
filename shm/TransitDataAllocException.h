/*
 * TransitDataAllocException.h
 *
 *  Created on: Sep 26, 2014
 *      Author: root
 */

#ifndef TRANSITDATAALLOCEXCEPTION_H_
#define TRANSITDATAALLOCEXCEPTION_H_

#include <exception>

using namespace std;

class TransitDataAllocException : public exception
{
public:
	TransitDataAllocException();
	virtual ~TransitDataAllocException() throw();

	virtual const char* what() const throw();
};

#endif /* TRANSITDATAALLOCEXCEPTION_H_ */
