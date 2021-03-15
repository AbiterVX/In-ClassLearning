#pragma once


#include "链表栈.h"
#include<math.h>
#include<iostream>
#include<string>
#include<sstream>
#include<cstring>
using namespace std;




class Calculater            //计算
{
protected:
	char *InfixExression = NULL;           //中缀表达式
	Stack<char> Symbols;                 //符号栈 
	Stack<double> OrderNumbers;          //栈，数字 
										 //Stack<char> OrderSymbols;            //符号栈 
										 //Stack<int> OrderList;                //链表
	double Result = 0;                   //结果数值
	int Form[9][9] = { { 1,1,0,0,0,1,1,0,0 },
	                   { 1,1,0,0,0,1,1,0,0 },
	                   { 1,1,1,1,0,1,1,0,0 },
	                   { 1,1,1,1,0,1,1,0,0 },
	                   { 0,0,0,0,0,2,4,0,0 },
	                   { 1,1,1,1,4,1,1,1,0 },
	                   { 0,0,0,0,0,4,3,0,0 },
					   { 1,1,1,1,0,1,1,1,0 },
					   { 1,1,1,1,0,1,1,1,1 }
	                  };               //构造的表格
public:
	Calculater()                      //默认构造 
	{
		Symbols.InsertFirst('#');
	}
	void LeadingIn(char* infixExression)     //导入中缀表达式
	{
		InfixExression = infixExression;
	}
	bool IfSymbol(char CHAR)
	{
		if (CHAR == '(' || CHAR == ')' || CHAR == '#' || CHAR == '+' || CHAR == '-'
			|| CHAR == '*' || CHAR == '/' || CHAR == '^' || CHAR == '%')
		{
			return true;
		}
		else
		{
			return false;
		}
	}




	int TransformSymbol(char symbol)
	{
		int Level = 0;
		switch (symbol)
		{
		case '+':
			Level = 0;
			break;
		case '-':
			Level = 1;
			break;
		case '*':
			Level = 2;
			break;
		case '/':
			Level = 3;
			break;
		case '(':
			Level = 4;
			break;
		case ')':
			Level = 5;
			break;
		case '#':
			Level = 6;
			break;
		case '^':
			Level = 7;
			break;
		case '%':
			Level = 8;
			break;

		}
		

		return Level;
	}



	int IfPrior(char symbol1, char symbol2)   //判断符号优先级
	{
		int level = Form[TransformSymbol(symbol1)][TransformSymbol(symbol2)];
		return level;
	}




	double Transform()                       //中缀转后缀
	{

		double TransformNumber = 0;      //小数
		char PreviousSymbol = '#';       //上一个运算符，实现小数运算
		int DecimalTimes = 0;            //小数位数

		for (int i = 0;; i++)
		{			
			if (InfixExression[i] != '\0')                                                   //如果没有输完
			{
				if (48 <= InfixExression[i] && InfixExression[i] <= 57)                      //数字
				{
					double number = InfixExression[i] - 48;                                  //ascll码变成数字

					if (PreviousSymbol != '.')                                               //如果不是小数
					{
						TransformNumber *= 10;                                               //将分离的数字
						TransformNumber += number;                                           //变成多位数
					}
					else                                                                     //如果是小数
					{
						DecimalTimes++;                                                      //小数位数计数
						TransformNumber = TransformNumber + number * pow(0.1, DecimalTimes); //进行小数位相加
					}

					if (IfSymbol(InfixExression[i + 1]) == 1)                              //如果下一位为符号，则数字以输入完毕，则输出数字
					{
						OrderNumbers.InsertFirst(TransformNumber);                           //插入到数字栈
																							 //OrderList.InsertLast(0);                                             //将链表位置记为数字0
						TransformNumber = 0;                                                 //清零，方便之后计算
						DecimalTimes = 0;
					}
				}

				else if (InfixExression[i] == '.')                                           //如果为小数点，则当前符号改为小数点
				{
					PreviousSymbol = '.';
				}


				else if (IfSymbol(InfixExression[i]))                                        //如果为运算符
				{
					PreviousSymbol = InfixExression[i];                                      //当前符号改为运算符
					if (IfPrior(Symbols.GetTopData(), InfixExression[i]) == 0)                 //如果优先级小，则插入符号栈中
					{
						Symbols.InsertFirst(InfixExression[i]);                              //插入
					}

					else if (IfPrior(Symbols.GetTopData(), InfixExression[i]) == 1)           //如果优先级大，则
					{
						double Number2 = OrderNumbers.GetTopData();
						OrderNumbers.RemoveFirst();
						double Number1 = OrderNumbers.GetTopData();
						OrderNumbers.RemoveFirst();


						double result = CalculateNumber(Number1, Number2, Symbols.GetTopData());
						OrderNumbers.InsertFirst(result);

						Symbols.RemoveFirst();                                               //移除符号栈栈顶元素

						i--;
					}



					else if (IfPrior(Symbols.GetTopData(), InfixExression[i]) == 2)         //如果两个括号相遇
					{
						Symbols.InsertFirst(InfixExression[i]);                             //则清空两个括号
						Symbols.RemoveFirst();
						Symbols.RemoveFirst();
					}
					else if (IfPrior(Symbols.GetTopData(), InfixExression[i]) == 3)         //如果两个#相遇，则完毕
					{
						//cout << "结束！" << endl;
						break;
					}
					else                                                                    //算式格式错误
					{
						cout << "错误！" << endl;
						break;
					}
				}

				if (InfixExression[i] == '#')
				{
					i--;
				}

			}

			else  //输完则结束
			{
				break;
			}
		}

		Result = OrderNumbers.GetTopData();	
		return Result;
	}






	double CalculateNumber(double Number1, double Number2, char Symbol)
	{
		double result = 0;
		switch (Symbol)
		{
		case '+':
			result = Number1 + Number2;
			break;
		case '-':
			result = Number1 - Number2;
			break;
		case '*':
			result = Number1 * Number2;
			break;
		case '/':
			result = Number1 / Number2;
			break;
		case '^':
			result = pow(Number1,Number2);
			break;
		case '%':
			result = (int)Number1% (int)Number2;
			break;
		}

		return result;
	}

	



	char* CStringToCHAR(CString cstring) {          
		string STRING;
		stringstream ss;
		ss << cstring;
		ss >> STRING;
		char * CHAR = (char*)STRING.data();
		return CHAR;
	}

	CString DoubleToCString(double number)
	{
		CString CSTRING;
		CSTRING.Format(_T("%1f"), number);
		return CSTRING;
	}

	string CStringToString(CString cstring)
	{
		int len = WideCharToMultiByte(CP_ACP, 0, cstring, -1, NULL, 0, NULL, NULL);   //CString转char*
		char *Formular = new char[len + 1];                                           //
		WideCharToMultiByte(CP_ACP, 0, cstring, -1, Formular, len, NULL, NULL);       //

		string STRING;
		STRING = Formular;
		return STRING;
	}

};


