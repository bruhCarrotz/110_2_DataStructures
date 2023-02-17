#include <iostream>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <bits/stdc++.h>
#include "function.h"
using namespace std;

//ALL NODE FUNCTIONS
Node::Node(std::string id, u32 time){
    this->id = id;
    this->time = time;
};

u32 Node::get_time(){
    return time;
};

std::string Node::get_id(){
    return id;
};

void Node::set_time(u32 time){
    this->time = time;
};

ostream& operator<<(ostream& os, Node& n) {
    os << n.id << " AT " << n.time;
    return os;
};

// NODES OPERATOR OVERLOADING
bool operator== (Node& node1, Node& node2){
    return node1.get_time() == node2.get_time();
};

bool operator!= (Node& node1, Node& node2){
    return node1.get_time() != node2.get_time();
};

bool operator< (Node& node1, Node& node2){
    if(node1.get_time() == node2.get_time()){
        return node1.get_id() < node2.get_id();
    }
    return node1.get_time() < node2.get_time();
};

bool operator> (Node& node1, Node& node2){
    if(node1.get_time() == node2.get_time()){
        return node1.get_id() > node2.get_id();
    }
    return node1.get_time() > node2.get_time();
};

bool operator<= (Node& node1, Node& node2){
    return node1.get_time() <= node2.get_time();
};

bool operator>= (Node& node1, Node& node2){
    return node1.get_time() >= node2.get_time();
};

//TIME OF NODES OPERATOR OVERLOADING
bool operator== (Node& node1, u32 time){
    return node1.get_time() == time;
};

bool operator!= (Node& node1, u32 time){
    return node1.get_time() != time;
};

bool operator< (Node& node1, u32 time){
    return node1.get_time() < time;
};

bool operator> (Node& node1, u32 time){
    return node1.get_time() > time;
};

bool operator<= (Node& node1, u32 time){
    return node1.get_time() <= time;
};

bool operator>= (Node& node1, u32 time){
    return node1.get_time() >= time;
};

void operator+= (Node& node1,u32 time){
    node1.set_time(node1.get_time() + time);
};

//HEAP FUNCTIONS
template <class T>
u32 BinaryHeap<T>::parent_idx(u32 idx){
    return (idx-1)/2;
};

template <class T>
u32 BinaryHeap<T>::left_idx(u32 idx){
    return (2*idx) + 1;
};

template <class T>
u32 BinaryHeap<T>::right_idx(u32 idx){
    return (2*idx) + 2;
};

template <class T>
void BinaryHeap<T>::heapify_up(int idx){
    if(idx == 0) return;
    u32 index = idx;

    if(heap[parent_idx(index)] > heap[index]){
        T temp = heap[parent_idx(index)];
        heap[parent_idx(index)] = heap[index];
        heap[index] = temp;

        int min = parent_idx(index);
        heapify_up(min);
    }
};

template <class T>
void BinaryHeap<T>::heapify_down(int idx){
    u32 left_child = 2*idx + 1;
    u32 right_child = 2*idx + 2;

    if(left_child >= heap.size()) return;

    u32 minIndex = idx;

    if(heap[idx] > heap[left_child]){
        minIndex = left_child;
    }
    
    if((right_child < heap.size()) && (heap[minIndex] > heap[right_child])){
        minIndex = right_child;
    }

    if(minIndex != idx){
        T temp = heap[idx];
        heap[idx] = heap[minIndex];
        heap[minIndex] = temp;
        heapify_down(minIndex);
    }
};

template <class T>
u32 BinaryHeap<T>::size(){
    return heap.size();
};

template <class T>
void BinaryHeap<T>::insert(T element){
    heap.push_back(element);
    heapify_up(heap.size()-1);
};

template <class T>
T BinaryHeap<T>::get_min(){
    return heap.front();
};

