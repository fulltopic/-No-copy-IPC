/*
 * TestTmp.cpp
 *
 *  Created on: Nov 22, 2014
 *      Author: root
 */

#include <bitset>
#include <cstddef>
#include <cstdlib>
#include <ctime>

using namespace std;

template<int UpperBound> class Urand
{
private:
	bitset<UpperBound> used;
public:
	Urand() { srand(time(0));};
	int operator()();
};

template<int UpperBound>
int Urand<UpperBound>::operator ()()
{
}
