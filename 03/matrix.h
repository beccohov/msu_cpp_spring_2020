#pragma once
#include <stdexcept>
class Matrix {
public:
    class Row {
    public:
        int& operator[](int);
        Row(int);
        ~Row();
    private:
        int* row;
        int columns;
    };
    Matrix& operator*=(int);
    Matrix(int,int);
    int getRowsSize();
    int getColumnsSize();
    bool operator==(Matrix&);
    bool operator!=(Matrix&);
    Row& operator[](int);
private:
    Row** rows;
    int rows_shape;
    int columns_shape;
};