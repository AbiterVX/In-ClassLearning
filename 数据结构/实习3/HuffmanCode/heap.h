#ifndef HEAP_H
#define HEAP_H
#endif // HEAP_H
#include<algorithm>
#include<iostream>
#include<time.h>
#include <fstream>
#include <sstream>
#include<Windows.h>
using namespace std;







struct TreeNode
{
    long long Weight;             //次数
    //string HufmanCode;          //Hufman编码
    unsigned int CompressCode=0;  //Hufman编码，int数值型
    int CodeLength=0;             //编码长度
    unsigned char Data;           //当前的char值

    TreeNode* LeftChild;          //左child
    TreeNode* RightChild;         //右child
    TreeNode* Parent=NULL;        //  parent

    TreeNode()
    {
        LeftChild = NULL;
        RightChild = NULL;

    }
    TreeNode(long long weight, unsigned char data,
        TreeNode* leftChild = NULL, TreeNode* rightChild = NULL)
    {
        Weight= weight;
        Data = data;
        LeftChild = leftChild;
        RightChild = rightChild;
    }
};


class Heap
{
private:
    TreeNode**Data=new TreeNode*[257];     //数组
    int Length=0;         //长度

public:
    Heap()
    {
        Length = 0;
    }
    Heap(TreeNode **data, int TotalNumber) //构造
    {
        Data = data;                       //导入数据
        Length = TotalNumber - 1;          //舍弃第【0】个，将下标对应。
    }

    void SetLength(int length)
    {
        Length = length;
    }

    void HeapAdjust(int CurrentNumber, int length)          //调整一次，得到最小值，即顶部
    {
        int CurrentMin = CurrentNumber;                     //当前最大
        int LeftChild = CurrentNumber * 2;                  //左child
        int RightChild = CurrentNumber * 2 + 1;             //右child

        if (CurrentNumber <= length / 2)                                    //如果当前小于总长
        {
            if (LeftChild <= length && Data[LeftChild]->Weight < Data[CurrentMin]->Weight)  //如果左child不为叶节点，
            {                                                                               //且大于当前的数值，
                CurrentMin = LeftChild;                                                     //则当前最大变为左child
            }
            if (RightChild <= length && Data[RightChild]->Weight < Data[CurrentMin]->Weight)//如果右child不为叶节点，
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
    TreeNode* GetTop()
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
    void Insert(TreeNode *NewNode)
    {
        Data[Length + 1] = NewNode;
        Length++;
    }
    void OutPut()
    {
        for (int i = Length; i > 0; i--)
        {
            cout << Data[i]->Weight << " ";
        }
        cout << endl;
    }
};




