#include <iostream>

class IntCell{
    public:
        IntCell(int c,int d){
            a = new int(c);
            b = new int(d);
        }
        ~IntCell(){    // in the custom desturctor, we just delete the pointer a
            delete a;
        }
        void read(){
            std::cout<< *a << " "<< *b << std::endl;
        }
        
        private:
            int *a;
            int *b;
};

int main() {
    IntCell kal(3,5);
    kal.~IntCell();    // call the custom destructor
    kal.read();        // let's check what happens when we check value of a and b

    return 0;
}