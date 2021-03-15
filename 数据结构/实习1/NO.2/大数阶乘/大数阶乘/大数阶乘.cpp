// 大数阶乘.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include"链表.h"

#include<Windows.h>

using namespace std;




void Factorial(int number) //大数阶乘
{
	List Result;                                                 //结果
	Result.Insert(0, 1);                                         //起始节点
	Node *current = Result.GetFirstNode()->link;                 //设置当前节点与第一个节点位置一致
	int add = 0;                                                 //进位	

	for (int i = 1; i <= number; i++)                            //阶乘
	{
		while (current != Result.GetLastNode())                                  //各节点数据 进行乘法
		{
			(current->Data) *= i;
			current = current->link;
		}
		current = Result.GetFirstNode()->link;                    //设置当前节点与第一个节点位置一致

		while (current != Result.GetLastNode())                                  //每一次数据相乘后，数据进行规范，即每个节点数据为3位
		{
			if (current->link == Result.GetLastNode() && current->Data >= 1000)  //如果最高位大于3位，则向前增加一位
			{
				Node *NewNode = new Node(0);
				current->link = NewNode;
				NewNode->link = Result.GetLastNode();
				Result.GetLastNode()->BackLink = NewNode;
				NewNode->BackLink = current;
				
			}

			add = (current->Data) / 1000;                           //进位
			current->Data %= 1000;
			current = current->link;
			if (current != Result.GetLastNode())                                 //最高位进位
			{
				(current->Data) += add;
			}

		}
		current = Result.GetFirstNode()->link;                     //设置当前节点与第一个节点位置一致
	}


	if (current->Data >= 1000)                                   //最高位进位。
	{
		Node *NewNode = new Node;
		current->link = NewNode;
		add = (current->Data) % 1000;
		current->Data % 1000;
		current = current->link;
		current += add;
	}

	//Result.Inverse(Result.GetFirstNode());

	Node *node = Result.GetLastNode()->BackLink;
	int i = 0;



	fstream File("Factorial.txt", ios_base::out);

	while (node != Result.GetFirstNode() )
	{
		if (i>0)
		{
			if (node->Data >= 100)
			{
				File << node->Data << " ";
			}
			else if (10 <= node->Data && node->Data < 100)
			{
				File << 0 << node->Data << " ";
			}
			else if (0 <= node->Data && node->Data < 10)
			{
				File << 0 << 0 << node->Data << " ";
			}
		}
		else
		{
			File << node->Data << " ";
			i = 1;
		}

		node = node->BackLink;
	}


	File.close();

	ShellExecute(NULL, L"open", L"Factorial.txt", NULL, NULL, SW_SHOWNORMAL); //打开文件
																			  //Result.FactorialOutPutReverse(Result.GetFirstNode()->link);  //倒序递归输出
}





int main()
{
	int number;
	cin >> number;
	Factorial(number);

    return 0;
}

/*
Result.Inverse(Result.GetFirstNode());
Node *node = Result.GetFirstNode()->link;
int i = 0;




while (node != NULL)
{
if (i>0)
{
if (node->Data >= 100)
{
File << node->Data << " ";
}
else if (10 <= node->Data && node->Data < 100)
{
File << 0 << node->Data << " ";
}
else if (0 <= node->Data && node->Data < 10)
{
File << 0 << 0 << node->Data << " ";
}
}
else
{
File << node->Data << " ";
i = 1;
}

node = node->link;
}
*/