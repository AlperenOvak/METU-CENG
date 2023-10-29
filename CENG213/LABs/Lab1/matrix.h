#ifndef __matrix_v1_hpp__
#define __matrix_v1_hpp__

#include <iostream>

class Matrix{
    public:
        /*****************************/
        /* Initialization */
        //Constructor. The default value for dimension is 4.
        Matrix(int dimension=4);
        //Destructor
        ~Matrix();
        /*****************************/
        /*  Member Operations*/

        //Getter Function for dimension value
        int get_dimension() const;
        //Getter Funciton for ith and jth member of matrix
        //Check if i and j are within matrix boundry
        int get_number(int i,int j) const;
        //Setter functiom
        //Check if i and j are within matrix boundry
        void set_number(int i,int j,int value)const;

        Matrix& operator=(const Matrix& rhs);

        Matrix operator+(const Matrix& rhs) const;

        Matrix operator-(const Matrix& rhs) const;

        bool operator==(const Matrix& rhs) const;

        friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    private:
        int n;
        int** matrix;
};

#endif