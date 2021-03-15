#pragma once

#include"队列.h"
#include"栈.h"
#include<iostream>
using namespace std;

struct Edge
{
	int AnotherAddress;  //边的另一个顶点
	double Weight;             //权重
	Edge *link;                //下一条边链指针
	Edge()
	{
		link = NULL;
	}
};
struct Vertex
{
	char Data;        //点的信息
	int Address;      //地址
	Edge *LinkEdge;   //边链表
	Vertex()
	{
		LinkEdge = NULL;
	}
};



class Graph
{
private:
	Vertex *AllVertex;  //所有顶点信息
	int MaxVertexNumber;//最大点的个数
	int VertexNumber;   //点的个数
	int EdgeNumber;     //边的个数
public:
	Graph(int MaxVertex)
	{
		AllVertex = new Vertex[MaxVertex];
		MaxVertexNumber = MaxVertex;
		VertexNumber = 0;
		EdgeNumber = 0;
	}
	~Graph() {}
	bool InsertEdge(char Vertex1, char Vertex2, double weight = 1)//插入边
	{
		int Vertex1Address = -1;
		int Vertex2Address = -1;
		for (int i = 0; i < VertexNumber; i++)
		{
			if (AllVertex[i].Data== Vertex1)
			{
				Vertex1Address = i;
				break;
			}
		}
		for (int i = 0; i < VertexNumber; i++)
		{
			if (AllVertex[i].Data == Vertex2)
			{
				Vertex2Address = i;
				break;
			}
		}
		if (Vertex1Address!=-1 && Vertex2Address!=-1)
		{
			Edge *CurrentEdge = AllVertex[Vertex1Address].LinkEdge;     //当前位置
			while (CurrentEdge != NULL)                                 //找到末尾位置
			{
				if (CurrentEdge->AnotherAddress != Vertex2Address)//检验是否重复
				{
					CurrentEdge = CurrentEdge->link;
				}
				else
				{
					return false;  //重复
				}
			}

			CurrentEdge = new Edge;
			CurrentEdge->AnotherAddress = Vertex2Address;
			CurrentEdge->Weight = weight;
			CurrentEdge->link = AllVertex[Vertex1Address].LinkEdge; //在链表头插入
			AllVertex[Vertex1Address].LinkEdge = CurrentEdge;       //

			Edge *CurrentEdge2=new Edge;                         //另一个点
			CurrentEdge2->AnotherAddress = Vertex1Address;
			CurrentEdge2->Weight = weight;
			CurrentEdge2->link = AllVertex[Vertex2Address].LinkEdge;//在链表头插入
			AllVertex[Vertex2Address].LinkEdge = CurrentEdge2;      //

			EdgeNumber++;
			return true;
		}
		return false;
	}	
	bool InsertVertex(char data)//插入顶点
	{
		for (int i = 0; i < VertexNumber; i++)
		{
			if (data == AllVertex[i].Data)
			{
				return false;
			}
		}

		if (VertexNumber < MaxVertexNumber)
		{			
			VertexNumber++;
			AllVertex[VertexNumber - 1].Data = data;
			AllVertex[VertexNumber - 1].Address = VertexNumber - 1;
			return true;
		}
		return false;
	}

