#include <iostream>
#include "LinkedList.h"
#include "Node.h"

int main() {
    LinkedList<int> myList;
    LinkedList<int> myList2;
    Node<int> *a;

    // Append elements to the linked list
    myList.print();

    //std::cout << (myList.getLastNode()!=NULL);
    
    myList.append(1);
    myList.append(2);
    myList.append(3);
    myList.append(4);
    myList.append(5);
    //std::cout << myList.getFirstNode()->data;
    std::cout << "Linked List: " << std::endl;
    myList.print();
   

    // Prepend an element to the linked list
    myList.prepend(0);

    // Print the linked list after prepending
    std::cout << "Linked List after prepending: "<< std::endl;
    myList.print();

    myList.removeAllNodes();
    std::cout << "Linked List after removeAllNodes: "<< std::endl;
    myList.print();
    myList.removeAllNodes();
    std::cout << "Linked List after removeALL: "<< std::endl;
    myList.print();
    a=myList.getFirstNode();
    myList.append(5);
    myList.append(3);
    myList.append(5);
    myList.append(4);
    myList.append(6);
    myList.append(7);
    std::cout << "contains?"<< myList.containsNode(a) << std::endl;
    myList.print();

    a=myList.getLastNode();
    myList.removeNode(a);
    std::cout << "delete lst?"<< myList.containsNode(a) << std::endl;
    myList.print();

    myList.removeAllNodes();
    std::cout << "remove all"<<  std::endl;
    myList.print();

    myList.removeNodeAtIndex(5);
    std::cout << "remove0"<<  std::endl;
    myList.print();

    /*myList.removeNode(5);
    std::cout << "remove5s"<< myList.containsNode(a) << std::endl;
    myList.print();

    

    myList2=myList;
    std::cout << "=op"<<  std::endl;
    myList.print();

    LinkedList<int> copiedList(myList);

    // Print the original list
    std::cout << "Original List: " << std::endl;
    myList.print();

    // Print the copied list
    std::cout << "Copied List: "<< std::endl;
    copiedList.print();

    myList.moveToIndex(3,3);
    std::cout << "Linked List after moveToIndex: " << std::endl;
    myList.print();


    //myList.append(6);
    

    myList.removeNode(7);
    std::cout << "remove7s"<< myList.containsNode(a) << std::endl;
    myList.print();
    
    

    /*std::cout << "get index 1 = "<< myList.getNodeAtIndex(3) << std::endl;


    myList.insertAfterNode(31,myList.getNodeAtIndex(2));
    std::cout << "Linked List after insertAfterNode: "<< std::endl;
    myList.print();

    // Insert an element at a specific index
    myList.insertAtIndex(99, 3);

    // Print the linked list after insertion
    std::cout << "Linked List after insertion: " << std::endl;
    myList.print();

    std::cout << "getIndex= "<< myList.getIndex(myList.getNodeAtIndex(3)) << std::endl;


    myList.moveToIndex(0,15);
    std::cout << "Linked List after moveToIndex: " << std::endl;
    myList.print();

    myList.removeNode(myList.getNodeAtIndex(3));
    std::cout << "Linked List after removeNode*: " << std::endl;
    myList.print();
*/
    /*myList.removeNode(3);
    std::cout << "Linked List after removeNode: " << std::endl;
    myList.print();*/

    /*myList.getNodeAtIndex(1);
    std::cout << "Linked List after getNodeAtIndex: " << std::endl;
    myList.print();
    /*

    

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
