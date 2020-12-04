#include<iostream>
#include<string>
#include<iomanip>

const int kBlankNum = 10;

class List;

class ListNode {
	friend List;
	friend std::istream& operator>>(std::istream& is, ListNode& node);
	friend std::ostream& operator<<(std::ostream& os, ListNode& node);
	ListNode() :_candidate_number(0), _name("\0"), _gender("\0"), _age(0), _category("\0"), _prev(NULL), _next(NULL) {}
public:
	void PrintNode();
private:
	int _candidate_number;
	std::string _name;
	std::string _gender;
	int _age;
	std::string _category;
	ListNode* _prev;
	ListNode* _next;
};

std::istream& operator>>(std::istream& is, ListNode& node)
{
	is >> node._candidate_number >> node._name >> node._gender >> node._age >> node._category;
	if (std::cin.eof())	return is;
	if (std::cin.fail()) {
		std::cerr << "输入错误！" << std::endl;
		return is;
	}
	return is;
}

std::ostream& operator<<(std::ostream& os, ListNode& node)
{
	os.setf(std::ios::left);
	os << std::setw(kBlankNum) << node._candidate_number
		<< std::setw(kBlankNum) << node._name
		<< std::setw(kBlankNum) << node._gender
		<< std::setw(kBlankNum) << node._age
		<< std::setw(kBlankNum) << node._category << std::endl;
	return os;
}

void ListNode::PrintNode()
{
	if (this == NULL)
	{
		std::cerr << "不存在输入的数据" << std::endl;
		return;
	}
	std::cout << *this;
	return;
}

class List {
public:
	List() = default;
	~List();
	void Creat();
	ListNode* SearchPosition(int pos);
	ListNode* SearchCandidateNumber(int num);
	void Insert();
	void Modify();
	void Remove();
	int Size();
	void Print();
private:
	ListNode* _first;
	ListNode* _last;
};

List::~List()
{
	ListNode* p = _first;
	while (p != NULL)
	{
		ListNode* q = p;
		p = p->_next;
		delete q;
	}
	return;
}

void List::Creat()
{
	int total;
	std::cout << "请输入考生人数：";
	std::cin >> total;
	ListNode* p = new ListNode;
	_first = p;
	std::cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << std::endl;
	for (int i = 0; i < total; i++)
	{
		ListNode* q = new ListNode;
		std::cin >> *q;
		p->_next = q;
		q->_prev = p;
		p = q;
	}
	p->_next = NULL;
	_last = p;
	std::cout << std::endl;
	return;
}

ListNode* List::SearchPosition(int pos)
{
	if (pos == 0)
	{
		return _first;
	}
	ListNode* p = _first;
	int count = 0;
	while (p != NULL)
	{
		p = p->_next;
		count++;
		if (count == pos) break;
	}
	return p;
}

ListNode* List::SearchCandidateNumber(int num)
{
	ListNode* p = _first->_next;
	while (p != NULL)
	{
		if (p->_candidate_number == num)
		{
			break;
		}
		p = p->_next;
	}
	return p;
}

void List::Insert()
{
	std::cout << "请输入你要插入的考生的位置：";
	int pos;
	std::cin >> pos;
	if (pos<1 || pos>this->Size() + 1)
	{
		std::cerr << "输入位置过大/过小，无法插入" << std::endl;
		return;
	}
	ListNode* p = this->SearchPosition(pos - 1);
	ListNode* new_node = new ListNode;
	std::cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！" << std::endl;
	std::cin >> *new_node;
	new_node->_next = p->_next;
	new_node->_prev = p;
	if (p->_next != NULL)
		p->_next->_prev = new_node;
	p->_next = new_node;
	if (new_node->_next == NULL)
	{
		_last = new_node;
	}
	return;
}

void List::Modify()
{
	std::cout << "请输入要修改的考生考号：";
	int num;
	std::cin >> num;
	ListNode* p = this->SearchCandidateNumber(num);
	if (p == NULL)
	{
		std::cerr << "不存在输入编号" << std::endl;
		return;
	}
	std::cout << "请输入要修改的内容（1为考号，2为姓名，3为性别，4为年龄，5为报考类别）：";
	int content;
	std::cin >> content;
	if (content == 1) {
		int num;
		std::cout << "请输入考号：";
		std::cin >> num;
		p->_candidate_number = num;
	}
	else if (content == 2) {
		std::string name;
		std::cout << "请输入姓名：";
		std::cin >> name;
		p->_name = name;
	}
	else if (content == 3) {
		std::string gender;
		std::cout << "请输入性别：";
		std::cin >> gender;
		p->_gender = gender;
	}
	else if (content == 4)
	{
		int age;
		std::cout << "请输入年龄：";
		std::cin >> age;
		p->_age = age;
	}
	else if (content == 5)
	{
		std::string category;
		std::cout << "请输入报考类别：";
		std::cin >> category;
		p->_category = category;
	}
	else {
		std::cerr << "错误输入！";
	}
	return;
}

void List::Remove()
{
	int num;
	std::cout << "请输入要删除的考生的考号：";
	std::cin >> num;
	ListNode* p = NULL;
	p = this->SearchCandidateNumber(num);
	if (p == NULL)
	{
		std::cerr << "不存在所输入考号" << std::endl;
		return;
	}
	ListNode* prev = p->_prev;
	prev->_next = p->_next;
	if (p->_next != NULL)
		p->_next->_prev = prev;
	std::cout << "你删除的考生信息是：" << *p << std::endl;
	if (prev->_next == NULL)
	{
		_last = prev;
	}
	delete p;
	return;
}

int List::Size()
{
	ListNode* p = _first->_next;
	int size = 0;
	while (p != NULL)
	{
		p = p->_next;
		size++;
	}
	return size;
}

void List::Print()
{
	ListNode* p = _first->_next;
	std::cout.setf(std::ios::left);
	std::cout << std::setw(kBlankNum) << "考号"
		<< std::setw(kBlankNum) << "姓名"
		<< std::setw(kBlankNum) << "性别"
		<< std::setw(kBlankNum) << "年龄"
		<< std::setw(kBlankNum) << "报考类别" << std::endl;

	while (p != NULL)
	{
		std::cout << *p;
		p = p->_next;
	}
	return;
}

int main(void)
{
	std::cout << "首先请建立考生信息系统！" << std::endl;
	List li;
	li.Creat();
	li.Print();
	std::cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << std::endl;
	while (true)
	{
		int num;
		std::cout << "请选择您要进行的操作：";
		std::cin >> num;
		if (num == 1)
		{
			li.Insert();
		}
		else if (num == 2)
		{
			li.Remove();
		}
		else if (num == 3)
		{
			std::cout << "请输入要查找考生的考号：";
			int i;
			std::cin >> i;
			ListNode* p = li.SearchCandidateNumber(i);
			p->PrintNode();
		}
		else if (num == 4)
		{
			li.Modify();
		}
		else if (num == 5)
		{
			li.Print();
		}
		else if (num == 0)
		{
			break;
		}
		li.Print();
	}

	return 0;
}