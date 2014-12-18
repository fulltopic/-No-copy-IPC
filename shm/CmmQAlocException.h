/*
 * CmmQAlocException.h
 *
 *  Created on: Sep 11, 2014
 *      Author: root
 */

#ifndef CMMQALOCEXCEPTION_H_
#define CMMQALOCEXCEPTION_H_

#include <exception>

using namespace std;

class CmmQAlocException: public exception
{
public:
	CmmQAlocException();
	virtual ~CmmQAlocException() throw();

	virtual const char* what() const throw();
};

#endif /* CMMQALOCEXCEPTION_H_ */
