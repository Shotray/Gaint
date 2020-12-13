#include<iostream>
#include<string>
#include<vector>
#include<cmath>
using namespace std;

#define NULL 0
#include<stdexcept>
#include<string>


template<class type> class List;

template<class type>
class ListNode {
  friend List<type>;
  ListNode() : _prev(NULL), _next(NULL) {}
  ListNode(type data) :_data(data), _prev(NULL), _next(NULL) {}
private:
  type _data;
  ListNode* _prev;
  ListNode* _next;
};

template<class type>
class List {
public:
  List();
  ~List();
  void insert(int pos, type data);
  void push_back(type data);
  bool empty();
  int size() { return _size; }
  void remove(int pos);
  void pop();
  class Iter;
  Iter begin();
  Iter end();
  Iter find(type data);
private:
  ListNode<type>* _first;
  ListNode<type>* _last;
  int _size;
};

template <class type>
class List<type>::Iter {
  const ListNode <type>* ptr;
public:
  Iter() = default;
  Iter(const ListNode<type>* pointer) :ptr(pointer) {}
  Iter& operator++();
  Iter operator++(int);
  bool operator==(const Iter& other)const { return ptr == other.ptr; }
  bool operator!=(const Iter& other)const { return ptr != other.ptr; }
  const type& operator*() { return ptr->_data; }
  type get_data() { return ptr->_data; }
};

template<class type>
auto List<type>::Iter::operator++()->Iter& {
  if (ptr == nullptr)
    throw std::out_of_range("Out of range when iterating List");
  ptr = ptr->_next;
  return *this;
}

template<class type>
auto List<type>::Iter::operator++(int)->Iter {
  Iter copy = *this;
  ++* this;
  return copy;
}

template <class type>
auto List<type>::begin()->Iter {
  if (!empty()) return Iter(_first->_next);
  else throw std::out_of_range("The list is empty");
}

template <class type>
auto List<type>::end()->Iter {
  if (!empty())return Iter(_last);
  else throw std::out_of_range("The list is empty");
}

template <class type>
auto List<type>::find(type data)->Iter {
  List<type>::Iter itor;
  for (itor = begin();itor != end();itor++) {
    if (itor.get_data() == data) return itor;
  }
  if (itor.get_data() == _last->_data) return itor;
  return std::out_of_range("The data is not in the list");
}

template<class type>
List<type>::List() {
  ListNode<type>* p = new ListNode<type>;
  _first = p;
  _last = _first;
  _size = 0;
}

template<class type>
List<type>::~List() {
  ListNode<type>* p = _first;
  while (p != NULL) {
    ListNode<type>* q = p;
    p = p->_next;
    delete q;
  }
  return;
}

template<class type>
void List<type>::insert(int pos, type data) {
  if (pos > _size)
    throw std::out_of_range("The position is out of range");
  ListNode<type>* p = new ListNode<type>(data);
  if (pos == _size) {
    p->_prev = _last;
    _last->_next = p;
    _last = p;
    _size++;
    return;
  }
  if (empty()) {
    _first->_next = p;
    p->_prev = _first;
    _size++;
    return;
  }
  int position = 0;
  ListNode<type>* temp = _first;
  while (temp != NULL) {
    if (position == pos) break;
    temp = temp->_next;
    position++;
  }
  p->_next = temp->_next;
  temp->_next->_prev = p;
  p->_prev = temp;
  temp->_next = p;
  _size++;
  return;
}

template<class type>
void List<type>::push_back(type data) {
  ListNode<type>* p = new ListNode<type>;
  p->_data = data;
  _last->_next = p;
  p->_prev = _last;
  _last = p;
  _size++;
}

template<class type>
bool List<type>::empty() {
  if (_first->_next == NULL)
    return true;
  return false;
}

template<class type>
void List<type>::remove(int data) {
  if (empty())
    throw std::out_of_range("The list is empty");
  ListNode<type>* node = _first->_next;
  while (node->_data != data && node->_next != NULL)
  {
    node = node->_next;
  }
  if (node == NULL)return;
  if (node == _last) {
    _last = node->_prev;
    _last->_next = NULL;
    delete node;
  }
  else {
    node->_prev->_next = node->_next;
    node->_next->_prev = node->_prev;
    delete node;
  }
  _size--;
  return;
}

template<class type>
void List<type>::pop()
{
  if (empty())
    throw std::out_of_range("The list is empty");
  ListNode<type>* node = _last;
  _last = _last->_prev;
  _last->_next = NULL;
  delete node;
  _size--;
  return;
}

template <class type>
class Stack {
  List<type> stack;

public:
  Stack() = default;
  bool empty();
  void pop();
  void push(type data);
  int size();
  type top();
};

template<class type>
bool Stack<type>::empty()
{
  if (stack.empty()) return true;
  return false;
}

template<class type>
void Stack<type>::pop()
{
  stack.pop();
  return;
}

template<class type>
void Stack<type>::push(type data) {
  stack.push_back(data);
  return;
}

template<class type>
int Stack<type>::size() {
  return stack.size();
}

