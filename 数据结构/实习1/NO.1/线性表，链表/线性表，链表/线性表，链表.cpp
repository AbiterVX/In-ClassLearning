// 线性表，链表.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include<Windows.h>
using namespace std;

template <class T>
struct Node
{
	T Data;            //数据
	Node<T> *link;          //连接

	Node()               //默认构造
	{		
		link = NULL;
	}
	Node(T data)       //构造并写入数据
	{
		Data = data;
		link = NULL;
	}

};


template <class T>
class List
{
protected:
	Node<T> *first;                //初始节点
public:
	List()   
	{
		first = new Node<T>(0);
		first->link = NULL;
	}
	List(T data)
	{		
		first = new Node(data);
	}

	void Empty()                   //清空
	{
		Node<int> *current=NULL;

		if (first->link ==NULL)
		{
			
			return;
		}
		while (first->link !=NULL)
		{	
            
			current = first->link;
			//cout << current->Data << endl;
			first->link = current->link;
			
			delete current;
				
		}
		
	}

	~List()                         //析构
	{
		Empty();
		delete first;
	}


	int Length()                     //链表长度
	{
		int length = 0;              //起始长度
		Node *current;               //当前节点
		current = first->link;       //初始节点与当前计数位置一致
		while (current != NULL)      //判断长度是否截至
		{
			current = current->link; //指向下一个节点
			length++;                //自加
		}
		return length;
	} 

	bool Insert(int position, T data)                 //在第i个元素后插入
	{
		Node<T> *current = first;                     //当前位置，初始位置为起始节点。

		for(int i=1;i<position;i++)                   //将“当前位置”指向要求位置
		{
			if (current != NULL)
			{
				current = current->link;              //指向下一个节点
			}
		}

		if (current == NULL)                          //如果插入位置大于链表长度，且链表不为空
		{
			return false;
		}
		else                                          //链表为空，或者插入位置小于链表长度
		{
			Node<T> *NewNode = new Node<T>(data);     //创建新的节点 ,存入数据  
			NewNode->link = current->link;            //将插入点之后的链表与其进行连接
			current->link = NewNode;                  //将插入点之前的链表与其进行连接
		}
		
		return true;
	}

	bool Remove(int position)                         //删除第i个元素
	{
		Node<T> *current = first;                     //当前位置，初始位置为起始节点。
		Node<T> *DeleteNode;
		for (int i = 1; i<position; i++)              //将“当前位置”指向要求位置
		{
			if (current != NULL)
			{
				current = current->link;              //指向下一个节点
			}
		}

		if (current == NULL)                          //如果删除位置大于链表长度
		{
			return false;
		}
		else                                          //删除位置小于链表长度
		{
			DeleteNode = current->link;
			current->link=current->link->link;        //将删除点之后的链表与之前的链表进行连接	  
			delete DeleteNode;
		}
		return true;
	} 

	T GetData(int position)                           //得到某点的数据
	{
		Node<T> *current = first;                     //当前位置，初始位置为起始节点。

		for (int i = 1; i<=position; i++)             //将“当前位置”指向要求位置
		{
			if (current != NULL)
			{
				current = current->link;              //指向下一个节点
			}
		}

		return current->Data;
	}


	bool Combine(List &AnotherList)                    //两个顺序链表合并
	{
		Node<T> *current1 = first;                         //第一条链表的当前位置
		Node<T> *current2 = AnotherList.first->link;       //第二条链表的当前位置
		Node<T> *LastCurrent1 = current1->link;            //第一条链表的剩余
		Node<T> *LastCurrent2 = current2->link;            //第二条链表的剩余

		while (current2 != NULL)
		{
			LastCurrent1 = current1->link;
			LastCurrent2 = current2->link;

			if (current1->link != NULL )
			{			
				if (current1->Data < current2->Data &&current2->Data <= current1->link->Data)
				{
					current1->link = current2;
					current2->link = LastCurrent1;

					current1 = current2;
					current2 = LastCurrent2;

					
				}
				else
				{
					current1 = current1->link;			
				}				
			}
			else
			{		
				current1->link = current2;
				break;
			}
		}
		
		current1 = current1->link;
		if (current1->link != NULL &&current2 !=NULL)
		{
			if (current2->Data <= current1->link->Data)
			{
				LastCurrent1 = current1->link;
				current1->link = current2;
				current2->link = LastCurrent1;
			}
		}
		
		AnotherList.GetFirstNode()->link = NULL;
		

		return true;
	}
	bool Inverse(Node<T> *node)                   //逆置
	{
		Node<T> *current=first->link;
		Node<T> *LinkNode1;
		Node<T> *LinkNode2 = NULL;
		
		while (current!= NULL)
		{
			LinkNode1 = current->link;		
			current->link = LinkNode2;			
			LinkNode2 = current;                  /////////////
						
			current = LinkNode1;
		}
		first->link = LinkNode2;

		return true;
	}
	bool OutPutOrder(Node<T> *node)                    //顺序递归输出,  list.GetFirstNode()->link
	{	
		if (node != NULL)
		{
			cout << node->Data << " ";
			OutPutOrder(node->link);	
		}
		return true;
	}

