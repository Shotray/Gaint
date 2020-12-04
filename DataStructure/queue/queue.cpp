#include"list.hpp"

template <class type>
class Queue{
    List<type> queue;
    public:
    Queue()=default;
    void pop_front(){queue.pop_front();}
    void push(type data){queue.push_back(data);};
    bool empty(){return queue.empty();};
    int size(){return queue.size();};
    type front(){return queue.begin().get_data();};
};