	bool DFS(char BeginData)
	{
		int CurrentVertex = -1;                  //找到起始位置
		for (int i = 0; i < VertexNumber; i++)
		{
			if (AllVertex[i].Data == BeginData)
			{
				CurrentVertex = i;
				break;
			}
		}
		if (CurrentVertex == -1)
		{
			return false;
		}

		int *IfVisit = new int[VertexNumber];      //判断是否被访问，数组
		char *VisitQueue = new char[VertexNumber]; //访问的次序数组
		for (int i = 0; i < VertexNumber; i++)
		{
			IfVisit[i] = 0;                        //初始为未被访问，为0
		}

		stack<Vertex> VertexStack;                 //顶点栈
		int VisitedNumber = 0;                     //已被访问顶点的个数
		Edge *CurrentEdge;                         //邻接顶点
		do
		{
			if (IfVisit[CurrentVertex] != 1)                                  //当前顶点未被访问
			{
				IfVisit[CurrentVertex] = 1;                                   //访问	
				VisitQueue[VisitedNumber] = AllVertex[CurrentVertex].Data;    //访问
				VisitedNumber++;
				VertexStack.InsertFirst(AllVertex[CurrentVertex]);            //顶点入栈	
				CurrentEdge = AllVertex[CurrentVertex].LinkEdge;              //当前的邻接顶点 
				while (CurrentEdge != NULL)                                   //找到第一个未被访问的邻接顶点
				{
					if (IfVisit[CurrentEdge->AnotherAddress] == 1)
					{
						CurrentEdge = CurrentEdge->link;
					}
					else
					{
						break;
					}
				}
				if (CurrentEdge != NULL)                              //如果当前顶点存在未被访问的邻接顶点
				{
					CurrentVertex = CurrentEdge->AnotherAddress;      //下一个顶点
				}
			}
			else                                                      //当前顶点被访问过
			{
				VertexStack.RemoveFirst();		
				Edge *CurrentEdge= VertexStack.GetTopData().LinkEdge;
				while (CurrentEdge != NULL)
				{
					if (IfVisit[CurrentEdge->AnotherAddress] == 1)
					{
						CurrentEdge = CurrentEdge->link;
					}
					else
					{
						CurrentVertex = CurrentEdge->AnotherAddress;
						break;
					}			
				}
				if (CurrentEdge = NULL)
				{
					CurrentVertex = VertexStack.GetTopData().Address;
				}
			}
		} while (!VertexStack.IfEmpty());

		for (int i = 0; i < VertexNumber; i++)
		{
			cout << VisitQueue[i] << " ";
		}
		return true;
	}
	bool BFS(char BeginData)
	{
		int CurrentVertex = -1;                    //找到起始位置
		for (int i = 0; i < VertexNumber; i++)
		{
			if (AllVertex[i].Data == BeginData)
			{
				CurrentVertex = i;
				break;
			}
		}
		if (CurrentVertex == -1)
		{
			return false;
		}

		int *IfVisit = new int[VertexNumber];      //判断是否被访问
		char *VisitQueue = new char[VertexNumber]; //访问的次序
		for (int i = 0; i < VertexNumber; i++)
		{
			IfVisit[i] = 0;                        //初始为未被访问
		}
		Queue<Edge *> VertexQueue;                 //顶点队列
		int VisitedNumber = 0;                     //已被访问顶点的个数
		Edge*CurrentEdge;                         //邻接顶点
		do
		{
			IfVisit[CurrentVertex] = 1;                                   //访问	
			VisitQueue[VisitedNumber] = AllVertex[CurrentVertex].Data;    //存入输出数组
			VisitedNumber++;
			CurrentEdge = AllVertex[CurrentVertex].LinkEdge;
			while (CurrentEdge != NULL)
			{
				if (IfVisit[CurrentEdge->AnotherAddress] != 1)
				{				
					VertexQueue.Insert(CurrentEdge);
					IfVisit[CurrentEdge->AnotherAddress] = 1;
				}			
				CurrentEdge = CurrentEdge->link;
			}
			if (!VertexQueue.IfEmpty())
			{
				CurrentVertex = VertexQueue.GetTopData()->AnotherAddress;
				VertexQueue.Remove();
			}			
		} while (VisitedNumber != VertexNumber);

		for (int i = 0; i < VertexNumber; i++)
		{
			cout << VisitQueue[i] << " ";
		}
		return true;
	}

	void OutPut()
	{
		Edge *CurrentEdge;
		for (int i = 0; i < VertexNumber; i++)
		{
			cout <<AllVertex[i].Data<< ": ";
			CurrentEdge=AllVertex[i].LinkEdge;
			while (CurrentEdge != NULL)
			{
				cout << AllVertex[CurrentEdge->AnotherAddress].Data << " ";
				CurrentEdge = CurrentEdge->link;
			}
			cout << endl;
		}
	}
};