	bool OutPutReverse(Node<T> *node)                  //逆序递归输出,  list.GetFirstNode()->link
	{
		if (node != NULL)
		{
			OutPutReverse(node->link);
			cout << node->Data << " ";
		}
		return true;
	}
	Node<T> *GetFirstNode()
	{
		return first;
	}

	bool FactorialOutPutReverse(Node<T> *node)                    //大数阶乘，顺序递归输出,  list.GetFirstNode()->link
	{
		
		if (node != NULL)
		{
			FactorialOutPutReverse(node->link);

			if (node->link != NULL)
			{
				if (node->Data >= 100)
				{
					cout << node->Data << " ";
				}
				else if (10 <= node->Data && node->Data < 100)
				{
					cout << 0 << node->Data << " ";
				}
				else if (0 <= node->Data && node->Data < 10)
				{
					cout << 0 << 0 << node->Data << " ";
				}
			}
			else
			{
				cout << node->Data << " ";
			}
			
		}
		return true;
	}
};



void Factorial(int number) //大数阶乘
{	
	List<int> Result;                                                 //结果
	Result.Insert(0, 1);                                         //起始节点
	Node<int> *current = Result.GetFirstNode()->link;                 //设置当前节点与第一个节点位置一致
	int add = 0;                                                 //进位	

	for (int i = 1; i <= number; i++)                            //阶乘
	{
		while (current != NULL)                                  //各节点数据 进行乘法
		{			
			(current->Data) *= i;			
			current = current->link;
		}
		current= Result.GetFirstNode()->link;                    //设置当前节点与第一个节点位置一致

		while (current != NULL)                                  //每一次数据相乘后，数据进行规范，即每个节点数据为3位
		{
			if (current->link == NULL && current->Data >= 1000)  //如果最高位大于3位，则向前增加一位
			{
				Node<int> *NewNode = new Node<int>(0);
				current->link = NewNode;
			}

			add=(current->Data) /1000;                           //进位
			current->Data %= 1000;			
			current = current->link;
			if (current != NULL)                                 //最高位进位
			{			
				(current->Data) += add;
			}
			
		}	
		current=Result.GetFirstNode()->link;                     //设置当前节点与第一个节点位置一致
	}


	if (current->Data >= 1000)                                   //最高位进位。
	{
		Node<int> *NewNode = new Node<int>;
		current->link = NewNode;
		add = (current->Data) % 1000;
		current->Data % 1000;
		current = current->link;
		current += add;
	}

	Result.Inverse(Result.GetFirstNode());
	Node<int> *node = Result.GetFirstNode()->link;
	int i = 0;



	fstream File("Factorial.txt", ios_base::out );

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
	File.close();

	ShellExecute(NULL, L"open", L"Factorial.txt", NULL, NULL, SW_SHOWNORMAL); //打开文件
	//Result.FactorialOutPutReverse(Result.GetFirstNode()->link);  //倒序递归输出
}




int main()
{
	
	List<int> list;
	list.Insert(0, 10);
	list.Insert(0, 8);
	list.Insert(0, 6);
	list.Insert(0, 4);
	list.Insert(0, 2);

	list.OutPutOrder(list.GetFirstNode()->link);
	cout << endl;

	List<int> list1;
	list1.Insert(0, 9);
	list1.Insert(0, 7);
	list1.Insert(0, 5);
	list1.Insert(0, 3);
	list1.Insert(0, 1);

	list1.OutPutOrder(list1.GetFirstNode()->link);
	cout << endl;


	list1.Combine(list);
	list1.OutPutOrder(list1.GetFirstNode()->link);

    return 0;
}












/*
int number;
cin >> number;
Factorial(number);
*/





/*
List<int> list;
list.Insert(0, 10);
list.Insert(0, 8);
list.Insert(0, 6);
list.Insert(0, 4);
list.Insert(0, 2);

List<int> list1;
list1.Insert(0, 9);
list1.Insert(0, 7);
list1.Insert(0, 5);
list1.Insert(0, 3);
list1.Insert(0, 1);

list1.Combine(list);
list1.OutPutOrder(list1.GetFirstNode()->link);
*/