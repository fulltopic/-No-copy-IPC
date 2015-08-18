/*
 * TestGcc.cc
 *
 *  Created on: Sep 6, 2014
 *      Author: root
 */




#ifdef OLDCPP
#include <cstdatomic>
#else
#include <atomic>
#endif
#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <pthread.h>

using namespace std;

class A
{
	char aa[4];
	static atomic_int seq;
};

struct TailInd
{
	int tail;
	int head;
};

int main()
{
//	unordered_map<int, int> tester;


	atomic_bool x;

	bool a = true;
	bool b = false;
	x.compare_exchange_strong(a, b);

	x.store(true);
	bool expected = false;
	bool rc = x.compare_exchange_strong(expected, false);

	cout << "To test " << rc << endl;


	atomic_int y;
	cout << "Size of atomic_int " << sizeof(atomic_int) << " atomic_bool " << sizeof(atomic_bool) << endl;
	cout << "Is lock free ?" << y.is_lock_free() << endl;

	cout << "Size of A " << sizeof(A) << endl;

	atomic_int testXc(0);
	atomic_int testMem(0);
	testMem = 1;
	testXc = testMem.exchange(testXc);
	cout << "testMem = " << testMem << " testXc = " << testXc << endl;

	atomic_long testLong(0);
	atomic_int testInt(0);
	cout << "Long is of size " << sizeof(testLong) << " is atomic ? " << testLong.is_lock_free() << endl;
	cout << "Long is of size " << sizeof(testInt) << " is atomic ? " << testInt.is_lock_free() << endl;

	atomic<TailInd> testTail;

	cout << "Tail Indicator is lock free " << testTail.is_lock_free() << endl;

	pthread_t test_tid;
}
