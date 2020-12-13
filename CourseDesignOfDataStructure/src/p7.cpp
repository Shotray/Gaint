#include<iostream>
#include<vector>
#include<stdexcept>
using namespace std;

template<class type>
struct node {
  type _data;
  node* _prev = NULL;
  node* _next = NULL;
};

template <class type>
class SortedList {
public:
  SortedList();
  ~SortedList();
  void push(type data);
  bool empty();
  void pop_front();
  type front();
  int size() { return _size; }
private:
  node<type>* _first;
  node<type>* _last;
  int _size;
};

template<class type>
SortedList<type>::SortedList() {
  node<type>* p = new node<type>;
  p->_data = INT_MIN;
  _first = p;
  _last = _first;
  _size = 0;
}

template<class type>
SortedList<type>::~SortedList() {
  while (_first->_next != NULL) {
    node<type>* temp = _first;
    _first = _first->_next;
    delete temp;
  }
  delete _first;
}

template<class type>
void SortedList<type>::push(type data) {
  node<type>* n = _first;
  bool is_inserted = false;
  while (n->_next != NULL) {
    if (n->_data <= data && n->_next->_data > data) {
      node<type>* temp = new node<type>;
      temp->_data = data;
      temp->_prev = n;
      temp->_next = n->_next;
      n->_next->_prev = temp;
      n->_next = temp;
      is_inserted = true;
      break;
    }
    n = n->_next;
  }
  if (n->_next == NULL && !is_inserted) {
    node<type>* temp = new node<type>;
    temp->_data = data;
    temp->_prev = n;
    n->_next = temp;
    _last = temp;
  }
  _size++;
  return;
}

template<class type>
bool SortedList<type>::empty() {
  if (_first->_next == NULL)
    return true;
  return false;
}

template<class type>
type SortedList<type>::front() {
  if (empty())
    throw std::out_of_range("The list is empty.");
  return _first->_next->_data;
}

template<class type>
void SortedList<type>::pop_front() {
  if (empty())
    throw std::out_of_range("The list is empty.");
  node<type>* p = _first->_next;
  _first->_next = p->_next;
  delete p;
  _size--;
}

int calculateMinCost(SortedList<int>& pieces) {
  int ans = 0;
  while (pieces.size() > 1) {
    int temp = 0;
    temp += pieces.front();
    pieces.pop_front();
    temp += pieces.front();
    pieces.pop_front();
    pieces.push(temp);
    ans += temp;
  }
  return ans;
}

void solve() {
  cout << "Please input n which means how many pieces do we need:";
  int n;
  cin >> n;
  if(cin.fail()) 
    throw invalid_argument("Wrong Input");
  cout << "Please input the lengths of pieces:";
  SortedList<int> pieces;
  for (int i = 0;i < n;i++) {
    int temp;
    cin >> temp;
    if(cin.fail()) 
      throw invalid_argument("Wrong input!");
    pieces.push(temp);
  }
  cout <<"The total cost is:"<< calculateMinCost(pieces);
}

int main(void) {
  solve();
  system("pause");
  return 0;
}
