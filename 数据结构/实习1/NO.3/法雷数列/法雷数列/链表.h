#pragma once


#include<iostream>
using namespace std;



struct Node
{
	int Numerator;       //分子
	int Denominator;     //分母
	Node *link;          //连接

	Node()               //默认构造
	{
		link = NULL;
	}
	Node(int numerator,int denominator)       //构造并写入数据
	{
		Numerator = numerator;
		Denominator = denominator;
		link = NULL;
	}

};




class List
{
protected:
	Node *first;                    //初始节点
public:
	List()
	{
		first = new Node(0,0);
	}

	bool Insert(int position, int numerator, int denominator)               //在第i个元素后插入
	{
		Node *current = first;                        //当前位置，初始位置为起始节点。

		for (int i = 1; i<position; i++)                   //将“当前位置”指向要求位置
		{
			if (current != NULL)
			{
				current = current->link;              //指向下一个节点
			}
		}

		if (current == NULL)     //如果插入位置大于链表长度，且链表不为空
		{
			return false;
		}
		else                                          //链表为空，或者插入位置小于链表长度
		{
			Node *NewNode = new Node(numerator,denominator);           //创建新的节点 ,存入数据  
			NewNode->link = current->link;            //将插入点之后的链表与其进行连接
			current->link = NewNode;                  //将插入点之前的链表与其进行连接
		}

		return true;
	}


	bool Insert(Node *node, int numerator, int denominator)               //在node后插入
	{
		Node *NewNode = new Node(numerator, denominator);                 //新加节点
		Node *LastNode= node->link;

		//cout << LastNode->Denominator << endl;/////////////

		node->link = NewNode;
		NewNode->link = LastNode;
		return true;
	}





	bool Remove(int position) //删除第i个元素
	{
		Node *current = first;                        //当前位置，初始位置为起始节点。

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
			current->link = current->link->link;        //将删除点之后的链表与之前的链表进行连接	               
		}
		return true;
	}
	
	Node *GetFirstNode()                            //得到头结点
	{
		return first;
	}

	
};