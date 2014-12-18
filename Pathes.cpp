/*
 * Pathes.cpp
 *
 *  Created on: Sep 15, 2014
 *      Author: root
 */



#include <vector>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	vector<vector<vector<int> > > rcss;

	vector<vector<int> > rc0(4, vector<int>(4, 0));
	for(int i = 0; i < 4; i ++)
	{
		rc0[i][i] = 1;
	}
	rcss.push_back(rc0);

	vector<vector<int> > rc1(4, vector<int>(4, 0));
	rc1[0][1] = 1;
	rc1[0][2] = 1;
	rc1[1][3] = 1;
	rc1[2][3] = 1;
	rc1[3][1] = 1;
	rc1[3][0] = 1;
	rcss.push_back(rc1);
	cout << "Result " << 1 << endl;
	for(int j = 0; j < 4; j ++)
	{
		for(int k = 0; k < 4; k ++)
		{
			cout << rc1[j][k] << ",";
		}
		cout << endl;
	}

	for(int i = 2; i <= 14; i ++)
	{
		vector<vector<int> > rcs(4, vector<int>(4, 0));
//		for(int j = 1; j < i; j ++)
//		{
			int index1 = 1;
			int index2 = i - 1;

			if(index1 > 1)
			{
				break;
			}

			for(int k = 0; k < 4; k ++)
			{
				for(int t = 0; t < 4; t ++)
				{
					for(int x = 0; x < 4; x ++)
					{
						rcs[k][x] += rcss[index1][k][t] * rcss[index2][t][x];
					}
				}
			}
//		}
		rcss.push_back(rcs);

		cout << "Result " << i << endl;
		for(int j = 0; j < 4; j ++)
		{
			for(int k = 0; k < 4; k ++)
			{
				cout << rcs[j][k] << ",";
			}
			cout << endl;
		}
	}


}
