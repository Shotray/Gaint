//单项链表

#include<iostream>

class List;

class ListNode {
	friend List;
public:
	void PrintNode();
private:
	int _data;
	ListNode* _next;
};

void ListNode::PrintNode()
{
	std::cout << this->_data << std::endl;
	return;
}

class List {
//创建、插入、删除、查找、算总数
public:
	void Create();
	void Insert();
	void Delete();
	ListNode* Search(int i);
	int Count();
	void Print();
private:
	ListNode* _first;
	ListNode* _last;
};

void List::Create()
{
	int data;
	ListNode* p = new ListNode;
	_first = p;
	_first->_data = 0;
	std::cout << "请输入数据，按-1结束输入:";
	std::cin >> data;
	while (std::cin.good())
	{
		if (data == -1)
		{
			break;
		}
		ListNode* q = new ListNode;
		p->_next = q;
		q->_data = data;
		p = q;
		std::cout << "请输入数据，按-1结束输入:";
		std::cin >> data;
	}
	_last = p;
	p->_next = NULL;
	return;
}


void List::Insert()
{
	ListNode* p=new ListNode;
	int i;
	int data;
	std::cout << "请输入要插入的数据：";
	std::cin >> data;
	p->_data = data;
	std::cout << "请输入要插入的位置：";
	std::cin >> i;

	int length = this->Count();
	if (i <= 0 || i > length+1)
	{
		std::cerr << "输入过大/过小，无法查找";
	}
	//存在两种方法判断插入是否是首位/末位
	//1、通过i和count结果来判断
	//2、末尾通过NULL来判断，首位不需要改变，有一个first指针
	ListNode* previous;
	previous = this->Search(i - 1);
	p->_next = previous->_next;
	previous->_next = p;

	//方法一
	if (p->_next == NULL) {
		_last = p;
	}

	//方法二
	/*if (i == length+1){
		_last = p;
	}*/
	return;
}

void List::Delete()
{
	int i;
	std::cout << "请输入想要删除的位置：";
	std::cin >> i;

	ListNode* q = this->Search(i);
	ListNode* previous = this->Search(i-1);
	previous->_next = q->_next;
	if (q->_next == NULL)
	{
		_last = previous;
	}
	delete q;
	return;
}

ListNode* List::Search(int i)
{
	ListNode* p;
	//小bug 用户查找0的时候可以查找到我的空链表头
	if (i < 0 || i > this->Count())
	{
		std::cerr << "输入过大/过小，无法查询" << std::endl;
	}
	p = _first;
	for (int j = 1; j <= i; j++)
	{
		p = p->_next;
	}
	return p;
}

int List::Count()
{
	ListNode* p;
	p = _first->_next;
	int count = 0;
	while (p != NULL)
	{
		count++;
		p = p->_next;
	}
	return count;
}

void List::Print()
{
	ListNode* p;
	p = _first->_next;
	while (p != NULL)
	{
		std::cout << "data:" << p->_data << std::endl;
		p = p->_next;
	}
	return;
}

int main(void)
{
	List li;
	int i;
	ListNode* p;
	li.Create();
	std::cout << "共有" << li.Count() << "个数据,";
	std::cout << "请输入想要查询的数据：";
	std::cin >> i;
	p = li.Search(i);
	p->PrintNode();
	li.Insert();
	li.Delete();
	li.Print();
	return 0;
}