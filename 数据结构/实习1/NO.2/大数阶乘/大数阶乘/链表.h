#pragma once

using namespace std;


 


struct Node
{
	int Data;            //数据
	Node *link;          //连接
	Node *BackLink;

	Node()               //默认构造
	{
		link = NULL;
		BackLink = NULL;
	}
	Node(int data)       //构造并写入数据
	{
		Data = data;
		link = NULL;
		BackLink = NULL;
	}

};

class List
{
protected:
	Node *first;                    //初始节点
	Node *last;
public:
	List()
	{
		first = new Node(0);
		last = new Node(0);

		first->link = last;
		last->BackLink = first;
		last->link = NULL;
		first->BackLink = NULL;
	}

	void Empty()                   //清空
	{
		Node *current;

		if (first->link == last)
		{
			return;
		}
		while (first->link != last)
		{
			current = first->link;
			first->link = current->link;
			delete current;
		}

	}

	~List()                         //析构
	{
		Empty();
		delete first;
		delete last;
	}


	int Length()                     //链表长度
	{
		int length = 0;              //起始长度
		Node *current;               //当前节点
		current = first->link;       //初始节点与当前计数位置一致
		while (current != NULL)      //判断长度是否截至
		{
			current = current->link; //指向下一个节点
			length++;                //自加
		}
		return length;
	}


	bool Insert(int position, int data)               //在第i个元素后插入
	{
		Node *current = first;                        //当前位置，初始位置为起始节点。

		for (int i = 1; i<position; i++)                   //将“当前位置”指向要求位置
		{
			if (current != last)
			{
				current = current->link;              //指向下一个节点
			}
		}

		if (current == last )     //如果插入位置大于链表长度，且链表不为空
		{
			return false;
		}
		else                                          //链表为空，或者插入位置小于链表长度
		{
			Node *NewNode = new Node(data);           //创建新的节点 ,存入数据  
			NewNode->link = current->link;            //将插入点之后的链表与其进行连接
			current->link = NewNode;                  //将插入点之前的链表与其进行连接

		    
			NewNode->BackLink = current;
			NewNode->link->BackLink = NewNode;

			//cout<< NewNode->Data << endl;
			//cout << NewNode->BackLink->Data << endl;
		}

		return true;
	}



	Node *GetFirstNode()
	{
		return first;
	}
	
	Node *GetLastNode()
	{
		return last;
	}


	bool Inverse(Node *node)                   //逆置
	{
		Node *current = first->link;
		Node *LinkNode1;
		Node *LinkNode2 = NULL;

		while (current != NULL)
		{
			LinkNode1 = current->link;
			current->link = LinkNode2;
			LinkNode2 = current;                  /////////////

			current = LinkNode1;
		}
		first->link = LinkNode2;

		return true;
	}
	
	

	/*bool FactorialOutPutReverse(Node *node)                    //大数阶乘，顺序递归输出,  list.GetFirstNode()->link
	{

		if (node != NULL)
		{
			FactorialOutPutReverse(node->link);

			if (node->link != NULL)
			{
				if (node->Data >= 100)
				{
					cout << node->Data << " ";
				}
				else if (10 <= node->Data && node->Data < 100)
				{
					cout << 0 << node->Data << " ";
				}
				else if (0 <= node->Data && node->Data < 10)
				{
					cout << 0 << 0 << node->Data << " ";
				}
			}
			else
			{
				cout << node->Data << " ";
			}

		}
		return true;
	}*/
};
