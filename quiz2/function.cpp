#include "function.h"
#include <iostream>
using namespace std;

void LinkedList::reverse(int left, int right){
    if (left > right) return; //if not valid then terminate
 
    Node* previous = nullptr; //declare previous pointer
    Node* current = head; //declare pointer we gonna use throughout
 
    for (int i = 1 ; current != NULL && i < left ; i++){ 
        previous = current;
        current = current->next;
    }
 
    Node* start = current;
    Node* end = nullptr;

    //previous is at left-1 node
    //current is in left node

    for (int i = 1; current != NULL && i <= right-left+1; i++){ //reverse 
        Node* next = current->next;
        current->next = end;
        end = current;
        current = next;
    }

    if (start){ //return head node
        start->next = current;
        if (previous != NULL) {
            previous->next = end;
        }
        else head = end;
    }
 
}