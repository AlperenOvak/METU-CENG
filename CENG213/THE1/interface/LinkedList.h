#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template <class T>
class LinkedList
{
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &rhs);
    ~LinkedList();

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

    int getSize() const;
    bool isEmpty() const;
    bool containsNode(Node<T> *node) const;
    int getIndex(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void append(const T &data);
    void prepend(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAtIndex(const T &data, int index);
    void moveToIndex(int currentIndex, int newIndex);
    void mergeNodes(int sourceIndex, int destIndex);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeNodeAtIndex(int index);
    void removeAllNodes();

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    int size;
};

template<class T>
LinkedList<T>::LinkedList()
{
    /* TODO */
    T a;
    head=new Node<T>(a);
    size=0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &rhs)
{   
    /* TODO */
    T a;
    head=new Node<T>(a);
    size=0;
    
    Node<T>* current = rhs.head->next; 
    Node<T>* lastNode = head->next;
    while(current != NULL){
        Node<T>* newNode = new Node<T>(current->data);

        if(lastNode==NULL){
            head->next=newNode;
            newNode->prev = head;
        }
        lastNode->next=newNode;
        newNode->prev=lastNode;
        lastNode=newNode;
    }
}

template<class T>
LinkedList<T>::~LinkedList()
{   
    /* TODO */
    /*removeAllNodes();*/
    delete head;
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    /* TODO */
    /*removeAllNodes();
    if(rhs.head->next == NULL){
        return *this;
    }
    Node<T>* current = rhs.head->next;
    while(current->next != NULL){
        append(current->data);
        current = current -> next;
    }*/
    return *this;
}

template<class T>
int LinkedList<T>::getSize() const
{
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
    return (size == 0);
}

template<class T>
bool LinkedList<T>::containsNode(Node<T> *node) const
{
    /* TODO */
    return 0;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    /* TODO */
    if (isEmpty()) {
        return NULL;
    }
    return head->next;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    /* TODO */
    if (isEmpty()) {
        return NULL;
    }
    Node<T>* current = head->next;
    while(current->next != NULL){
        current=current->next;
    }
    return current;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    /* TODO */
    Node<T>* current = head->next;
    while(current != NULL){
        if(data==current->data){
            return current;
        }
        current=current->next;
    }
    return NULL;
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    /* TODO */
    if(index >= 0 && index<size){
        Node<T>* current = head->next;
        int i=0;
        while(i!=index){
            current=current->next;
            i++;
        }
        return current;
    }
    return NULL;
}

template<class T>
void LinkedList<T>::append(const T &data)
{   
    /* TODO */
    Node<T>* newNode = new Node<T>(data);
    Node<T>* lastNode = getLastNode();
    if(lastNode==NULL){
        head->next=newNode;
    }else{
        newNode->prev = head;
        lastNode->next=newNode;
        newNode->prev=lastNode;
    }
    size++;
}

template<class T>
void LinkedList<T>::prepend(const T &data)
{
    /* TODO */
    Node<T>* newNode = new Node<T>(data);
    Node<T>* nextNode = head->next;
    head->next=newNode;
    newNode->next=nextNode;
    if (nextNode != NULL) {
        nextNode->prev = newNode;
    }
    size++;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    /* TODO */
    Node<T>* newNode = new Node<T>(data);
    if(node->next != NULL){
        node->next->prev=newNode;
    }
    newNode->prev=node;
    newNode->next=node->next;
    node->next=newNode;
    size++;
}

template<class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)
{
    /* TODO */
    /*if(index >= 0 && index<size){
        Node<T>* newNode = new Node<T>(data);
    }*/
}

template<class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{
    /* TODO */
    Node<T>* current = head->next;
    int i=0;
    while(current->next != NULL){
        current=current->next;
        i++;
        if(current==node){
            return i;
        }
    }
    
    return -1;
}

template<class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)
{
    /* TODO */
    /*if(currentIndex >= 0 && currentIndex<size){
        if(newIndex<size){
            
        }
    }*/
}

template<class T>
void LinkedList<T>::mergeNodes(int sourceIndex, int destIndex)
{
    /* TODO */
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{   
    /* TODO */
}

template<class T>
void LinkedList<T>::removeNode(const T &data)
{   
    /* TODO */
}

template<class T>
void LinkedList<T>::removeNodeAtIndex(int index)
{
    /* TODO */
}

template<class T>
void LinkedList<T>::removeAllNodes()
{   
    /* TODO */
    Node<T>* current = head->next;
    Node<T>* nextNode;
    while (current != NULL) {
        if(current->next != NULL){
            nextNode = current->next;
        }
        delete current;
        current = nextNode;
    }
    head->next = NULL;
    size = 0;
    
}

template<class T>
void LinkedList<T>::print() const
{
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T> *node = this->getFirstNode();

    while(node)
    {
        std::cout << *node << std::endl;
        node = node->next;
    }

}

#endif //LINKEDLIST_H