#pragma once

#include "stdafx.h"
#include<vector>
#include<iostream>
using namespace std;


class ListNode
{
public:
	int val;
	ListNode *next;
	ListNode(int val)
	{
		this->val = val;
		this->next = NULL;
	}
};


class Solution
{
public:
	vector<ListNode*> rehashing(vector<ListNode*> hashTable)
	{
		int Length = hashTable.size();
		int NewLength = Length * 2;
		for (int i = 0; i < Length; i++)
		{
			hashTable.push_back(NULL);
		}

		ListNode* Current = NULL;
		ListNode* NewList = NULL;
		for (int i = Length - 1; i >= 0; i--)
		{
			if (hashTable[i] != NULL)
			{
				Current = hashTable[i];
				while (Current->next != NULL)
				{
					Current = Current->next;
				}
				Current->next = NewList;
				/*if (NewList!= NULL)
				{
				NewList->next = NULL;
				}*/

				NewList = hashTable[i];
				hashTable[i] = NULL;
			}
		}

		Current = NewList;
		ListNode* NewNode = NULL;
		int Position = 0;

		ListNode* NewPosition = NULL;
		while (Current != NULL)
		{
			NewNode = Current;
			if (Current->next != NULL)
			{
				Current = Current->next;
			}
			else
			{
				Current = NULL;
			}
			NewNode->next = NULL;
			Position = (NewNode->val %NewLength + NewLength) % NewLength;

			if (hashTable[Position] != NULL)
			{
				ListNode* Current1 = hashTable[Position];
				while (Current1->next != NULL)
				{
					Current1 = Current1->next;
				}
				Current1->next = NewNode;
			}
			else
			{
				hashTable[Position] = NewNode;
			}
		}


		return hashTable;
	}


};