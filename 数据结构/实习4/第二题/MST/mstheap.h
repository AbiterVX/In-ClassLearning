#ifndef MSTHEAP_H
#define MSTHEAP_H

#endif // MSTHEAP_H

#include<algorithm>
#include<iostream>
using namespace std;
#define Max 2147483647

struct Node
{
    int FirstAddress;
    int SecondAddress;
    int Weight;
    Node(int first=-1, int second=-1, int weight= Max)
    {
        FirstAddress = first;
        second = second;
        weight = weight;
    }
};

class Heap
{
private:
    Node*Data;    //数组
    int Length;                //长度
    int MaxLength;
public:
    Heap(int TotalNumber) //构造
    {
        Length = 0;
        MaxLength = TotalNumber;          //舍弃第【0】个，将下标对应。
        Data = new Node[TotalNumber + 1];
    }

    void HeapAdjust(int CurrentNumber, int length)          //调整一次，得到最小值，即顶部
    {
        int CurrentMin = CurrentNumber;                     //当前最大
        int LeftChild = CurrentNumber * 2;                  //左child
        int RightChild = CurrentNumber * 2 + 1;             //右child

        if (CurrentNumber <= length / 2)                                    //如果当前小于总长
        {
            if (LeftChild <= length && Data[LeftChild].Weight < Data[CurrentMin].Weight)  //如果左child不为叶节点，
            {                                                                               //且大于当前的数值，
                CurrentMin = LeftChild;                                                     //则当前最大变为左child
            }
            if (RightChild <= length && Data[RightChild].Weight < Data[CurrentMin].Weight)//如果右child不为叶节点，
            {                                                                              //且大于当前的数值，
                CurrentMin = RightChild;                                                   //则当前最大变为右child
            }

            if (CurrentMin != CurrentNumber)                                //交换数值
            {
                swap(Data[CurrentMin], Data[CurrentNumber]);
                HeapAdjust(CurrentMin, length);
            }
        }
    }

    void BuildHeap()
    {
        for (int i = Length / 2; i >= 1; i--)
        {
            HeapAdjust(i, Length);
        }
    }
    Node GetTop()
    {
        return Data[1];
    }

    bool PopTop()
    {
        if (Length > 1)
        {
            Data[1] = Data[Length];
            HeapAdjust(1, Length--);
            return true;
        }
        else if (Length = 1)
        {
            Length = 0;
        }
        else
        {
            return false;
        }
    }
    void Insert(Node NewNode)
    {
        if (Length < MaxLength)
        {
            Data[Length+1] = NewNode;
            Length++;
        }
    }
    void OutPut()
    {
        for (int i = Length; i > 0; i--)
        {
            cout << Data[i].Weight << " ";
        }
        cout << endl;
    }
};


