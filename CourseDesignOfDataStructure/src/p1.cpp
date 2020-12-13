#include<iostream>
#include<string>
#include<iomanip>
#include<stdexcept>

const int kBlankNum = 10;


class List;

class ListNode {
	friend List;
 public:
	friend std::istream& operator>>(std::istream& is, ListNode& node);//重载输入运算符
	friend std::ostream& operator<<(std::ostream& os, ListNode& node);//重载输出运算符
	ListNode() :_candidate_number(0), _name("\0"), _gender("\0"), _age(0), _category("\0"), _prev(NULL), _next(NULL) {}//默认值为0的构造函数
	void PrintNode();//输出该结点
private:
	int _candidate_number;//学生考号
	std::string _name;//学生姓名
	std::string _gender;//学生性别
	int _age;//学生年龄
	std::string _category;//学生报考类别
	ListNode* _prev;//前一个结点
	ListNode* _next;//后一个结点
};

std::istream& operator>>(std::istream& is, ListNode& node)
{
	is >> node._candidate_number >> node._name >> node._gender >> node._age >> node._category;
	if (std::cin.eof())	return is;
	if (std::cin.fail()) {
		std::cerr << "Wrong Input!" << std::endl;
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
		std::cerr << "The data entered doesn't exist." << std::endl;
		return;
	}
	std::cout << *this;
	return;
}

class List {
public:
	List() = default;//默认构造函数
	~List();//删除所有新开辟空间的析构函数
	void Creat();//构造系统
	ListNode* SearchPosition(int pos);//根据输入位置寻找考生
	ListNode* SearchCandidateNumber(int num);//根据输入考号寻找考生
	void Insert();//插入考生信息
	void Modify();//修改考生信息
	void Remove();//删除考生信息
	int Size();//系统内考生信息数量
	void Print();//输出所有考生信息
private:
	ListNode* _first;//标记整个链表头节点
	ListNode* _last;//标记整个链表尾节点
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
	std::cout << "Please input the number of students:";
	std::cin >> total;
	if(std::cin.fail())
		throw std::invalid_argument("Invalid input!");
	ListNode* p = new ListNode;
	_first = p;
	std::cout << "Please input the examinee's number, name, gender, age and registration category in turn!" << std::endl;
	for (int i = 0; i < total; i++)
	{
		ListNode* q = new ListNode;
		std::cin >> *q;
		if(std::cin.fail())
			throw std::invalid_argument("Invalid input!");
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
	std::cout << "Please enter the location of the candidate you want to insert:";
	int pos;
	std::cin >> pos;
	if (pos<1 || pos>this->Size() + 1)
	{
		std::cerr << "The input position is too large / too small to insert." << std::endl;
		return;
	}
	ListNode* p = this->SearchPosition(pos - 1);
	ListNode* new_node = new ListNode;
	std::cout << "Please enter the data of the candidate you want to insert:" << std::endl;
	std::cin >> *new_node;
	if(std::cin.fail())
		throw std::invalid_argument("Invalid input!");
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
	std::cout << "Please input the examinee's number to be modified:";
	int num;
	std::cin >> num;
	ListNode* p = this->SearchCandidateNumber(num);
	if (p == NULL)
	{
		std::cerr << "The examinee's number entered doesn't exist." << std::endl;
		return;
	}
	std::cout << "Please enter the content to be modified (1 is the examinee's number, 2 is the name, 3 is the gender, 4 is the age, and 5 is the registration category):";
	int content;
	std::cin >> content;
	if (content == 1) {
		int num;
		std::cout << "Please input the examinee's number：";
		std::cin >> num;
		p->_candidate_number = num;
	}
	else if (content == 2) {
		std::string name;
		std::cout << "Please input name:";
		std::cin >> name;
		p->_name = name;
	}
	else if (content == 3) {
		std::string gender;
		std::cout << "Please input gender:";
		std::cin >> gender;
		p->_gender = gender;
	}
	else if (content == 4)
	{
		int age;
		std::cout << "Please input age:";
		std::cin >> age;
		p->_age = age;
	}
	else if (content == 5)
	{
		std::string category;
		std::cout << "Please input registration category:";
		std::cin >> category;
		p->_category = category;
	}
	else {
		std::cerr << "Wrong Input"<<std::endl;
	}
	return;
}

void List::Remove()
{
	int num;
	std::cout << "Please enter the examinee's number of the candidate to be deleted:";
	std::cin >> num;
	ListNode* p = NULL;
	p = this->SearchCandidateNumber(num);
	if (p == NULL)
	{
		std::cerr << "The examinee's number entered does not exist" << std::endl;
		return;
	}
	ListNode* prev = p->_prev;
	prev->_next = p->_next;
	if (p->_next != NULL)
		p->_next->_prev = prev;
	std::cout << "The information of the examinee you delete is:" << *p << std::endl;
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
	std::cout << std::setw(kBlankNum) << "examinee's number"
		<< std::setw(kBlankNum) << "name"
		<< std::setw(kBlankNum) << "gender"
		<< std::setw(kBlankNum) << "age"
		<< std::setw(kBlankNum) << "registration category" << std::endl;

	while (p != NULL)
	{
		std::cout << *p;
		p = p->_next;
	}
	return;
}



int main(void)
{
	std::cout << "First of all, please establish the examinee information system!" << std::endl;
	List li;
	li.Creat();
	li.Print();
	std::cout << "Please select the operation you want to perform (1 is insert, 2 is delete, 3 is search, 4 is modify, 5 is statistics, 0 is cancel operation)" << std::endl;
	while (true)
	{
		int num;
		std::cout << "Please choose the action:";
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
			std::cout << "Please input the examinee's number you want to search:";
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
		}
		else if (num == 0)
		{
			break;
		}
		li.Print();
	}
	system("pause");
	return 0;
}