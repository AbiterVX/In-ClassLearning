#pragma once

#include "stdafx.h"
#include<iostream>
using namespace std;



struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
private:
	ListNode *first;                //初始节点
public:
	Solution()
	{
		first = new ListNode(-1);
		first->next = NULL;
	}
	void InPut(int Data)
	{
		ListNode *Current = new ListNode(Data);
		if (first->next == NULL)
		{
			first->next = Current;
		}
		else
		{
			Current->next = first->next;
			first->next = Current;
		}
		//OutPut();
	}
	bool OutPut()
	{
		ListNode *Current;
		if (first->next != NULL)
		{
			Current = first->next;
		}
		else
		{
			return false;
		}
		while (Current != NULL)
		{
			cout << Current->val << " ";
			Current = Current->next;
		}
		cout << endl;
		return true;
	}
	ListNode *GetFirst()
	{
		return first->next;
	}



	ListNode * reverseKGroup(ListNode * head, int k) {
		if (k == 1)
		{
			return head;
		}
		int count = 0;
		ListNode *Current = head;
		ListNode *CountNode = head;
		ListNode *OtherS;
		ListNode *Head = new ListNode(0);
		ListNode *Tail = new ListNode(0);
		ListNode *LastTail = new ListNode(0);
		ListNode *NewList = head;
		bool Enough = 1;
		int FIRST = 0;
		while (Enough != 0)         //如果足够k个
		{
			for (int i = 0; i < k; i++)       //如果不足k个，直接退出
			{
				if (CountNode->next != NULL)
				{
					CountNode = CountNode->next;
				}
				else
				{
					if (i != k - 1)
					{
						Enough = 0;
					}
					break;
				}
			}
			if (Enough == 1)     //足够
			{
				while (count < k)
				{
					if (Head->next != NULL)
					{
						OtherS = Head->next;
						Head->next = Current;
						//cout << Current->val << " ";	
						Current = Current->next;
						Head->next->next = NULL;
						Head->next->next = OtherS;
					}
					else
					{
						Head->next = Current;
						Tail->next = Current;
						//cout << Current->val << " ";
						Current = Current->next;
						Head->next->next = NULL;
					}
					count++;
				}
				count = 0;
				if (FIRST == 0)
				{
					NewList = Head->next;
					FIRST = 1;
					LastTail->next = Tail->next;
					Tail->next = Current;
				}
				if (Current != NULL)
				{
					CountNode = Current;
					if (FIRST != 1)
					{
						LastTail->next->next = Head->next;
						LastTail->next = Tail->next;
					}
					Head->next = NULL;
					FIRST = 2;
				}
				else
				{
					if (FIRST != 1)
					{
						LastTail->next->next = Head->next;
					}
					break;
				}
			}
			else
			{
				if (Current != NULL)
				{
					LastTail->next->next = Current;
				}
			}
		}
		return NewList;
	}


};


int main()
{
	Solution s;
	//s.InPut(7);
	//s.InPut(6);
	//s.InPut(5);
	//s.InPut(4);
	s.InPut(3);
	s.InPut(2);
	s.InPut(1);
	s.OutPut();

	ListNode *NewList;
	ListNode *Current;
	NewList = s.reverseKGroup(s.GetFirst(), 3);
	Current = NewList;



	cout << endl << endl;
	while (Current != NULL)
	{
		cout << Current->val << " ";
		Current = Current->next;
	}
	cout << endl;





	return 0;
}

