#pragma once

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<stack>
#include<math.h>
using namespace std;


class TreeNode
{
public:
	int val;
	TreeNode *left, *right;
	TreeNode(int val)
	{
		this->val = val;
		this->left = this->right = NULL;
	}
};


class Solution {
public:
	/*
	* @param root: A Tree
	* @return: A list of lists of integer include the zigzag level order traversal of its nodes' values.
	*/
	vector<vector<int>> zigzagLevelOrder(TreeNode * root)
	{
		// write your code here
		vector<vector<int>> result;
		if (root == NULL)
		{
			return result;
		}
		stack<TreeNode*> Order;
		stack<TreeNode*> Reverse;
		TreeNode * CurrentNode = root;
		int Type = 1;
		int Level = 0;
		Order.push(CurrentNode);
		while (Order.empty() != 1 || Reverse.empty() != 1)
		{
			if (Order.empty() != 1)
			{
				vector<int> NewLevel;
				while (Order.empty() != 1)
				{
					CurrentNode = Order.top();
					Order.pop();
					NewLevel.push_back(CurrentNode->val);
					if (CurrentNode->left != NULL)
					{
						Reverse.push(CurrentNode->left);
					}
					if (CurrentNode->right != NULL)
					{
						Reverse.push(CurrentNode->right);
					}

				}
				result.push_back(NewLevel);
				Level++;
			}
			else
			{
				while (Reverse.empty() != 1)
				{
					vector<int> NewLevel;
					while (Reverse.empty() != 1)
					{
						CurrentNode = Reverse.top();
						Reverse.pop();
						NewLevel.push_back(CurrentNode->val);
						if (CurrentNode->right != NULL)
						{
							Order.push(CurrentNode->right);
						}
						if (CurrentNode->left != NULL)
						{
							Order.push(CurrentNode->left);
						}
					}
					result.push_back(NewLevel);
					Level++;
				}
			}
			if (Type = 1)
			{
				Type = 2;
			}
			else
			{
				Type = 1;
			}
		}
		return result;
	}




};
