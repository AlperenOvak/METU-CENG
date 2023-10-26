#include <iostream>
#include "LinkedList.h"

int main() {
    LinkedList<int> myList;

    // Append elements to the linked list
    myList.print();

    //std::cout << (myList.getLastNode()!=NULL);
    
    myList.append(1);
    myList.append(2);
    myList.append(3);
    myList.append(4);
    myList.append(5);
    std::cout << myList.getFirstNode()->data;
    std::cout << "Linked List: " << std::endl;
    myList.print();

    /*
    // Print the linked list
    std::cout << "Linked List: ";
    myList.print();

    // Prepend an element to the linked list
    myList.prepend(0);

    // Print the linked list after prepending
    std::cout << "Linked List after prepending: ";
    myList.print();

    // Insert an element at a specific index
    myList.insertAtIndex(99, 2);

    // Print the linked list after insertion
    std::cout << "Linked List after insertion: ";
    myList.print();

    // Remove an element by value
    myList.removeNode(3);

    // Print the linked list after removal
    std::cout << "Linked List after removal: ";
    myList.print();

    // Get the size of the linked list
    int size = myList.getSize();
    std::cout << "Size of the linked list: " << size << std::endl;

    // Check if the linked list is empty
    bool isEmpty = myList.isEmpty();
    std::cout << "Is the linked list empty? " << (isEmpty ? "Yes" : "No") << std::endl;*/

    return 0;
}
