#ifndef MAINBINARYTREE_H
#define MAINBINARYTREE_H

#endif // MAINBINARYTREE_H


#include "queue.h"
#include "stack.h"

#include<fstream>
#include <sstream>

using namespace std;


template<typename Type>
struct TreeNode                 //树结点
{
    Type Data;                  //数据
    TreeNode<Type> *LeftChild;  //左child
    TreeNode<Type> *RightChild; //右child

    TreeNode()
    {
        LeftChild = NULL;
        RightChild = NULL;
    }

    TreeNode(Type data, TreeNode<Type> *leftchild=NULL,
                        TreeNode<Type> *rightchild=NULL )
    {
        Data = data;
        LeftChild = leftchild;
        RightChild = rightchild;
    }
};




template<class Type>
class TheBinaryTree                             //二叉树
{
private:
    TreeNode<Type> *Root;                    //根结点
    char* TreeData;  //前序建立树
    char* PREorder;  //前序遍历结果
    char* INorder;   //中序遍历结果

    int count = 0;
    void CreateBinaryTree(TreeNode<Type> *& Current) // 建立树
    {
        Type data;                                      //数据
        data = TreeData[count];                      //
        if (data != '\0')                                //未读完，读入并建立树
        {
            if (data != '#')                            //非空
            {
                Current = new TreeNode<Type>(data);     //建立结点
                                                        //cout << data << " ";
                count++;
                CreateBinaryTree(Current->LeftChild);   //建立左子树
                count++;
                CreateBinaryTree(Current->RightChild);  //建立右子树
            }
            else                                        //叶结点
            {
                Current = NULL;
            }
        }

    }


public:
    TheBinaryTree()                             // 构造函数
    {
        Root = NULL;
        /*ifstream data("CreateTreeData.txt");
        CreateBinaryTree(Root, data);
        data.close();*/
    }
    TheBinaryTree(char *data)
    {
        TreeData = data;
        CreateBinaryTree(Root);
        count = 0;
    }

    void BuildBinaryTree(char *data)
    {
            TreeData = data;
            CreateBinaryTree(Root);
            count = 0;
    }


    void Find(Type key, TreeNode<Type> * Current)    //查找
    {
        stack<TreeNode<Type>*> find;
        TreeNode<Type>* Previous=NULL;

        for (int i = 0;; i++)
        {
            if(Current != NULL)
            {
                if (Current->Data != key)
                {
                    find.InsertFirst(Current);
                    if (Current->LeftChild != NULL)
                    {
                        Current = Current->LeftChild;
                    }
                    else if(Current->RightChild !=NULL)
                    {
                        Current= Current->RightChild;
                    }
                    else
                    {
                        Current = NULL;
                    }
                }
                else
                {
                    break;
                }
            }
            else
            {
                find.RemoveFirst();
                if (Previous == find.GetTopData())
                {
                    find.RemoveFirst();
                }
                Previous = find.GetTopData();

                Current = find.GetTopData();
                Current = Current->RightChild;
            }
        }

        while (!find.IfEmpty())
        {
            visit(find.GetTopData());
            find.RemoveFirst();
        }

    }


    void ConfirmBinaryTree(char* preOrder,char* inOrder,int Length)
    {
        Root = NULL;
        PREorder = preOrder;
        INorder = inOrder;

        int prePosition =0;
        int inPosition =0;
        ConfirmSubTree(Root, prePosition, inPosition, Length);
    }

