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
LinkedList<T>::LinkedList()                                               //DONE
{
    /* TODO */
    //T a;
    head=new Node<T>(T());
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
LinkedList<T>::~LinkedList() //DONE
{   
    /* TODO */
    removeAllNodes();
    delete head;
    size = 0;
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
    }
    return *this;*/
    if(this != &rhs){
        while(head->next){
            removeNodeAtIndex(0);
        }
        Node<T>* current = rhs.head->next;
        while(current){
            append(current->data);
            current=current->next;
        }
    }
    return *this;
}

template<class T>
int LinkedList<T>::getSize() const                                        //DONE
{
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const                                       //DONE
{
    return (size == 0);
}

template<class T>
bool LinkedList<T>::containsNode(Node<T> *node) const                     //DONE
{
    /* TODO */
    Node<T>* current = head->next;
    while(current != NULL){
        if(node==current){
            return 1;
        }
        current=current->next;
    }
    return 0;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const                              //DONE
{
    /* TODO */
    if (isEmpty()) {
        return NULL;
    }
    return head->next;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const                               //DONE
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
Node<T> *LinkedList<T>::getNode(const T &data) const                      //DONE
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
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const                   //DONE
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
void LinkedList<T>::append(const T &data)                                 //DONE
{   
    /* TODO */
    if(head->next == NULL){
        head->next = new Node<T>(data,head,NULL);
    }else{
        Node<T>* current = head->next;
        while(current->next != NULL){
            current=current->next;
        }
        current->next=new Node<T>(data,current,NULL);
    }
    size++;
    //std::cout<<"app"<<data<<std::endl;
    
}

template<class T>
void LinkedList<T>::prepend(const T &data)                                //DONE
{
    /* TODO */
    
    if(head->next == NULL){
        head->next = new Node<T>(data,head,NULL);
    }else{
        head->next = new Node<T>(data,head,head->next);
    }
    size++;
    //std::cout<<"pre"<<data<<std::endl;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)         //DONE
{
    /* TODO */
    if(containsNode(node)){
        Node<T>* newNode = new Node<T>(data);
        if(node->next != NULL){
            node->next->prev=newNode;
        }
        newNode->prev=node;
        newNode->next=node->next;
        node->next=newNode;
        size++;
    }else{
        //std::cout<<"insertafternode "<<node->data<<std::endl;
    }
    
}

template<class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)               //DONE           
{
    /* TODO */
    if(index >= 0 && index<size){
        //Node<T>* newNode = new Node<T>(data);
        if(index != 0){
        insertAfterNode(data,getNodeAtIndex(index-1));
        }else{
            prepend(data);
        }
    }/*else if(index==size){
        append(data);
    }*/
}

template<class T>
int LinkedList<T>::getIndex(Node<T> *node) const                          //DONE
{
    /* TODO */
    Node<T>* current = head->next;
    int i=0;
    while(current->next != NULL){
        if(current==node){
            return i;
        }
        current=current->next;
        i++;
    }
    
    return -1;
}

template<class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)           //DONE
{
    /* TODO */
    if(currentIndex >= 0 && currentIndex<size){
        Node<T> * current = getNodeAtIndex(currentIndex);
        Node<T> * newNode;
        if(newIndex<size){
            newNode = getNodeAtIndex(newIndex);
        }else{
            newNode = getLastNode();
        }
        if(current == head->next){
            head->next=current->next;
            current->next->prev = NULL;
        }else{
            current->prev->next=current->next;
            current->next->prev = current->prev;
        }
        current->prev=newNode;
        current->next=newNode->next;
        newNode->next=current;
        if(newNode->next != NULL){
            newNode->next->prev=current;
        }
    }
}

template<class T>
void LinkedList<T>::mergeNodes(int sourceIndex, int destIndex)
{
    /* TODO */
    if (sourceIndex < 0 || sourceIndex >= size || destIndex < 0 || destIndex >= size) {
        return; 
    }
    
    T sour = getNodeAtIndex(sourceIndex)->data;
    T dest = getNodeAtIndex(destIndex)->data;

    getNodeAtIndex(destIndex)->data = dest + sour; // Use operator+ for merging.

    removeNode(getNodeAtIndex(sourceIndex));
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node)  //Removing last node gives error
{   
    /* TODO */
    if(node || !(node == head)){
        if(node->prev != NULL){
            node->prev->next=node->next;
        }else{
            head->next=node->next;
        }
        if(node->next != NULL){
            node->next->prev=node->prev;
        }
        delete node;
        size--;

    }

}

template<class T>
void LinkedList<T>::removeNode(const T &data)    //DONE
{   
    /* TODO */
    Node<T>* current = head->next;
    while (current != NULL) {
        if (current->data == data) {
            Node<T>* nextNode = current->next;
            removeNode(current);
            current = nextNode;
        } else {
            current = current->next;
        }
    }
}

template<class T>
void LinkedList<T>::removeNodeAtIndex(int index)   //NOT WORKING
{
    /* TODO */
    if (index < 0 || index >= size || isEmpty()) {
        return; // Index is out of bounds or the list is empty; do nothing.
    }

    Node<T>* nodeToRemove = getNodeAtIndex(index);
    
    if (nodeToRemove) {
        removeNode(nodeToRemove);
    }
}

template<class T>
void LinkedList<T>::removeAllNodes()
{   
    /* TODO */
    /*Node<T>* current = head->next;
    if((!isEmpty())){
        Node<T>* nextNode = current->next ;
        while(current->next != NULL){
            delete current;
            current=nextNode;
            nextNode=current->next;
        }
    }
    head->next = NULL;
    size = 0;*/
    while(head->next){
        removeNodeAtIndex(0);
    }
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