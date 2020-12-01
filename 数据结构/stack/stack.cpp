#include "list.hpp"
#include<iostream>

template <class type>
class Stack{
    List<type> stack;
    
public:
    Stack()=default;
    bool empty();
    void pop();
    void push(type data);
    int size();
    type top();
};

template<class type>
bool Stack<type>::empty()
{
    if(stack.empty()) return true;
    return false;
}

template<class type>
void Stack<type>::pop()
{
    stack.pop();
    return;
}

template<class type>
void Stack<type>::push(type data){
    stack.push_back(data);
    return;
}

template<class type>
int Stack<type>::size(){
    return stack.size();
}

template<class type>
type Stack<type>::top(){
    typename List<type>::Iter itor;
    itor=stack.end();
    return itor.get_data();
}

int main(void){
    Stack<int> s;
    s.top();
    return 0;
}