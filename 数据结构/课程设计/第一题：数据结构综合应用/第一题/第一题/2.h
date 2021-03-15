#pragma once

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<stack>
using namespace std;

class Solution {
public:
	Solution()
	{
		BeginRow = 0;
		BeginColumn = 0;
		EndRow = 0;
		EndColumn = 0;
		result = 0;
	}

	int BeginRow;
	int BeginColumn;
	int EndRow;
	int EndColumn;
	int result;

	int maximalRectangle(vector<vector<bool>> &matrix)
	{
		int BR = 0;
		int BC = 0;
		int ER = 0;
		int EC = 0;
		int MaxArea = 0;                                   //最大矩形，面积
		int CurrentArea = 0;                               //当前计算面积
		int Size = matrix.size();                            //矩阵长度
		if (Size == 0)
		{
			return 0;
		}
		int ColumnSize = matrix[0].size();
		stack<int> STACK;
		int *Height = new int[ColumnSize];                       //Size个矩形条
		int ZeroPosition = 0;
		for (int CurrentLevel = 0; CurrentLevel < Size; CurrentLevel++)
		{
			for (int i = 0; i < ColumnSize; i++)                    //计算矩形条高度
			{
				for (int j = CurrentLevel; j < Size; j++)
				{
					if (j == CurrentLevel)
					{
						if (matrix[j][i] == 1)
						{
							Height[i] = 1;
						}
						else
						{
							Height[i] = 0;
						}
					}
					else
					{
						if (Height[i] != 0 && matrix[j][i] == 1)
						{
							Height[i] += 1;
						}
						else
						{
							break;
						}
					}
				}
			}

			bool ALL = 1;
			for (int i = 0; i<ColumnSize; i++)
			{
				if (Height[i] != Size)
				{
					ALL = 0;
					break;
				}
			}
			if (ALL == 1)
			{
				BeginRow = 0;
				BeginColumn = 0;
				EndRow = Size - 1;
				EndColumn = ColumnSize - 1;
				if (ColumnSize == 0)
				{
					EndColumn = 0;
				}
				result = Size*ColumnSize;
				return result;
			}

			ZeroPosition = 0;
			int current = 0;
			int CurrentHeight = 0;
			while (current < ColumnSize)
			{
				if (STACK.empty() || Height[STACK.top()] <= Height[current])
				{
					if (Height[current] == 0)
					{
						current++;
						ZeroPosition = current;
					}
					else
					{
						STACK.push(current++);
					}
				}
				else
				{
					if (Height[current] == 0)
					{
						while (!STACK.empty())
						{
							CurrentHeight = STACK.top();
							STACK.pop();

							if (STACK.empty())
							{
								CurrentArea = Height[CurrentHeight] * (current - ZeroPosition);
								BR = CurrentLevel;
								BC = ZeroPosition;
								ER = CurrentLevel + Height[CurrentHeight] - 1;
								EC = current - 1;
							}
							else
							{
								CurrentArea = Height[CurrentHeight] * (current - STACK.top() - 1);
								BR = CurrentLevel;
								BC = STACK.top();
								ER = CurrentLevel + Height[CurrentHeight] - 1;
								EC = current - 1;
							}
							if (MaxArea < CurrentArea)
							{

								BeginRow = BR;
								BeginColumn = BC;
								EndRow = ER;
								EndColumn = EC;

								MaxArea = CurrentArea;
							}
							if (MaxArea >= Size*ColumnSize * 4 / 5)
							{
								result = MaxArea;
								return MaxArea;
							}
						}
					}
					else
					{
						CurrentHeight = STACK.top();
						STACK.pop();
						if (STACK.empty())
						{
							CurrentArea = Height[CurrentHeight] * (current - ZeroPosition);
							BR = CurrentLevel;
							BC = ZeroPosition;
							ER = CurrentLevel + Height[CurrentHeight] - 1;
							EC = current - 1;
						}
						else
						{
							CurrentArea = Height[CurrentHeight] * (current - STACK.top() - 1);
							BR = CurrentLevel;
							BC = STACK.top();
							ER = CurrentLevel + Height[CurrentHeight] - 1;
							EC = current - 1;
						}
						if (MaxArea < CurrentArea)
						{

							BeginRow = BR;
							BeginColumn = BC;
							EndRow = ER;
							EndColumn = EC;

							MaxArea = CurrentArea;
						}
						if (MaxArea >= Size*ColumnSize * 4 / 5)
						{
							result = MaxArea;
							return MaxArea;
						}
					}

				}
			}
			while (!STACK.empty())
			{
				CurrentHeight = STACK.top();
				STACK.pop();
				if (STACK.empty())
				{
					CurrentArea = Height[CurrentHeight] * (current - ZeroPosition);
					BR = CurrentLevel;
					BC = ZeroPosition;
					ER = CurrentLevel + Height[CurrentHeight] - 1;
					EC = current - 1;
				}
				else
				{
					CurrentArea = Height[CurrentHeight] * (current - STACK.top() - 1);
					BR = CurrentLevel;
					BC = STACK.top();
					ER = CurrentLevel + Height[CurrentHeight] - 1;
					EC = current - 1;
				}
				if (MaxArea < CurrentArea)
				{

					BeginRow = BR;
					BeginColumn = BC;
					EndRow = ER;
					EndColumn = EC;
					MaxArea = CurrentArea;
				}
				if (MaxArea >= Size*ColumnSize * 4 / 5)
				{
					result = MaxArea;
					return MaxArea;
				}
			}
		}
		result = MaxArea;
		return MaxArea;
	}

