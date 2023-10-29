#ifndef __myarray_h__
#define __myarray_h__

#include <iostream>

class MyArray
{
    public:
        MyArray();
        MyArray(int first_el);
        MyArray(const int* elemnets, int count);
        ~MyArray();
        MyArray(const MyArray& rhs);
        MyArray& operator=(const MyArray& rhs);
        void double_size();
        void append_data(int el);
        void insert_front(int el);
        void delete_data(int ind);
        int get_element(int ind)const;
        void print(char separtor = '\0')const;
        int get_n()const;
        int get_size() const;
    private:
        int* arr;
        int n;
        int size;
};

#endif