#include "myarray.h"

MyArray::MyArray(){
    arr=new int[1];
    n=0;
    size=1;
};
MyArray::MyArray(int first_el){
    arr= new int[2];
    n=1;
    size=2;
    arr[0]=first_el;
};
MyArray::MyArray(const int* elemnets, int count){
    size=count*2;
    n=count;
    arr=new int[size];
    for(int i=0;i<size;i++){
        arr[i]=elemnets[i];
    }
};
MyArray::~MyArray(){
    size=0;
    n=0;
    delete []arr;
};
MyArray::MyArray(const MyArray& rhs){
    arr=new int[rhs.size];
    size=rhs.size;
    n=rhs.n;
    for(int i=0;i<size;i++){
        arr[i]=rhs.arr[i];
    }
};
MyArray::MyArray& operator=(const MyArray& rhs){
    int* new_arr = new int[rhs.size];
    if(this != &rhs){
        size=rhs.size;
        n=rhs.n;
        for(int i=0;i<size;i++){
            arr[i]=rhs.arr[i];
        }
        delete []arr;
        arr=new_arr;
    }
    return *this;
};
void MyArray::double_size(){
    int* db_arr= new int[size*2];
    for(int i=0;i<size;i++){
        db_arr[i]=arr[i];
    }
    delete []arr;
    arr=db_arr;
    size*=2;
};
void MyArray::append_data(int el){
    if(n==size){
        double_size();
    }
    
    n++;
    arr[n]=el;
};
void MyArray::insert_front(int el){
    if(n==size){
        double_size();
    }
    for(int i=n-1;i>-1;i--){
        arr[i+1]=arr[i];
    }
    n++;
    arr[0]=el;
};
void MyArray::delete_data(int ind){
    int i;
    if(ind != n-1){
        for(i=ind;i<n-1;i++){
            arr[i]=arr[i+1];
        }
    }
    n-=1;
};
int MyArray::get_element(int ind)const{
    return arr[ind];
};
void MyArray::print(char separtor = '\0')const{
    if(n==0){
        std::cout<<"[]";
        return;
    }
    std::cout<<"[";
    for(int i=0;i<n;i++){
        if(n>=500) return;
        std:cout<<arr[i]<<separtor;
    }
    std::cout<<arr[n-1];
    std::cout<<"]";
};
int MyArray::get_n()const{
    reutn n;
};
int MyArray::get_size() const{
    return size;
};