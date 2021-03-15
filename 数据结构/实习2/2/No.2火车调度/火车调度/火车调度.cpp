// 火车调度.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"生成随机序列.h"
#include"链表队列.h"
#include <iostream>
#include<string>
#include<sstream>

#include <fstream>
#include <sstream>
#include<Windows.h>
using namespace std;

class TrainDispatching
{
private:
	Queue Train;;          //输入编号
	Queue *AllRailway;     //轨道
	int TrainNumber;       //火车个数
	int RailwayNumber;     //铁轨个数
	int length;            //长度
	
public:
	TrainDispatching()
	{
		TrainNumber = 0;
		RailwayNumber = 0;
		length = 0;
	}
	TrainDispatching(int N)
	{
		TrainNumber = N;
		AllRailway = new Queue[TrainNumber];
	}
	void LeadingIn(int *TRAIN)
	{
		for (int i = 0; i <TrainNumber; i++)
		{
			Train.Insert(TRAIN[i]);
		}
		
	}
	void LeadingIn(char *TRAIN)
	{			
		int Number=0;
		for (int i = 0;; i++)
		{
			if (TRAIN[i] != ',' &&TRAIN[i] != '\0')
			{
				Number *= 10;
				Number += TRAIN[i] -48;
			}
			else if (TRAIN[i] == ',')
			{
				Train.Insert(Number);
				length++;
				Number = 0;
			}	
			else if (TRAIN[i] == '\0')
			{
				Train.Insert(Number);
				length++;
				Number = 0;
				break;
			}
		}	
	}
	void Calculate()
	{
		Node *current = Train.GetFirst()->link;                             //指向当前车厢的指针	                              
		int CurrentTrain;                                                   //当前车厢编号
                               
		while(current != NULL)
		{

			CurrentTrain = current->Data;                                   //得到编号
			//cout << CurrentTrain << endl;
			for (int i = 0;; i++)                                           //分配轨道
			{
				if (AllRailway[i].GetFirst() != NULL)
				{
					if (AllRailway[i].GetLastData() < CurrentTrain)
					{
						AllRailway[i].Insert(CurrentTrain);                //在最小的差值的轨道之后插入
						//cout << i << "," << CurrentTrain << endl;
						break;
					}				
				}
				else
				{
					AllRailway[i+1].Insert(CurrentTrain);                  //在最小的差值的轨道之后插入
					break;
				}			
			}	

			current = current->link;                                        //指向下一个车厢
		}
		
	}

	void OutPut()
	{

		fstream File("Train.txt", ios_base::out);

		File << "图示" << endl;
		Node *current;
		for (int i = 0; i < TrainNumber; i++)
		{
			if (AllRailway[i].GetFirst()->link != NULL)
			{
				current = AllRailway[i].GetFirst()->link;
				File << i + 1 << ": ";

				for (int j = 0;; j++)
				{
					if (current != NULL)
					{
						File << current->Data << " ";
						current = current->link;
					}
					else
					{
						File << endl;
						break;
					}
				}
			}
			else
			{
				break;
			}
		
		}
		File << endl;





		int OutputNumber = 1;
		while (OutputNumber != TrainNumber+1)
		{
			for (int i = 0;; i++)
			{
				if (AllRailway[i].GetFirst()->link != NULL)
				{
					if (AllRailway[i].GetTopData() == OutputNumber)
					{
						File << "编号为： " << OutputNumber <<" 的车厢从第 "<<i+1<<" 条轨道输出!" << endl;
						OutputNumber++;
						AllRailway[i].Remove();
					}
				}
				else
				{
					break;
				}
			}
		}
	
		File.close();
		ShellExecute(NULL, L"open", L"Train.txt", NULL, NULL, SW_SHOWNORMAL);
	}


	char* StringToCHAR(string String)
	{
		char * CHAR = (char*)String.data();
		return CHAR;
	}
};



int main()
{
	cout << "输入火车车厢个数" << endl;
	int N;
	cin >> N;

	TrainDispatching train(N);
	train.LeadingIn( RandomSequence(N) );
	//train.LeadingIn("3,4,6,1,11,13,5,7,19,8,12,2,9,16,10,14,17,18,20,15");

	train.Calculate();
	train.OutPut();
    return 0;
}







/*string STRING;
cout << "输入" << endl;
cin >> STRING;
char* TrainQueue = train.StringToCHAR(STRING);*/
