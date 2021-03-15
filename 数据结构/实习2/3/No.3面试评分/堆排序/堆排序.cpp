// 堆排序.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "大根堆.h"

#include<iostream>
#include<time.h>
#include"随机序列生成.h"
#include <fstream>
#include <sstream>
#include<Windows.h>
using namespace std;



int main()
{
	cout << "输入随机序列个数以及前M的人数的个数" << endl;
	int N, M;
	cin >>N>>M ;

	Heap heap(RandomSequence(N), N+1);
	heap.HeapSort();
	heap.OutPut(M);
    return 0;
}




/*
clock_t start, end;
start = clock();


end = clock();
double t = double(end - start) / 1000;
cout << t << endl;

*/