	int maximalRectangle(int *HEIGHT, int LENGTH)
	{
		int MaxArea = 0;                                   //最大矩形，面积
		int CurrentArea = 0;                               //当前计算面积
		int Size = LENGTH;                                //长度
		if (Size == 0)
		{
			return 0;
		}
		stack<int> STACK;
		int *Height = HEIGHT;                       //Size个矩形条
		int ZeroPosition = 0;

		for (int CurrentLevel = 0; CurrentLevel < Size; CurrentLevel++)
		{
			int current = 0;
			int CurrentHeight = 0;
			while (current < Size)
			{
				if (STACK.empty() || Height[STACK.top()] <= Height[current])
				{
					if (Height[current] == 0)
					{
						current++;
						ZeroPosition = current;
					}
					else
					{
						STACK.push(current++);
					}
				}
				else
				{
					if (Height[current] == 0)
					{
						while (!STACK.empty())
						{
							CurrentHeight = STACK.top();
							STACK.pop();
							if (STACK.empty())
							{
								CurrentArea = Height[CurrentHeight] * (current - ZeroPosition);
							}
							else
							{
								CurrentArea = Height[CurrentHeight] * (current - STACK.top() - 1);
							}
							if (MaxArea < CurrentArea)
							{
								MaxArea = CurrentArea;
							}
						}
					}
					else
					{
						CurrentHeight = STACK.top();
						STACK.pop();
						if (STACK.empty())
						{
							CurrentArea = Height[CurrentHeight] * (current - ZeroPosition);
						}
						else
						{
							CurrentArea = Height[CurrentHeight] * (current - STACK.top() - 1);
						}
						if (MaxArea < CurrentArea)
						{
							MaxArea = CurrentArea;
						}
					}

				}
			}
			while (!STACK.empty())
			{
				CurrentHeight = STACK.top();
				STACK.pop();
				if (STACK.empty())
				{
					CurrentArea = Height[CurrentHeight] * (current - ZeroPosition);
				}
				else
				{
					CurrentArea = Height[CurrentHeight] * (current - STACK.top() - 1);
				}
				if (MaxArea < CurrentArea)
				{
					MaxArea = CurrentArea;
				}
			}
		}
		return MaxArea;
	}

};