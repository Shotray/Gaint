#define NULL 0
#include<stdexcept>

template<class type> class List;

template<class type>
class ListNode {
  friend List<type>;
  ListNode() :_data(0), _prev(NULL), _next(NULL) {}
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
  //下标从1开始（indexes start from 1）
  //you can insert to the beginning by typing 0
  void insert(int pos, type data);
  void push_back(type data);
  bool empty();
  int size() { return _size; }
  void remove(int pos);
  void pop();
  void pop_front();
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
  if(ptr==nullptr)
    throw std::out_of_range("Out of range when iterating List");
  ptr = ptr->_next;
  return *this;
}

//List<type>::Iter List<type>::Iter::operator++(int)

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
  if(itor.get_data()==_last->_data) return itor;
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
  if(empty())
    throw std::out_of_range("The list is empty");
  ListNode<type>* node=_last;
  _last=_last->_prev;
  _last->_next=NULL;
  delete node;
}

template<class type>
void List<type>::pop_front(){
  if(empty())
    throw std::out_of_range("The list is empty");
  ListNode<type>* node=_first->_next;
  _first->_next=node->_next;
  node->_next->_prev=_first;
  delete node;
  _size--;
}

int main(void) {
  List<int>li;
  li.push_back(3);
  li.push_back(4);
  li.pop_front();
  return 0;
}