#include <iostream>
#include <string>

class ListException : public std::runtime_error {
public:
    ListException(const std::string& message) : std::runtime_error(message) {}
};

template <class T>
class Node {
public:
    Node(const T& e = T(), Node* n = nullptr);
    T element;
    Node* next;
};

template <class T>
class List {
private:
    Node<T>* dummyHead;

public:
    // Constructor
    List();

    // Destructor
    ~List();

    // Copy constructor
    List(const List& rhs);

    // Assignment operator
    List& operator=(const List& rhs);

    // Returns the zeroth node (dummy head)
    Node<T>* zeroth() const;

    // Returns the first node
    Node<T>* first() const;

    // Checks if the list is empty
    bool isEmpty() const;

    // Inserts a new node with data after the given node p
    void insert(const T& data, Node<T>* p);

    // Finds the first occurrence of data in the list and returns its node
    Node<T>* find(const T& data) const;

    // Finds the node with data and returns its previous node
    Node<T>* findPrevious(const T& data);

    // Removes the first occurrence of data from the list
    void remove(const T& data);

    // Makes the list empty
    void makeEmpty();

    T &operator[](int i) const;
    List<T> operator*(const List<T> &rhs) const;
};

// Implementation of the Node class
template <class T>
Node<T>::Node(const T& e, Node* n) : element(e), next(n) {}

// Implementation of the List class

// Constructor
template <class T>
List<T>::List() {
    dummyHead = new Node<T>();
}

// Destructor
template <class T>
List<T>::~List() {
    makeEmpty();
    delete dummyHead;
}

// Copy constructor
template <class T>
List<T>::List(const List& rhs) {
    dummyHead = new Node<T>();
    Node<T>* rhsCurrent = rhs.first();
    Node<T>* current = dummyHead;

    while (rhsCurrent != nullptr) {
        current->next = new Node<T>(rhsCurrent->element);
        current = current->next;
        rhsCurrent = rhsCurrent->next;
    }
}

// Assignment operator
template <class T>
List<T>& List<T>::operator=(const List& rhs) {
    if (this != &rhs) {
        makeEmpty();

        Node<T>* rhsCurrent = rhs.first();
        Node<T>* current = dummyHead;

        while (rhsCurrent != nullptr) {
            current->next = new Node<T>(rhsCurrent->element);
            current = current->next;
            rhsCurrent = rhsCurrent->next;
        }
    }
    return *this;
}

// Returns the zeroth node (dummy head)
template <class T>
Node<T>* List<T>::zeroth() const {
    return dummyHead;
}

// Returns the first node
template <class T>
Node<T>* List<T>::first() const {
    return dummyHead->next;
}

// Checks if the list is empty
template <class T>
bool List<T>::isEmpty() const {
    return dummyHead->next == nullptr;
}

// Inserts a new node with data after the given node p
template <class T>
void List<T>::insert(const T& data, Node<T>* p) {
    if (p != nullptr) {
        p->next = new Node<T>(data, p->next);
    }
}

// Finds the first occurrence of data in the list and returns its node
template <class T>
Node<T>* List<T>::find(const T& data) const {
    Node<T>* current = dummyHead->next;

    while (current != nullptr && current->element != data) {
        current = current->next;
    }

    return current;
}

// Finds the node with data and returns its previous node
template <class T>
Node<T>* List<T>::findPrevious(const T& data) {
    Node<T>* current = dummyHead;

    while (current->next != nullptr && current->next->element != data) {
        current = current->next;
    }

    return current;
}

// Removes the first occurrence of data from the list
template <class T>
void List<T>::remove(const T& data) {
    Node<T>* prevNode = findPrevious(data);

    if (prevNode->next != nullptr) {
        Node<T>* temp = prevNode->next;
        prevNode->next = temp->next;
        delete temp;
    }
}

// Makes the list empty
template <class T>
void List<T>::makeEmpty() {
    while (!isEmpty()) {
        remove(first()->element);
    }
}


template <class T>
T& List<T>::operator[](int i) const {
    Node<T> *p = dummyHead;
    if(!isEmpty()){
        while(i && p){
            p=p->next;
            i--;
        }
        if(p){
            return p->element;
        }else{
            throw ListException( "No such element on operator [] " );            
        }
    }
    throw ListException( "No such element on operator [] " );
}

template <class T>
List<T> List<T>::operator*(const List<T> &rhs) const {
    List<T> result;
    Node<T> *p=first();
    Node<T> *r=result.zeroth();
    while(p){
        if(rhs.find(p->element)){
           result.insert(p->element,r);
           r=r->next;
        }
        p=p->next;
    }

    return result;
}

int main() {
    try {
        List<int> myList;

        std::cout << "Is the list empty?" << (myList.isEmpty() ? "Yes" : "No") << std::endl;

        myList.insert(10, myList.zeroth());
        myList.insert(20, myList.first());
        myList.insert(30, myList.first()->next);

        std::cout << "List contents: ";
        Node<int>* current = myList.first();
        while (current != nullptr) {
            std::cout << current->element << " ";
            current = current->next;
        }
        std::cout << std::endl;

        int searchValue = 20;
        Node<int>* foundNode = myList.find(searchValue);
        if (foundNode != nullptr) {
            std::cout << "Found " << searchValue << " in the list." << std::endl;
        } else {
            std::cout << searchValue << " not found in the list." << std::endl;
        }

        std::cout << "Element at index 2: " << myList[4] << std::endl; // This will throw an exception since 40 is not in the list

    } catch (const ListException& ex) {
        std::cerr << "List Exception: " << ex.what() << std::endl;
    }

    return 0;
}
