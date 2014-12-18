#include "TestSnder.h"
#include "TestRcver.h"
#include "TestConfig.h"
#include <thread>
#include <iostream>
#include <string>

using namespace std;

void testSimple()
{
	TestSnder sender(SENDER);
	TestRcver rcver(RECEIVER);
	cout << "After initiation " << endl;


	thread rt(TestAppInterface::start, &rcver, 2);
	cout << "create thread receiver " << endl;
	thread st(TestAppInterface::start, &sender, 3);
	cout << "create thread sender " << endl;

//	sleep(1000);
	getchar();

	cout << "To stop sender and receiver " << endl;
	sender.stop();
	rcver.stop();

	cout << "Waiting for join " << endl;
	st.join();
	rt.join();

	cout << "End of test " << endl;
}

int main()
{
	testSimple();
}
