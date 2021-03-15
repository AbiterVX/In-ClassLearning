#pragma once

#include<algorithm>
#include<iostream>
#include<time.h>

#include <fstream>
#include <sstream>
#include<Windows.h>
using namespace std;



class Heap
{
private:
	int *Data;     //数组
	int Length;    //长度

public:
	Heap(int *data, int TotalNumber)      //构造
	{
		Data = data;                      //导入数据
		Length = TotalNumber - 1;         //舍弃第【0】个，将下标对应。
	}

	void HeapAdjust(int CurrentNumber, int length)          //调整一次，得到最大值，即顶部
	{
		int CurrentMax = CurrentNumber;                     //当前最大
		int LeftChild = CurrentNumber * 2;                  //左child
		int RightChild = CurrentNumber * 2 + 1;             //右child


		if (CurrentNumber <= length / 2)                                    //如果当前小于总长
		{
			if (LeftChild <= length && Data[LeftChild] > Data[CurrentMax])  //如果左child不为叶节点，
			{                                                               //且大于当前的数值，
				CurrentMax = LeftChild;                                     //则当前最大变为左child
			}
			if (RightChild <= length && Data[RightChild] > Data[CurrentMax])//如果右child不为叶节点，
			{                                                               //且大于当前的数值，
				CurrentMax = RightChild;                                    //则当前最大变为右child
			}

			if (CurrentMax != CurrentNumber)                                //交换数值  
			{
				swap(Data[CurrentMax], Data[CurrentNumber]);
				HeapAdjust(CurrentMax, length);
			}
		}
	}

	void HeapSort()
	{
		for (int i = Length / 2; i >= 1; i--)
		{
			HeapAdjust(i, Length);
		}

		for (int i = Length; i >= 1; i--)
		{
			swap(Data[1], Data[i]);
			HeapAdjust(1, i - 1);
		}
    }
	



	void OutPut()
	{
		
		for (int i = Length; i > 0; i--)
		{
			cout << Data[i] << " ";
		}
		cout << endl;
	}

	void OutPut(int OutputNumber)                           //输出前M个
	{
		fstream File("Heap.txt", ios_base::out);
		int end = Length - OutputNumber;
		for (int i = Length; i >end; i--)
		{
			File << Data[i] << " ";
		}
		//cout << endl;
		File.close();
		ShellExecute(NULL, L"open", L"Heap.txt", NULL, NULL, SW_SHOWNORMAL);
	}

};


