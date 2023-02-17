#include "function.h"
#include <iostream>
using namespace std;

//node
template <class T>
Node<T>::Node(T x,T y,T fence){
    this->x = x;
    this->y = y;
    this->fence = fence;
    this->next = NULL;
}

template <class T>
T Node<T>::compare(T x,T y){
    if(y > this->y) return true; //IF BOTTOM TO TOP LIKE THIS
    if(this->y > y) return false; //IF TOP TO BOTTOM FLIP THE DAMN THING
    return this->x < x;
}

//linked list
template <class T>
LinkedList<T>::LinkedList(){
    first = NULL;
    length = 0;
}

template <class T>
void LinkedList<T>::insert(T x, T y,T fence){
    Node<T>* new_node = new Node<T>(x, y, fence);
    if (first == NULL){ //WHEN INITIALING NODE
        first = new_node;
        return;
    }
    if( first->x == x && first->y == y ){ //INSERT BACK
        if( fence == 1 ) first->fence = 1;
        delete new_node;
        return;
    }
    Node<T>* temp = first;
    if(new_node->compare(first->x, first->y)){  //INSERT MIDDLE OR FRONT
        new_node->next = first;
        first = new_node;
        return;
    }
    if( temp != NULL && temp->x == x && temp->y == y ){ //OVERWRITE PART
        if( fence == 1 ) temp->fence = 1;
        delete new_node;
        return;
    }

    while(temp->next != NULL && new_node->compare(temp->next->x, temp->next->y) == false){ //MOVING FORWARD
        temp = temp->next;
    }
    new_node->next = temp->next;
    temp->next = new_node;
}

template <class T>
void LinkedList<T>::deletion(T x, T y){
    if (first == NULL) return; //NO PLANT
    Node<T> *temp = first;
    Node<T> *prev, *now;

    if(first->x == x && first->y == y){ //NORMAL DELETE
        if(first->fence == 1) return;
        else if(first->fence == 0){
            temp = first;
            first = first->next;   
            delete temp;
            return;
        }
    }
    // FINDING THE RIGHT NODE
    prev = first;
    now = first->next;
    if(now == NULL) return;

    while( now->x != x || now->y != y){ //STOP WHEN AT THE EXACT SPOT
        prev = now;
        now = now->next;
        if(now == NULL) return; // END OF LIST BUT NOT EXACT LOCATION
    }
    // FINDING EXACT LOCATION
    if( now -> fence == 1) return; //FOUND BUT CANT STEAL
    prev->next = now->next; //FOUND AND CAN STEAL
    delete now;
}

template <class T>
void LinkedList<T>::show(){
    Node<T>* temp = first;
    while (temp != NULL){
        cout << '(' << temp->x << ',' << temp->y <<')' << endl;
        temp = temp->next;
    }
}

LinkedList<int> list;

void plant(long long x,long long y,int withFence){
    list.insert(x, y, withFence);
}

void thief(long long x,long long y){
    list.deletion(x,y);
    list.deletion(x+1,y);
    list.deletion(x-1,y);
    list.deletion(x,y+1);
    list.deletion(x,y-1);
}

void superThief(long long x,long long y){
    list.deletion(x,y);
    list.deletion(x+1,y);
    list.deletion(x-1,y);
    list.deletion(x,y+1);
    list.deletion(x,y-1);
    list.deletion(x+1,y+1);
    list.deletion(x+1,y-1);
    list.deletion(x-1,y+1);
    list.deletion(x-1,y-1);
}

void display(){
    cout << "Display"<< endl;
    list.show();
}