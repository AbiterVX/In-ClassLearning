#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#endif // HUFFMANTREE_H
#include<heap.h>
using namespace std;






class HuffmanTree
{
private:
    TreeNode* Root;
    TreeNode **NodeS;
    unsigned int *Code;
    int* AllCodeLength;
    int Number=0;
    /********************************编码***************************************/
    void CreateCode()                                //Hufman编码
    {
        if (Root != NULL)
        {
            if (Root->LeftChild != NULL)
            {
                GetCode(Root->LeftChild, 0);
            }
            if (Root->RightChild != NULL)
            {
                GetCode(Root->RightChild, 1);
            }
        }
    }
    void GetCode(TreeNode * Current, int LeftOrRight)    //编码递归
    {
        Current->CodeLength = Current->Parent->CodeLength + 1;
        Current->CompressCode = Current->Parent->CompressCode << 1;
        if (LeftOrRight == 0)
        {
            unsigned int zero = 0;
            Current->CompressCode = Current->CompressCode | zero;
        }
        else
        {
            unsigned int one = 1;
            Current->CompressCode = Current->CompressCode | one;
        }

        if (Current->LeftChild == NULL && Current->RightChild == NULL)
        {
            Code[Current->Data] = Current->CompressCode;
            AllCodeLength[Current->Data] = Current->CodeLength;
        }
        else
        {
            if (Current->LeftChild != NULL)
            {
                GetCode(Current->LeftChild, 0);
            }
            if (Current->RightChild != NULL)
            {
                GetCode(Current->RightChild, 1);
            }
        }
    }

public:
    /*****************************构造*********************************/
    HuffmanTree()
    {
        Root = NULL;
    }
    HuffmanTree(int number,long long *WeightS)
    {
        Root = NULL;
        BuildTree(WeightS);
    }
    void BuildTree(long long *WeightS)
    {
        NodeS = new TreeNode*[257];       //257
        Code = new unsigned int[256];       //编码
        AllCodeLength=new int[256];

        Heap MinHeap;         //257，堆
        for (int i = 1; i <= 256; i++)      //256，存入各char的次数
        {
            NodeS[i] = new TreeNode;
            NodeS[i]->Data = i - 1;
            NodeS[i]->Weight = WeightS[i - 1];
            if (NodeS[i]->Weight != 0)
            {
                Number++;
                MinHeap.Insert(NodeS[i]);
                //cout << NodeS[i]->Weight << " ";
            }
        }




        MinHeap.BuildHeap();

        int length = Number;                   //256，堆长度
        while (length >= 2)                                          //构造Huffman树
        {
            TreeNode *FirstMInNode = MinHeap.GetTop();  //最小
            long long FirstMin = FirstMInNode->Weight;
            MinHeap.PopTop();
            TreeNode *SecondMInNode = MinHeap.GetTop(); //次小
            long long SecondMin = SecondMInNode->Weight;
            MinHeap.PopTop();
            TreeNode *Parent = new TreeNode;
            MergeTree(Parent, FirstMInNode, SecondMInNode);
            MinHeap.Insert(Parent);
            length--;

            MinHeap.HeapAdjust(1, length);
        }
        Root = MinHeap.GetTop();

        CreateCode();
    }

    void MergeTree(TreeNode *&parent,TreeNode *& tree1, TreeNode *& tree2)  //合并树
    {
        parent->LeftChild = tree1;
        parent->RightChild = tree2;
        parent->Weight = tree1->Weight + tree2->Weight;

        tree1->Parent = parent;
        tree2->Parent = parent;
    }

    unsigned int *GetAllCode()
    {
        return Code;
    }
    int * GetAllCodeLength()
    {
        return AllCodeLength;
    }


    /*string *GetAllCode()
    {
        return Code;
    }*/

    /***************************************其他*********************************************/

    /*void PreOrder(TreeNode * Current)          //前序遍历
    {
        if (Current != NULL)
        {
            if (Current->LeftChild == NULL&&Current->RightChild == NULL)
            {
                visit(Current);
            }
            PreOrder(Current->LeftChild);
            PreOrder(Current->RightChild);
        }
    }*/
   /* void visit(TreeNode * Current)             //访问
    {
        cout <<"权重："<< Current->Weight <<" 数值："<< Current->CompressCode<<" 长度："<< Current->CodeLength << endl;
    }*/
    TreeNode* GetRoot()
    {
        return Root;
    }


    /**************************************析构*************************************/
    ~HuffmanTree()
    {
        DeleteTree(Root);
    }
    void DeleteTree(TreeNode *treenode)
    {
        if (treenode != NULL)
        {
            DeleteTree(treenode->LeftChild);
            DeleteTree(treenode->RightChild);
            delete treenode;
        }
    }

};
