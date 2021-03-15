#ifndef MSTGRAPH_H
#define MSTGRAPH_H

#endif // MSTGRAPH_H

#include"mstheap.h"

class UFSets
{
private:
    int *Data;
    int Size;
public:
    UFSets(int size)
    {
        Size = size;
        Data = new int[Size];
        for (int i = 0; i < Size; i++)
        {
            Data[i] = -1;
        }
    }
    void Union(int child, int parent)
    {
        if (child >= 0 && child < Size  && parent>=0 && parent < Size)
        {
            int count = 0;
            if (Data[child] < 0)
            {
                count = Data[child];
            }
            Data[child] = parent;
            int Parent = Find(parent);
            Data[Parent] = Data[Parent] + count;
        }
    }
    int Find(int child)
    {
        int parent;
        int count = 1;
        while (count < Size)
        {
            if (Data[child] < 0)
            {
                parent = child;
                break;
            }
            else
            {
                child = Data[child];
            }
            count++;
        }
        return parent;
    }
    void OutPut()
    {
        for (int i = 0; i < Size; i++)
        {
            cout << Data[i] << " ";
        }
        cout << endl;
    }
};



class Graph
{
private:
    int MaxVertex;
    int VertexNumber;   //点的个数
    int EdgeNumber;     //边的个数
    char *VertexS;  //顶点
    double **Edge;   //边


public:
    Graph()
    {
        VertexNumber = 0;
        EdgeNumber = 0;
    }
    void BuildGraph(int Vertexnumber)
    {
        VertexS = new char[Vertexnumber];
        MaxVertex = Vertexnumber;
        Edge = new double*[MaxVertex];
        for (int i = 0; i < MaxVertex; i++)
        {
            Edge[i] = new double[MaxVertex];
            for (int j = 0; j < MaxVertex; j++)
            {
                if (i != j)
                {
                    Edge[i][j] = Max;
                }
                else
                {
                    Edge[i][j] = 0;
                }
            }
        }
    }
    Graph(int Vertexnumber)
    {
        BuildGraph(Vertexnumber);
        VertexNumber = 0;
        EdgeNumber = 0; 
    }
    //~Graph() {}
    int GetVertexNumber()
    {
        return VertexNumber;
    }
    char *GeTVertexS()
    {
        return VertexS;
    }

    bool InsertEdge(char Vertex1, char Vertex2, double weight =Max)//插入边
    {
        int VertexAddress1 = -1;
        int VertexAddress2 = -1;
        for (int i = 0; i < VertexNumber; i++)
        {
            if (Vertex1 == VertexS[i])
            {
                VertexAddress1 = i;
                break;
            }
        }
        for (int i = 0; i < VertexNumber; i++)
        {
            if (Vertex2 == VertexS[i])
            {
                VertexAddress2 = i;
                break;
            }
        }
        if (VertexAddress1 != -1 && VertexAddress2 != -1)
        {
            Edge[VertexAddress1][VertexAddress2] = weight;
            Edge[VertexAddress2][VertexAddress1] = weight;
            EdgeNumber++;
            return true;
        }
        return false;
    }
    void InsertAllEdge(double **Data)
    {
        for (int i = 0; i < VertexNumber; i++)
        {
            for (int j = 0; j < VertexNumber; j++)
            {
                Edge[i][j]=Data[i][j];
                if(Data[i][j]!=Max &&i!=j)
                {
                    EdgeNumber++;
                }
            }
        }
    }
    bool InsertEdge(int Vertex1, int Vertex2, double weight = Max)//插入边
    {
        if (Vertex1>=0 && Vertex1<VertexNumber &&Vertex2>=0 && Vertex2<VertexNumber)
        {
            Edge[Vertex1][Vertex2] = weight;
            Edge[Vertex2][Vertex1] = weight;
            EdgeNumber++;
            return true;
        }
        return false;
    }
    bool InsertVertex(char data)//插入顶点
    {
        if (VertexNumber == MaxVertex)
        {
            return false;
        }
        VertexS[VertexNumber++] = data;
        return false;
    }
    double GetWeight(char Vertex1, char Vertex2)
    {
        int VertexAddress1 = -1;
        int VertexAddress2 = -1;
        for (int i = 0; i < VertexNumber; i++)
        {
            if (Vertex1 == VertexS[i])
            {
                VertexAddress1 = i;
                break;
            }
        }
        for (int i = 0; i < VertexNumber; i++)
        {
            if (Vertex2 == VertexS[i])
            {
                VertexAddress2 = i;
                break;
            }
        }
        if (VertexAddress1 != -1 && VertexAddress2 != -1)
        {
            return Edge[VertexAddress1][VertexAddress2];
        }
        return false;
    }


    Node* Kruskal()
    {
        Node *MST = new Node[VertexNumber - 1];       //返回值
        Heap heap(EdgeNumber);                  //堆
        Node CurrentNode;                             //辅助节点
        for (int i = 0; i < VertexNumber; i++)        //初始化，将所有边进行堆排序
        {
            for (int j = i + 1; j < VertexNumber; j++)
            {
                if (Edge[i][j] !=Max)
                {
                    CurrentNode.FirstAddress = i;
                    CurrentNode.SecondAddress = j;
                    CurrentNode.Weight = Edge[i][j];
                    heap.Insert(CurrentNode);
                }
            }
        }

        heap.BuildHeap();
        //heap.OutPut();
        UFSets unsets(VertexNumber);  //并查集
        int EdgeStart;
        int EdgeEnd;
        int EdgeWeight;
        int count = 1;                                  //初始点为1个
        while (count < VertexNumber)
        {
            CurrentNode = heap.GetTop();
            heap.PopTop();

            EdgeStart=unsets.Find(CurrentNode.FirstAddress);  //查找该边的起始顶点的集合
            EdgeEnd= unsets.Find(CurrentNode.SecondAddress);  //查找该边的终止顶点的集合
            if (EdgeStart != EdgeEnd)                           //不再同一集合内
            {
                unsets.Union(EdgeStart, EdgeEnd);
                //unsets.OutPut();
                MST[count-1] = CurrentNode;
                count++;
            }
        }
        return MST;
    }

};



