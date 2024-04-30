#include <iostream>
#include <cstring>
int v = -1;
class ConstTest {
private:
    char *data;
    int intValue;
public:
    // Constructor
    // Constructor for no type
    ConstTest() {
        data = new char[6]; // "Empty" + '\0'
        strcpy(data, "Empty");
        intValue = v--;
        std::cout<<"Cons("<<"" <<")-->:("<<intValue<<","<<data<<") constructed\n";
    }
    
    ConstTest(const char *value) {
        data = new char[strlen(value) + 1];
        strcpy(data, value);
        intValue = -1; // Set int value to -1 for string type
        std::cout<<"Cons("<<"char*" <<")-->:("<<intValue<<","<<data<<") constructed\n";
    }
    
    // Constructor for int type
    ConstTest(int value) {
        data = new char[6]; // "Empty" + '\0'
        strcpy(data, "NoName");
        intValue = value;
        std::cout<<"Cons("<<"int" <<")-->:("<<intValue<<","<<data<<") constructed\n";
    }
    
    // Copy Constructor
    ConstTest(const ConstTest &other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
        intValue = other.intValue +100;
        std::cout<<"Cons("<<"Cons" <<")-->:KOPYA("<<intValue<<","<<data<<") constructed\n";
    }
    
    // Destructor
    ~ConstTest() {
        std::cout<<"~Cons("<<"" <<")-->:("<<intValue<<","<<data<<") destructed\n";
        delete[] data;
    }
    
    // Output method
    void out() const {
        std::cout << "("<<intValue << ","<< data<<")\n";
    }
} x("global"),*p;

ConstTest j(){
    ConstTest tmp("uzum");
    std::cout << "inside j, tmp is: ";
    tmp.out(); std::cout << "\n";
    return tmp;
}

ConstTest g(ConstTest &tmp){
    std::cout << "inside g, tmp is: ";
    tmp.out(); std::cout << "\n";
    return tmp;
}

ConstTest h(ConstTest tmp){
    std::cout << "inside h, tmp is: ";
    tmp.out(); std::cout << "\n";
    return tmp;
}

void f(ConstTest z){
    ConstTest t("f:t");
    std::cout << "inside f, z is: ";
    z.out(); std::cout << " \n ";
    
    p=new ConstTest[2];
}

int main() {
    // Write C++ code here
    ConstTest a("elma"), b(15), c("armut");
    
    std::cout << "1------------------\n";
    f(c);
    std::cout << "2------------------\n";
    g(b).out();
    std::cout << "3------------------\n";
    h(b).out();
    std::cout << "4------------------\n";
    j().out();
    std::cout << "5------------------\n";

    return 0;
}
