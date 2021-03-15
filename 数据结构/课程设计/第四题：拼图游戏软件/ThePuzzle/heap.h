#ifndef HEAP_H
#define HEAP_H

#endif // HEAP_H


#include<algorithm>
#include<QVector>
using namespace std;

struct Step
{
    int Count;
    int Cost;
    int From;
    int **Puzzle;
    Step *Parent;
    int EmptyX;
    int EmptyY;
    Step(int count,int Row,int Column,int**puzzle,Step*parent=NULL)
    {
        Parent=parent;
        Cost=0;
        Count=count;
        Puzzle=new int*[Row];
        for(int i=0;i<Row;i++)
        {
            Puzzle[i]=new int[Column];
            for(int j=0;j<Column;j++)
            {
                Puzzle[i][j]=puzzle[i][j];
            }
        }
    }


};



class Heap
{
private:
    QVector<Step*> Queue;
    int Length;
    void HeapAdjust(int CurrentNumber, int length)          //调整一次，得到最小值，即顶部
    {
        int CurrentMin = CurrentNumber;                     //当前min
        int LeftChild = CurrentNumber * 2;                  //左child
        int RightChild = CurrentNumber * 2 + 1;             //右child

        if (CurrentNumber <= length / 2)                                    //如果当前小于总长
        {
            if (LeftChild <= length &&  Queue[LeftChild]->Cost< Queue[CurrentMin]->Cost)  //如果左child不为叶节点，
            {                                                                               //且大于当前的数值，
                CurrentMin = LeftChild;                                                     //则当前最大变为左child
            }
            if (RightChild <= length && Queue[RightChild]->Cost < Queue[CurrentMin]->Cost)//如果右child不为叶节点，
            {                                                                              //且大于当前的数值，
                CurrentMin = RightChild;                                                   //则当前最大变为右child
            }

            if (CurrentMin != CurrentNumber)                                //交换数值
            {
                swap(Queue[CurrentMin], Queue[CurrentNumber]);
                HeapAdjust(CurrentMin, length);
            }
        }
    }

public:
    Heap(Step* Begin)
    {
        Length = 0;
        Queue.push_back(Begin);
    }

    void BuildHeap()
    {
        for (int i = Length / 2; i >= 1; i--)
        {
            HeapAdjust(i, Length);
        }
    }

    Step* GetTop()
    {
        BuildHeap();
        return Queue[1];
    }

    bool PopTop()
    {
        if (Length > 1)
        {
            Queue[1] = Queue[Length];
            HeapAdjust(1, Length--);
            Queue.pop_back();
            return true;
        }
        else if (Length = 1)
        {
            Length = 0;
            Queue.pop_back();
        }
        else
        {
            return false;
        }
    }
    void Insert(Step *NextStep)
    {
        Queue.push_back(NextStep);
        Length++;
    }


};

