#ifndef LIST_H
#define LIST_H

#endif // LIST_H
#include<QString>
using namespace std;


struct Node
{
    QString URL;
    int Name;
    QString Time;
    Node *link;          //连接
    Node()               //默认构造
    {
        link = NULL;
    }
    Node(int name,QString url,QString time)//构造并写入数据
    {
        Name=name;
        URL=url;
        Time=time;
        link = NULL;
    }
};


class Queue
{
protected:
    Node *first;                //初始节点
    Node *last;                 //尾节点
    int Length;
public:
    Queue()
    {
        Length = 0;
        first = new Node();
        last = new Node();

        first->link = NULL;
        last->link = NULL;
    }

    void Empty()                   //清空
    {
        Node *current = NULL;
        if (first->link == NULL)
        {
            return;
        }
        while (first->link != NULL)
        {
            current = first->link;
            first->link = current->link;
            delete current;
        }
    }

    bool Insert(int name,QString url,QString time)                 //插入
    {
        Length++;
        Node *NewNode = new Node(name,url,time);   //创建新的节点 ,存入数据
        if (last->link != NULL)
        {
            last->link->link = NewNode;
            last->link = NewNode;
        }
        else
        {
            first->link = NewNode;
            last->link = NewNode;
        }
        return true;
    }


    Node* GetTop()
    {
        if (first->link != last)
        {
            return first->link;
        }
        else
        {
            return first;
        }
    }
    Node* GetLast()
    {
        if (last->link != NULL)
        {
            return last->link;
        }
        else
        {
            return last;
        }
    }

    bool IfEmpty()                   //判断是否为空
    {
        if (first->link == last)
        {
            return true;
        }
        else
        {
            return false;
        }
    }


    Node* GetFirst()
    {
        return first;
    }

    int Find(QString url)
    {
        int Count=0;
        Node *CurrentNode;
        if(first->link!=NULL)
        {
            CurrentNode=first->link;
        }
        else
        {
            return -1;
        }

        while(CurrentNode!=NULL)
        {
            if(CurrentNode->URL==url)
            {
                return Count;
            }
            else
            {
                Count++;
                if(CurrentNode->link!=NULL)
                {
                    CurrentNode=CurrentNode->link;
                }
                else
                {
                    CurrentNode=NULL;
                }
            }
        }

        return -1;
    }
};







