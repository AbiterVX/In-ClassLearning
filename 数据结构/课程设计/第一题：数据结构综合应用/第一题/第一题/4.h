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

	int maxPathSum(TreeNode * root)
	{
		int MaxPathSum = pow(2, 31) - 1;
		MaxPathSum = 0 - MaxPathSum;
		EachPath(root, MaxPathSum);
		return MaxPathSum;
	}

	int EachPath(TreeNode * root, int &MaxPathSum)
	{
		if (root == NULL)    //为空，递归
		{
			return 0;
		}
		int LeftPath = EachPath(root->left, MaxPathSum);
		int RightPath = EachPath(root->right, MaxPathSum);

		int Left = 0;                //是否选择，左child 与 右child
		int Right = 0;
		if (Left < LeftPath)
		{
			Left = LeftPath;
		}
		if (Right<RightPath)
		{
			Right = RightPath;
		}
		if (MaxPathSum < Left + Right + root->val) //判断左，到当前，再到右，这条路径是否为最大
		{
			MaxPathSum = Left + Right + root->val;
		}
		int OneSide = Left;                         //返回单边最短，  1.只有当前节点 
		if (Left < Right)                          //                2.当前节点 +左child
		{                                          //                3.当前节点 +右child
			OneSide = Right;
		}
		return OneSide + root->val;
	}
};
