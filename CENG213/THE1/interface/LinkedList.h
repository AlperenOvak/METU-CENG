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
    head = new Node<T>;
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &rhs)
{   
    /* TODO */
}

template<class T>
LinkedList<T>::~LinkedList()
{   
    for(int i=0;i<size;i++){
        /*start from the tail*/
    }
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    /* TODO */
}

template<class T>
int LinkedList<T>::getSize() const
{
    return size-1;
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
    if(size==1){
        return 1;
    }
    return 0;
}

template<class T>
bool LinkedList<T>::containsNode(Node<T> *node) const
{
    /* TODO */
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    /* TODO */
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    /* TODO */
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    /* TODO */
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    /* TODO */
}

template<class T>
void LinkedList<T>::append(const T &data)
{   
    /* TODO */
}

template<class T>
void LinkedList<T>::prepend(const T &data)
{
    /* TODO */
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    /* TODO */
}

template<class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)
{
    /* TODO */
}

template<class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{
    /* TODO */
}

template<class T>
void LinkedList<T>::swapWithLeft(Node<T> *node)
{
    /* TODO */
}

template<class T>
void LinkedList<T>::swapWithRight(Node<T> *node)
{
    /* TODO */
}

template<class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)
{
    /* TODO */
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