template<class type>
type Stack<type>::top() {
  typename List<type>::Iter itor;
  itor = stack.end();
  return itor.get_data();
}

int priority(char symbol) {
  switch (symbol) {
  case '=':
    return 0;
  case '(':
  case ')':
    return 1;
  case '+':
  case '-':
    return 2;
  case '*':
  case '/':
    return 3;
  case '%':
    return 4;
  case '^':
    return 5;
  }
  return -1;
}

bool isOperationalSymbol(char symbol) { 
  if(priority(symbol)!=-1)
    return true;
  return false;
}

bool isNumber(char num) {
  if (num >= '0' && num <= '9')
    return true;
  return false;
}

bool isParenthesisMatching(string s) {
  int parenthesis = 0;
  for (int i = 0;i < s.size();i++) {
    if (s[i] == '(')
      parenthesis++;
    if (s[i] == ')')
      parenthesis--;
  }
  return parenthesis == 0;
}

struct element {
  bool is_num=false;
  double _num = 0.0;
  char operation = ',';
};

vector<element> suffix(string s) {
  vector<element> suf;
  Stack<element> op;
  for (int i = 0;i < s.size();i++) {
    double num;
    if (isNumber(s[i])) {
      int j = i + 1;
      while (isNumber(s[j]) || s[j] == '.') {
        j++;
      }
      string snum = s.substr(i, j);
      num = stod(snum);
      if (s[0] == '-' && i == 1) {
        num = -num;
        op.pop();
      }
      if (s[0] == '+' && i == 1){
        op.pop();
      }
      i = j-1;
      element temp;
      temp.is_num = true;
      temp._num = num;
      suf.push_back(temp);
    }
    else if (isOperationalSymbol(s[i])) {
      if (op.empty()) {
        element temp;
        temp.is_num = false;
        temp.operation = s[i];
        op.push(temp);
      }
      else if (s[i] == ')') {
        while (op.top().operation != '(') {
          suf.push_back(op.top());
          op.pop();
        }
        op.pop();
      }
      else if (s[i] == '(') {
        element temp;
        temp.is_num = false;
        temp.operation = '(';
        op.push(temp);
        if (s[i + 1] == '-'||s[i+1]=='+') {
          temp.is_num = true;
          temp._num = 0;
          suf.push_back(temp);
        }
      }
      else {
        while (!op.empty()&&priority(op.top().operation) >= priority(s[i])) {
          suf.push_back(op.top());
          op.pop();
        }
        element temp;
        temp.is_num = false;
        temp.operation = s[i];
        op.push(temp);
      }
    }
    else {
      throw invalid_argument("Invalid input.");
    }
  }
  while (!op.empty()) {
    suf.push_back(op.top());
    op.pop();
  }
  return suf;
}

void print(vector<element> test) {
  for (int i = 0;i < test.size();i++) {
    if (test[i].is_num) cout << test[i]._num << ' ';
    else cout << test[i].operation << ' ';
  }
  return;
}

int pow(int left, int right) {
  int ans = 1;
  while (right) {
    if (right & 1)
      ans *= left;
    left *= left;
    right >>= 1;
  }
  return ans;
}

double run(double left, double right, char op) {
  if (op == '-') return left - right;
  if (op == '+') return left + right;
  if (op == '*')return left * right;
  if (op == '/') {
    if (fabs(right - 0.0) < 1e-8) {
      throw invalid_argument("Divided by 0.");
      return 0;
    }
    else return left / right; 
  }
  if (op == '%')return (int)left % (int)right;
  if (op == '^')return pow((int)left, (int)right);
}

double calculate(string s) {
  if (!isParenthesisMatching(s))
    throw invalid_argument("Bracket mismatch.");

  if (s[s.size() - 1] == '=') s.pop_back();
  else
    throw invalid_argument("There is no '=' in the end of expression.");

  vector<element> suf = suffix(s);
  Stack<double> result;
  for (int i = 0;i < suf.size();i++) {
    if (suf[i].is_num)
      result.push(suf[i]._num);
    else {
      double left, right;
      right = result.top();
      result.pop();
      left = result.top();
      result.pop();
      double res=run(left, right, suf[i].operation);
      result.push(res);
    }
  }

  return result.top();
}

bool check(string s){
  for(int i=0;i<s.size();i++){
    if(s[i]>='0'&&s[i]<='9')
      continue;
    switch(s[i]){
      case '%':
      case '^':
      case '+':
      case '-':
      case '*':
      case '/':
      case '(':
      case ')':
      case '=':
      case '.':
        continue;
      default:return false;
    }
  }
  return true;
}

void solve() {
  string s;
  while(true){
    cout << "Please input the arithemetic expression."<<endl;
    cin >> s;
    if(!check(s)) 
      throw invalid_argument("Wrong input!");
    cout << "The answer is:";
    cout << calculate(s) << endl;
    cout<<"continue?(y,n):";
    char judge;
    cin>> judge;
    if(judge=='n') return;
  }
  return;
}

int main(void) {
  solve();
  system("pause");
  return 0;
}