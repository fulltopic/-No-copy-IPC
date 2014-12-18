/*
 * TestShift.cc
 *
 *  Created on: Dec 16, 2014
 *      Author: zf
 */

#include <iostream>
#include <string>
#include <sys/types.h>
#include <climits>

using namespace std;

enum consts
{
	SHIFTNUM = sizeof(ushort) * 8,
};

int main()
{
	int i = 1;
	i <<= SHIFTNUM;

	cout << sizeof(USHRT_MAX) << ", " << sizeof(ushort) << endl;
	cout << USHRT_MAX << endl;
	cout << i << endl;
}




