#ifndef MINPATH_H
#define MINPATH_H
#endif // MINPATH_H

#include<QString>
#include<QPoint>
#define Max 2147483647
struct Node
{
    int PositionX;
    int PositionY;
    QString Name;
    QString Data;
    //char *Name;
    //char *Data;
    Node()
    {
        PositionX = 0;
        PositionY = 0;
        //Name = new char[20];
        //Data = new char[40];
    }
};


class Graph
{
private:
    int MaxVertex;      //最大点个数
    int VertexNumber;   //点的个数
    int EdgeNumber;     //边的个数
    Node *VertexS;     //顶点
    double **Edge;      //边

    int *PathS;

public:
    Node *Path;
    int PathNumber;
    double *PathLength;
    double Sum;


    int GetEdgeNumber()
    {
        return EdgeNumber;
    }

    QPoint GetVertex(QString name)
    {
        int current=find(name);
        return QPoint(VertexS[current].PositionX,VertexS[current].PositionY);
    }


    Graph(int Vertexnumber)
    {
        VertexS = new Node[Vertexnumber];
        MaxVertex = Vertexnumber;
        VertexNumber = 0;
        EdgeNumber = 0;
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
    bool InsertEdge(QString Vertex1,QString Vertex2, double weight = Max) //插入边
    {              /*char *Vertex1, char *Vertex2*/
        int VertexAddress1 = -1;
        int VertexAddress2 = -1;
        for (int i = 0; i < VertexNumber; i++)
        {
            if (Vertex1 == VertexS[i].Name)
            {
                VertexAddress1 = i;
                break;
            }
        }
        for (int i = 0; i < VertexNumber; i++)
        {
            if (Vertex2 == VertexS[i].Name)
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
    bool InsertEdge(int Vertex1, int Vertex2, double weight = Max)//插入边
    {
        if (Vertex1 >= 0 && Vertex1<VertexNumber &&Vertex2 >= 0 && Vertex2<VertexNumber)
        {
            Edge[Vertex1][Vertex2] = weight;
            Edge[Vertex2][Vertex1] = weight;
            EdgeNumber++;
            return true;
        }
        return false;
    }
    bool InsertVertex(QString name,int X,int Y,QString data)//插入顶点
    {                 /*char *name  char*data */
        if (VertexNumber == MaxVertex)
        {
            return false;
        }

        VertexS[VertexNumber].Name = name;
        VertexS[VertexNumber].Data = data;
        VertexS[VertexNumber].PositionX = X;
        VertexS[VertexNumber].PositionY = Y;
        VertexNumber++;
        return false;
    }
    double GetWeight(QString Vertex1, QString Vertex2)
    {               /*char *Vertex1, char *Vertex2*/
        int VertexAddress1 = -1;
        int VertexAddress2 = -1;
        for (int i = 0; i < VertexNumber; i++)
        {
            if (Vertex1 == VertexS[i].Name)
            {
                VertexAddress1 = i;
                break;
            }
        }
        for (int i = 0; i < VertexNumber; i++)
        {
            if (Vertex2 == VertexS[i].Name)
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
    double GetWeight(int Vertex1,int Vertex2)
    {
        if (Vertex1>=0 && Vertex1<VertexNumber && Vertex2 >= 0 && Vertex2<VertexNumber)
        {
            return Edge[Vertex1][Vertex2];
        }
        return -1;
    }
    int find(QString Vertex)
    {       /* char *Vertex*/
        int VertexAddress = -1;
        for (int i = 0; i < VertexNumber; i++)
        {
            if (Vertex == VertexS[i].Name)
            {
                VertexAddress = i;
                break;
            }
        }
        if (VertexAddress != -1)
        {
            return VertexAddress;
        }
        return -1;
    }

    void ShortestPath(QString start,QString destination)
    {                /*char *start,char *destination*/
        PathNumber=0;
        Path = new Node[VertexNumber];
        PathLength = new double[VertexNumber];

        int Start=find(start);
        int Destination=find(destination);
        bool *IfJoin = new bool[VertexNumber];      //加入集合
        PathS = new int[VertexNumber];         //存储起始点到目的点的经历点，路径
        double *Length = new double[VertexNumber];  //每个点到start点的最短长度
        for (int i = 0; i < VertexNumber; i++)      //初始化
        {
            Length[i] = Edge[find(start)][i];       //起点到每个点的距离，长度
            IfJoin[i] = 0;                          //每个点都未加入集合
            if (i != Start && Length[i] != Max)     //直接相连，路径为起始点。
            {
                PathS[i] = Start;
            }
            else
            {
                PathS[i] = -1;                      //没有直接相连，标记为-1
            }
        }
        IfJoin[Start] = 1;                          //起始点加入集合
        Length[Start] = 0;                          //起始点到自己的距离为0

        double CurrentMinLength;                    //当前最短距离
        int CurrentVertex;                          //当前顶点
        double CurrentLength = 0;                   //当前距离
        for (int i = 0; i < VertexNumber-1; i++)
        {
            CurrentMinLength = Max;
            CurrentVertex = Start;
            for (int j = 0; j < VertexNumber; j++)  //选择当前距离最短的点
            {
                if (IfJoin[j]!=1 && Length[j]<CurrentMinLength)
                {
                    CurrentVertex = j;
                    CurrentMinLength = Length[j];
                }
            }
            IfJoin[CurrentVertex] = 1;               //当前最小，加入集合

            for (int k = 0; k < VertexNumber; k++)
            {
                CurrentLength = Edge[CurrentVertex][k];
                if (IfJoin[k] != 1 && CurrentLength <Max &&
                    Length[CurrentVertex] + CurrentLength < Length[k])
                {
                    Length[k] = Length[CurrentVertex] + CurrentLength;
                    PathS[k] = CurrentVertex;
                }
            }
        }

        Sum = 0;
        int current = Destination;
        for (int i = 0; i < VertexNumber; i++)
        {
            //cout<<"点："<<PathS[current]<<"  名称："<<VertexS[current].Name << "  信息：" << VertexS[current].Data << "  X坐标：" <<
            //	                       VertexS[current].PositionX << "  Y坐标：" << VertexS[current].PositionY<<endl;
            if (PathS[current] != -1)
            {
                Sum += GetWeight(current, PathS[current]);
                //cout << GetWeight(current, PathS[current]) << endl;
            }
            current = PathS[current];
            if (current == -1)
            {
                break;
            }
        }
        //cout << Sum << endl;
        GetPath(Destination);
    }
    void GetPath(int current)
    {
        if (current != -1)
        {
            GetPath(PathS[current]);
            Path[PathNumber] = VertexS[current];
            PathLength[PathNumber] = GetWeight(current, PathS[current]);
            PathNumber++;
        }
    }


    Node *RealVertex;
    int RealVertexNumber;
    void GetRealVerTex()
    {
        RealVertexNumber = 0;
        RealVertex = new Node[VertexNumber];
        for (int i = 0; i < VertexNumber; i++)
        {
            if (VertexS[i].Name[0] != '#')
            {
                RealVertex[RealVertexNumber] = VertexS[i];
                RealVertexNumber++;
            }
        }
    }

    double **GetEdgeS()
    {
        return Edge;
    }
};
