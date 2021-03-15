#pragma once
using namespace std;

template<typename Type>
struct QueueNode
{
	Type Data;                 //数据
	QueueNode<Type> *link;          //连接

	QueueNode()                  //默认构造
	{
		link = NULL;
	}
	QueueNode(Type data)            //构造并写入数据
	{
		Data = data;
		link = NULL;
	}

};


template<typename Type>
class Queue
{
protected:
	QueueNode<Type> *first;                //初始节点
	QueueNode<Type> *last;                 //尾节点
	int Length;
public:
	Queue()
	{
		Length = 0;
		first = new QueueNode<Type>();
		last = new QueueNode<Type>();
		first->link = NULL;
		last->link = NULL;
	}
	void Empty()                   //清空
	{
		QueueNode<Type> *current = NULL;

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
	/*~Queue()                         //析构
	{
	Empty();
	delete first;
	//delete last;
	}*/
	bool Insert(Type data)                 //插入
	{
		Length++;
		QueueNode<Type> *NewNode = new QueueNode<Type>(data);   //创建新的节点 ,存入数据 
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
	bool Remove()                         //删除
	{
		Length--;
		if (first->link != NULL)
		{
			QueueNode<Type>*DeleteNode;
			DeleteNode = first->link;
			first->link = first->link->link;  //将删除点之后的链表与之前的链表进行连接	
			if (first->link == NULL)
			{
				last->link = NULL;
			}
			delete DeleteNode;
		}
		else
		{
			return false;
		}
		return true;
	}
	Type GetTopData()
	{
		if (first->link != last)
		{
			return first->link->Data;
		}
		else
		{
			return false;
		}
	}
	

	Type GetLastData()
	{
		if (last->link != NULL)
		{
			return last->link->Data;
		}
		else
		{
			return 0;
		}
	}
	bool IfEmpty()                   //判断是否为空
	{
		if (first->link == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	QueueNode<Type>* GetFirst()
	{
		return first;
	}

	QueueNode<Type>* GetLast()
	{
		return last;
	}
};
