#pragma once


using namespace std;





struct Node
{
	int Data;                 //数据
	Node *link;          //连接

	Node()                  //默认构造
	{
		link = NULL;
	}
	Node(int data)            //构造并写入数据
	{
		Data = data;
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
		first = new Node(0);
		last = new Node(0);

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

	/*~Queue()                         //析构
	{
		Empty();
		delete first;
		//delete last;
	}*/


	bool Insert(int data)                 //插入
	{
		Length++;
		Node *NewNode = new Node(data);   //创建新的节点 ,存入数据 
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
		if (first->link != last)
		{
			Node*DeleteNode;
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


	int GetTopData()
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

	int GetLastData()
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

	Node* GetLast()
	{
		return last;
	}
};
