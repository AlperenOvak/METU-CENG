#include "matrix.h"


Matrix::Matrix(int dimension)
{
    n=dimension;
    int** a = new int*[dimension];

    for(int i=0;i<n;i++){
        a[i]=new int [dimension];
        for(int j=0;j<n;j++){
            a[i][j]=0;
        }
    }
    matrix = a;
}

Matrix::~Matrix(){
    for(int i=0;i<n;i++){
        delete[]matrix[i];
    }
    delete[] matrix;
}

int Matrix::get_dimension() const{
    return n;
}

int Matrix::get_number(int i,int j)const{
    if ((i<n)&&(j<n)){
        return matrix[i][j];
    }
    return 0;
}

void Matrix::set_number(int i,int j, int value)const{
    if ((i<n)&&(j<n)){
        matrix[i][j] = value;
    }
}

Matrix& Matrix::operator=(const Matrix& rhs){
    if(n!=rhs.n)return *this;

    int i,j;
    n=rhs.get_dimension();
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            matrix[i][j] = rhs.get_number(i,j);
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& rhs)const{
    
    Matrix a= Matrix(rhs.n);
    if(n!=rhs.n)return *this;

    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            a.matrix[i][j] = matrix[i][j]+rhs.get_number(i,j);
        }
    }
    return a;
}

Matrix Matrix::operator-(const Matrix& rhs)const{
    
    Matrix a= Matrix(rhs.n);
    if(n!=rhs.n)return *this;

    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            a.matrix[i][j] = matrix[i][j]-rhs.get_number(i,j);
        }
    }
    return a;
}

bool Matrix::operator==(const Matrix& rhs)const{
    
    
    if(n!=rhs.n) return 0;

    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(matrix[i][j] != rhs.get_number(i,j)){
                return 0;
            } 
        }
    }
    return 1;
}