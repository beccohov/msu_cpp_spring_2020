#include <iostream>
#include <assert.h>
#include"matrix.h"
using namespace std;
int main() {
    Matrix matrix_A(2,2);
    Matrix matrix_B(5, 5);
    Matrix matrix_C(5, 5);
    matrix_B[0][0] = 5;
    matrix_C[0][0] = 25;
    matrix_B *= 5;
    assert(matrix_A[0][0] == 0);
    matrix_A[0][0] = 5;
    assert(matrix_A[0][0] == 5);
    assert(matrix_B == matrix_C);
    assert(matrix_C != matrix_A);
    assert(matrix_B[0][0] == 25);
    try {
        matrix_B[9][9];
    }
    catch (exception &e) {
        cout <<e.what()<< " exception worked successfully\n";
    }
    cout << "All tests passed\n";
    return 0;
}