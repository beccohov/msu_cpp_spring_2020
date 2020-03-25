#include "matrix.h"
#include <stdexcept>
#include <iostream>
Matrix::Matrix(int rows_, int  columns_)
{
    rows_shape = rows_;
    columns_shape = columns_;
    rows = new Row*[rows_];
    if (!rows) throw std::bad_alloc();
    for (int i = 0; i < rows_; i++) {
        rows[i] = new Row(columns_);
        if (!rows) throw std::bad_alloc();
    }
}
Matrix::Row::Row(int columns_)
{
    row = new int[columns_](); //Zero initializing
    columns = columns_;
    if (!row) throw std::bad_alloc();
}
Matrix::Row::~Row()
{
    delete[] row;
}
int & Matrix::Row::operator[](int j)
{
    if (j >= columns) throw std::out_of_range("");
    return row[j];
}
Matrix::Row & Matrix::operator[](int i)
{
   if (i >= rows_shape) throw std::out_of_range("");
   return *rows[i];
}
bool Matrix::operator!=(Matrix & matrix)
{
    bool not_equal = true;
    if (columns_shape != matrix.columns_shape || rows_shape != matrix.rows_shape) return not_equal;
    for (int i = 0; i < rows_shape; i++) {
        for (int j = 0 ; j < columns_shape; j++) 
            if ((*this)[i][j] != matrix[i][j]) {
                return not_equal;
            }
    }
    return false; //equal
}
bool Matrix::operator==(Matrix & matrix)
{
    return !((*this) != matrix);
}
Matrix & Matrix::operator*=(int number)
{
    for (int i = 0; i < rows_shape; i++)
        for (int j = 0; j < columns_shape; j++)
            (*this)[i][j] *= number;
    return *this;
}
int Matrix::getColumnsSize()
{
    return  columns_shape;
}
int Matrix::getRowsSize()
{
    return rows_shape;
}