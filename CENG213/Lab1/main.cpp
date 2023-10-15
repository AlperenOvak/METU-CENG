#include <iostream>
#include "matrix.cpp"

using namespace std;

int main(){
    //You can test your implementation here.

    //Initialize matrix1 and matrix2
    Matrix matrix1(4);
    Matrix matrix2(4);

    Matrix resultAddition = matrix1 + matrix2;
    Matrix resultSubtraction = matrix1 - matrix2;
    bool isEqual = (matrix1 == matrix2);

    std::cout << isEqual << std::endl;
}