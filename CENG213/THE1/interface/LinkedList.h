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
LinkedList<T>::LinkedList() // Default constructor
{
    head = new Node<T>(T()); // Create a dummy head node with default data.
    size = 0; // Initialize the size to 0.
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &rhs) // Copy constructor
{
    head = new Node<T>(T()); // Create a dummy head node for the new list.
    size = 0; // Initialize the size to 0.
    Node<T>* current = rhs.head->next;
    while (current != NULL) {
        append(current->data); // Copy nodes from the source list to the new list.
        current = current->next;
    }
    size = rhs.size; // Set the size of the new list.
}

template<class T>
LinkedList<T>::~LinkedList() // Destructor
{
    removeAllNodes(); // Deallocate memory for all nodes and the head.
    delete head;
    size = 0; // Reset the size.
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) // Assignment operator
{
    if (this != &rhs) {
        removeAllNodes(); // Remove existing nodes in the current list.
        Node<T>* current = rhs.head->next;
        while (current) {
            append(current->data); // Copy nodes from the source list.
            current = current->next;
        }
    }
    return *this;
}

template<class T>
int LinkedList<T>::getSize() const
{
    return size; // Return the size of the linked list.
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
    return (size == 0); // Check if the list is empty.
}

template<class T>
bool LinkedList<T>::containsNode(Node<T> *node) const
{
    Node<T>* current = head->next;
    while (current != NULL) {
        if (node == current) {
            return true; // Check if the list contains the specified node.
        }
        current = current->next;
    }
    return false;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    if (isEmpty()) {
        return NULL; // Return the first node in the list or NULL if the list is empty.
    }
    return head->next;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    if (isEmpty()) {
        return NULL; // Return the last node in the list or NULL if the list is empty.
    }
    Node<T>* current = head->next;
    while (current->next != NULL) {
        current = current->next;
    }
    return current;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    Node<T>* current = head->next;
    while (current != NULL) {
        if (data == current->data) {
            return current; // Find and return the node with the specified data.
        }
        current = current->next;
    }
    return NULL;
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    if (index >= 0 && index < size) {
        Node<T>* current = head->next;
        int i = 0;
        while (i != index) {
            current = current->next;
            i++;
        }
        return current; // Find and return the node at the specified index.
    }
    return NULL;
}

template<class T>
void LinkedList<T>::append(const T &data)
{
    if (head->next == NULL) {
        head->next = new Node<T>(data, head, NULL); // Append a new node with data at the end.
    } else {
        Node<T>* current = head->next;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new Node<T>(data, current, NULL);
    }
    size++; // Increment the size.
}

template<class T>
void LinkedList<T>::prepend(const T &data)
{
    if (head->next == NULL) {
        head->next = new Node<T>(data, head, NULL); // Prepend a new node with data at the beginning.
    } else {
        head->next = new Node<T>(data, head, head->next);
    }
    size++; // Increment the size.
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    if (containsNode(node)) {
        Node<T>* newNode = new Node<T>(data);
        if (node->next != NULL) {
            node->next->prev = newNode;
        }
        newNode->prev = node;
        newNode->next = node->next;
        node->next = newNode; // Insert a new node with data after the specified node.
        size++; // Increment the size.
    }
}

template<class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)
{
    if (index >= 0 && index < size) {
        if (index != 0) {
            insertAfterNode(data, getNodeAtIndex(index - 1));
        } else {
            prepend(data); // Insert a new node with data at the specified index.
        }
    }
}

template<class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{
    Node<T>* current = head->next;
    int i = 0;
    while (current->next != NULL) {
        if (current == node) {
            return i; // Get the index of the specified node in the list.
        }
        current = current->next;
        i++;
    }
    return -1;
}

template<class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)
{
    if (currentIndex >= 0 && currentIndex < size) {
        Node<T>* current = getNodeAtIndex(currentIndex);
        Node<T>* newNode;
        if (newIndex < size) {
            newNode = getNodeAtIndex(newIndex);
        } else {
            newNode = getLastNode();
        }
        if (current == head->next) {
            head->next = current->next;
            current->next->prev = NULL;
        } else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }
        current->prev = newNode;
        current->next = newNode->next;
        newNode->next = current; // Move a node to the specified index.
        if (newNode->next != NULL) {
            newNode->next->prev = current;
        }
    }
}

template<class T>
void LinkedList<T>::mergeNodes(int sourceIndex, int destIndex)
{
    if (sourceIndex >= 0 && sourceIndex < size && destIndex >= 0 && destIndex < size) {
        T sour = getNodeAtIndex(sourceIndex)->data;
        T dest = getNodeAtIndex(destIndex)->data;
        getNodeAtIndex(destIndex)->data = dest + sour; // Merge the data of nodes at specified indices.
        removeNode(getNodeAtIndex(sourceIndex));
    }
}

template<class T>
void LinkedList<T>::removeNode(const T &data)
{
    Node<T>* current = head->next;
    while (current != NULL) {
        if (current->data == data) {
            Node<T>* nextNode = current->next;
            removeNode(current); // Remove nodes with the specified data.
            current = nextNode;
        } else {
            current = current->next;
        }
    }
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{
    if (node && !(node == head)) {
        if (node->prev != NULL) {
            node->prev->next = node->next;
        } else {
            head->next = node->next;
        }
        if (node->next != NULL) {
            node->next->prev = node->prev;
        }
        delete node; // Remove the specified node from the list.
        size--; // Decrement the size.
    }
}

template<class T>
void LinkedList<T>::removeNodeAtIndex(int index)
{
    if (index >= 0 && index < size && !isEmpty()) {
        Node<T>* nodeToRemove = getNodeAtIndex(index);
        if (nodeToRemove) {
            removeNode(nodeToRemove); // Remove the node at the specified index.
        }
    }
}

template<class T>
void LinkedList<T>::removeAllNodes()
{
    while (head->next) {
        removeNodeAtIndex(0); // Remove all nodes in the list.
    }
    size = 0; // Reset the size.
}

template<class T>
void LinkedList<T>::print() const
{
    if (isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T> *node = getFirstNode();

    while (node) {
        std::cout << *node << std::endl; // Print the contents of the list.
        node = node->next;
    }
}

#endif // LINKEDLIST_H
