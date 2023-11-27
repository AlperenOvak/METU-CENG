#ifndef STACK_LINKEDLIST_H
#define STACK_LINKEDLIST_H

#include <iostream>
using namespace std;

template <class T>
class StackNode{
    public:
        StackNode(const T& e = T(),StackNode* n = NULL){
            item = e;
            next = n;
        }
        T item;
        StackNode* next;
}

template <class T>
class Stack{
    public:
        Stack();
        Stack(const Stack& rhs);
        ~Stack();
        Stack& operator=(const Stack& rhs);
        bool isEmpty();
        void
}




#endif