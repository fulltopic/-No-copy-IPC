/*
 * Test.cpp
 *
 *  Created on: Sep 11, 2014
 *      Author: root
 */




#include <string>
#include <iostream>

using namespace std;

class Test
{
private:
	int v;
	int vs[2];

public:
	Test(int vv):v(vv)
	{
		vs[0] = 3;
		vs[1] = 4;
	}

	int getV(int index)
	{
		switch(index)
		{
		case 0:
			return v;
		case 1:
			return vs[0];
		case 2:
			return vs[1];
		default:
			return -1;
		}
	}
};

class Generator
{
public:
	static Test Generate()
	{
		return Test(3);
	}
};

int main()
{
	Test tester = Generator::Generate();
	cout << tester.getV(2) << endl;
}
