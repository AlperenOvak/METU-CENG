#include <iostream>
#include "fake_numpy.h"

// Default constructor
FakeNumpy::FakeNumpy() {}

// Parameterized constructor
FakeNumpy::FakeNumpy(std::vector<double> array) : data(array) {}

// Overload addition operator
FakeNumpy FakeNumpy::operator+(const FakeNumpy& other){
    if (data.size() != other.data.size()) {
        throw std::invalid_argument("Array sizes must match for addition.");
    }
    FakeNumpy result;
    result.data.resize(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        result.data[i] = data[i] + other.data[i];
    }
    return result;
}

// Overload subtraction operator
FakeNumpy FakeNumpy::operator-(const FakeNumpy& other){
    if (data.size() != other.data.size()) {
        throw std::invalid_argument("Array sizes must match for addition.");
    }
    FakeNumpy result;
    result.data.resize(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        result.data[i] = data[i] - other.data[i];
    }
    return result;
}

// Overload equality operator
bool FakeNumpy::operator==(const FakeNumpy& other){
    if (data.size() != other.data.size()) {
        return 0;
    }
    for (size_t i = 0; i < data.size(); ++i) {
        if(data[i] != other.data[i]){
            return 0;
        } ;
    }
    return 1;
}

// Overload multiplication operator
FakeNumpy FakeNumpy::operator*(const FakeNumpy& other) {
    if (data.size() != other.data.size()) {
        throw std::invalid_argument("Array sizes must match for multiplication.");
    }
    FakeNumpy result;
    result.data.resize(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        result.data[i] = data[i] * other.data[i];
    }
    return result;
}

// Overload division operator
FakeNumpy FakeNumpy::operator/(const FakeNumpy& other) {
    if (data.size() != other.data.size()) {
        throw std::invalid_argument("Array sizes must match for division.");
    }
    FakeNumpy result;
    result.data.resize(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        if (other.data[i] == 0) {
            throw std::invalid_argument("Division by zero is not allowed.");
        }
        result.data[i] = data[i] / other.data[i];
    }
    return result;
}


// Function to print the elements of the array
void FakeNumpy::print() {
    for (const double& val : data) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}