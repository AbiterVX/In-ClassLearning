#pragma once


using namespace std;


template <class T>
struct Node
{
	T Data;                 //数据
	Node<T> *link;          //连接

	Node()                  //默认构造
	{
		link = NULL;
	}
	Node(T data)            //构造并写入数据
	{
		Data = data;
		link = NULL;
	}

};


template <class T>
class Stack
{
protected:
	Node<T> *first;                //头节点
	Node<T> *last;                 //尾节点
public:
	Stack()
	{
		first = new Node<T>(0);
		last = new Node <T>(0);

		first->link = last;
		last->link = NULL;
	}

	void Empty()                   //清空
	{

		Node<T> *current = NULL;

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
	~Stack()                         //析构
	{

		Empty();
		delete first;
		//delete last;
	}

	bool InsertFirst(T data)                    //头插入
	{
		Node<T> *NewNode = new Node<T>(data);   //创建新的节点 ,存入数据  
		NewNode->link = first->link;            //将插入点之后的链表与其进行连接
		first->link = NewNode;                  //将插入点之前的链表与其进行连接

		if (first->link->link == NULL)
		{
			last->link = NewNode;
		}
		return true;
	}

	bool InsertLast(T data)                     //末尾插入
	{
		Node<T> *NewNode = new Node<T>(data);   //创建新的节点 ,存入数据 
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

	bool RemoveFirst()                         //删除
	{
		if (first->link != last)
		{
			Node<T>*DeleteNode;
			DeleteNode = first->link;
			first->link = first->link->link;  //将删除点之后的链表与之前的链表进行连接	  
			delete DeleteNode;
		}
		else
		{
			return false;
		}
		return true;
	}

	T GetTopData()
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



	Node<T>* GetFirst()
	{
		return first;
	}

	Node<T>* GetLast()
	{
		return last;
	}
};