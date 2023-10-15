#ifndef FakeNumpy_H
#define FakeNumpy_H

#include <vector>

class FakeNumpy {
private:
    std::vector<double> data;

public:
    FakeNumpy();
    FakeNumpy(std::vector<double> array);
    FakeNumpy operator+(const FakeNumpy& other);
    FakeNumpy operator-(const FakeNumpy& other);
    bool operator==(const FakeNumpy& other);
    FakeNumpy operator*(const FakeNumpy& other);
    FakeNumpy operator/(const FakeNumpy& other);
    void print();
};

#endif