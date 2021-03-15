#pragma once


#include<Windows.h>
#include<algorithm>
#include<vector>
#include<time.h>
#include<iostream>

using namespace std;



int *RandomSequence(int N)
{
	int *Number = new int[N+1];
	Number[0] = 0;

	SYSTEMTIME Time;
	ZeroMemory(&Time, sizeof(Time));
	GetLocalTime(&Time);

	srand(time(NULL));

	int jj = rand();
	Sleep(jj / 500);
	srand(time(NULL));
	vector<int>w;

	for (int i = 1; i <= N; i++)
	{
		w.push_back(i);
	}

	random_shuffle(w.begin(), w.end());

	int TIME = rand();
	int TIME1 = rand() % 30;

	
	srand(time(NULL));
	vector<int> w1;

	for (int ii = 0; ii < N; ii++)
	{
		w1.push_back(ii);
	}

	random_shuffle(w1.begin(), w1.end());

	cout << "生成的随机序列:  "<<endl;

	for (int iii = 0; iii < N; iii++)
	{
		Number[iii+1] = w[w1[iii]];
		cout << w[w1[iii]] << " ";
	}

	cout << endl << endl;
	GetLocalTime(&Time);
	
	return Number;
}