    void ConfirmSubTree(TreeNode<Type> *& Current,int prePosition, int inPosition, int Length)
    {                    //              当前节点 ，  前序的位置  ，   中序的位置  ，长度
        if (Length <= 0)
        {
            return;
        }
        Current = new TreeNode<Type>;             //建立节点
        Current->Data = PREorder[prePosition];    //传入数值

        int MidPosition= FindPosition(prePosition,Length, inPosition);      //中间的位置


        int LeftPreBegin = prePosition + 1;
        int LeftInBegin = inPosition;
        int LeftLength = MidPosition - inPosition;

        int RightPreBegin = prePosition + (MidPosition - inPosition) + 1;
        int RightINBegin = MidPosition + 1;
        int RightLength = Length - 1 - (MidPosition - inPosition);


        ConfirmSubTree(Current->LeftChild, LeftPreBegin,
                              LeftInBegin, LeftLength);

        ConfirmSubTree(Current->RightChild, RightPreBegin,
                              RightINBegin, RightLength );
    }


    int FindPosition(int prePosition, int Length,int inPosition)
    {
        int MidPosition = 0;
        for (int i = 0; i < Length; i++)
        {
            if (PREorder[prePosition] != INorder[inPosition+i])
            {
                MidPosition++;
            }
            else
            {
                break;
            }
        }
        return MidPosition+ inPosition;
    }



    void SwapTree(TreeNode<Type> * Current)
    {
        if (Current != NULL)
        {
            TreeNode<Type> *NewNode = new TreeNode<Type>;
            NewNode = Current->LeftChild;
            Current->LeftChild = Current->RightChild;
            Current->RightChild = NewNode;

            SwapTree(Current->LeftChild);
            SwapTree(Current->RightChild);
        }
    }

    TreeNode<Type>* GetRoot()  // 得到根结点
    {
        return Root;
    }


    int Depth(TreeNode<Type>* Current)
    {
        if(Current==NULL)
        {
            return 0;
        }

        int Left=1;
        int Right=1;
        Left+=Depth(Current->LeftChild);
        Right+=Depth(Current->RightChild);

        return Left>Right ?Left:Right;
    }


    /*---------------------遍历--------------------------*/

    void visit(TreeNode<Type> * Current)             //访问
    {
        fstream File("Tree.txt", ios_base::out|ios_base::app);
        File<<Current->Data <<" ";
        File.close();
    }

    void PreOrder(TreeNode<Type> * Current)          //前序遍历
    {
        if (Current != NULL)
        {
            visit(Current);
            PreOrder(Current->LeftChild);
            PreOrder(Current->RightChild);
        }
    }

    void InOrder(TreeNode<Type> * Current)           //中序遍历
    {

        if (Current != NULL)
        {
            InOrder(Current->LeftChild);
            visit(Current);
            InOrder(Current->RightChild);
        }
    }

    void PostOrder(TreeNode<Type> * Current)         //后序遍历
    {

        if (Current != NULL)
        {
            PostOrder(Current->LeftChild);
            PostOrder(Current->RightChild);
            visit(Current);
        }
    }

    void LevelOrder(TreeNode<Type> * Current)        //层次遍历
    {
        Queue<TreeNode<Type>*> NodeQueue;            //队列

        while (Current != NULL)
        {
            visit(Current);                          //访问
            if (Current->LeftChild != NULL)          //左child入队
            {
                //cout << Current->LeftChild->Data << " ";
                NodeQueue.Insert(Current->LeftChild);
            }
            if (Current->RightChild != NULL)         //右child入队
            {
                //cout << Current->RightChild->Data << " ";
                NodeQueue.Insert(Current->RightChild);
            }
            if (!NodeQueue.IfEmpty())                //出队
            {
                Current = NodeQueue.GetTopData();
                NodeQueue.Remove();
            }
            else
            {
                break;
            }
        }
    }

};



/*void CreateBinaryTree(TreeNode<Type> *& Current,ifstream &data) // 建立树
{
Type Data;                                      //数据
data >> Data;                                   //
if (!data.eof())                                //未读完，读入并建立树
{
if (Data != '#')                            //非空
{
Current = new TreeNode<Type>(Data);     //建立结点
CreateBinaryTree(Current->LeftChild);   //建立左子树
CreateBinaryTree(Current->RightChild);  //建立右子树
}
else                                        //叶结点
{
Current = NULL;
}
}
}*/
