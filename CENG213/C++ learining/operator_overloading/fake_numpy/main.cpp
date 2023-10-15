#include <iostream>
#include "fake_numpy.h"
#include "fake_numpy.cpp"

int main() {
    FakeNumpy array1({1, 2, 3, 4});
    FakeNumpy array2({5, 6, 7, 8});

    FakeNumpy result = array1 + array2;
    std::cout << "Array1 + Array2: ";
    result.print();

    result = array1 - array2;
    std::cout << "Array1 - Array2: ";
    result.print();

    result = array1 * array2;
    std::cout << "Array1 * Array2: ";
    result.print();

    result = array1 / array2;
    std::cout << "Array1 / Array2: ";
    result.print();

    
    std::cout << (array1 == array2);

    return 0;
}



