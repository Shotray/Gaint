//单向链表（模板）

#include<iostream>

template<class T> class List;

template<class T>
class ListNode {
	friend List<T>;
public:
	void PrintNode();
private:
	T _data;
	ListNode* _next;
};

template<class T>
void ListNode<T>::PrintNode()
{
	std::cout << this->_data << std::endl;
	return;
}

template<class T>
class List {
//创建、插入、删除、查找、算总数
public:
	List() = default;
	~List();
	void Create();
	void Insert();
	void Remove();

	ListNode<T>* Search(int i);//用重载[]
	int operator[](const int i);

	int Size();
	void Print();
private:
	ListNode<T>* _first;
	ListNode<T>* _last;
};

template<class T>
List<T>::~List()
{
	ListNode<T>* p = _first;
	while (p != NULL)
	{
		ListNode<T>* q = p;
		p = p->_next;
		delete q;
	}
	return;
}

template<class T>
void List<T>::Create()
{
	int data;
	ListNode<T>* p = new ListNode<T>;
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
		ListNode<T>* q = new ListNode<T>;
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

template<class T>
void List<T>::Insert()
{
	ListNode<T>* p=new ListNode<T>;
	int i;
	int data;
	std::cout << "请输入要插入的数据：";
	std::cin >> data;
	p->_data = data;
	std::cout << "请输入要插入的位置：";
	std::cin >> i;

	int length = this->Size();
	if (i <= 0 || i > length+1)
	{
		std::cerr << "输入过大/过小，无法查找";
	}
	//存在两种方法判断插入是否是首位/末位
	//1、通过i和count结果来判断
	//2、末尾通过NULL来判断，首位不需要改变，有一个first指针
	ListNode<T>* previous;
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

template<class T>
void List<T>::Remove()
{
	int i;
	std::cout << "请输入想要删除的位置：";
	std::cin >> i;

	ListNode<T>* q = this->Search(i);
	ListNode<T>* previous = this->Search(i-1);
	previous->_next = q->_next;
	if (q->_next == NULL)
	{
		_last = previous;
	}
	delete q;
	return;
}

template<class T>
ListNode<T>* List<T>::Search(int i)
{
	ListNode<T>* p;
	//小bug 用户查找0的时候可以查找到我的空链表头
	if (i < 0 || i > this->Size())
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

template<class T>
int List<T>::operator[](const int pos)
{
	ListNode<T>* p;
	//小bug 用户查找0的时候可以查找到我的空链表头
	if (pos < 0 || pos > this->Size())
	{
		std::cerr << "输入过大/过小，无法查询" << std::endl;
	}
	p = _first;
	for (int j = 1; j <= pos; j++)
	{
		p = p->_next;
	}
	return p->_data;
}

template<class T>
int List<T>::Size()
{
	ListNode<T>* p;
	p = _first->_next;
	int count = 0;
	while (p != NULL)
	{
		count++;
		p = p->_next;
	}
	return count;
}

template<class T>
void List<T>::Print()
{
	ListNode<T>* p;
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
	List<int> li;
	int i;
	ListNode<int>* p;
	li.Create();
	std::cout << "共有" << li.Size() << "个数据,";
	std::cout << "请输入想要查询的数据：";
	std::cin >> i;
	std::cout << li[i];
	p = li.Search(i);
	p->PrintNode();
	li.Insert();
	li.Remove();
	li.Print();
	return 0;
}