template <class T>
void BinaryHeap<T>::del_min(){
   if (heap.size() == 0) return;
   heap[0] = heap.at(heap.size()-1);
   heap.pop_back();
   heapify_down(0);
};
/*
template <class T>
void BinaryHeap<T>::print(){
    for(int i=0 ; i<heap.size() ; i++){
        cout << heap[i] << endl;
    }
};
*/

u32 max_ele = 0;

//MANAGER FUNCTIONS
template <class T>
Manager<T>::Manager(){
    taQue = BinaryHeap<T>();
    endTime = 0xFFFFFFFF; //infinite time: FFFFFFFF in 32 bits 
}

template <class T>
int Manager<T>::finish_in_time(u32 costTime,u32 deadLine){
    Node node3 = taQue.get_min();
    u32 testtime = node3.get_time();

    u32 sum = testtime + costTime;
    if(sum > deadLine || sum > endTime){
        return 0; //overtime
    }
    else{
        return 1; //success
    }
}

template <class T>
u32 find_max(BinaryHeap<T> example , u32 size){
    for(int i=0 ; i<size ; i++){
        Node node3 = example.get_min();
        max_ele = node3.get_time();
        example.del_min();
    }
    return max_ele;
}

template <class T>
void Manager<T>::cmd_set_endTime(u32 endTime){
    //u32 longest = find_max(taQue, taQue.size());
    if(endTime < max_ele){
        cout << "SET_ENDTIME FAIL" << endl; 
        return;
    }
    this->endTime = 0;
    this->endTime = endTime;
    cout << "SET_ENDTIME SUCCESS" << endl;
}

template <class T>
void Manager<T>::cmd_add_task(string taskName,u32 costTime){ 
    if(taQue.size() == 0){
        cout << "ADD_TASK " << taskName << ": FAIL" << endl;
        return;
    }

    Node minimum = taQue.get_min();
    taQue.del_min();
    u32 task_time = minimum.get_time() + costTime;

    if(task_time > this->endTime){
        taQue.insert(minimum);
        cout << "ADD_TASK " << taskName << ": FAIL" << endl;
        //taQue.print();
    }
    else{
        minimum.set_time(task_time);
        taQue.insert(minimum);
        //taQue.print();
        cout << "ADD_TASK " << taskName << ": ";
        cout << minimum.get_id() << " AT " << minimum.get_time() << endl;
        if (minimum.get_time() > max_ele){
            max_ele = minimum.get_time();
        }
    }

}

template <class T>
void Manager<T>::cmd_add_ta(std::string id, u32 begin){
    if(begin < this->endTime){
        cout << "ADD_TA SUCCESS" << endl;
        taQue.insert(T(id,begin));
        if (begin > max_ele){
            max_ele = begin;
        }
    }
    else{
        cout << "ADD_TA FAIL" << endl;
    }
    //taQue.print();
}

template <class T>
void Manager<T>::cmd_check_schedule(u32 costTime,u32 deadLine){
    if(taQue.size() == 0){
        cout << "CHECK_SCHEDULE: NO TA WARNING!" << endl;
        return;
    }
    if(finish_in_time(costTime,deadLine) == 0){
        cout << "CHECK_SCHEDULE: OVERTIME WARNING!" << endl;
        return;
    }
    else{    
        cout << "CHECK_SCHEDULE: CAN FINISH!" << endl;
        return;
    }
}

template <class T>
void Manager<T>::result(){
    if(taQue.size()==0){
        cout << "NUMBER_TA: " << taQue.size() << endl;
        return;
    }
    Node node1 = taQue.get_min();
    cout << "NUMBER_TA: " << taQue.size() << endl;
    cout << "EARLIEST FINISH TA: " ;
    cout << node1.get_id() << " AT " << node1.get_time() << endl;
}

template Manager<Node>::Manager();
template void Manager<Node>::cmd_set_endTime(u32 endTime);
template void Manager<Node>::cmd_check_schedule(u32 costTime,u32 deadLine);
template void Manager<Node>::cmd_add_task(string taskName,u32 costTime);
template void Manager<Node>::cmd_add_ta(std::string id, u32 begin);
template void Manager<Node>::result();
