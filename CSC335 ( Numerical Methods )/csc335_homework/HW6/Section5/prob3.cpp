#include<iostream>
#include<armadillo>
using namespace arma;
using namespace std;

#ifdef PROB_3
int main(){
    //Partial Pivoting
    mat A = {
        {1, 2, -1},
        {2, 4, 0},
        {0, 1, -1}
    };
    int row_count = A.n_rows;
    int col_count = A.n_cols;
    mat P = eye(row_count, row_count);  // Overall Permutation Matrix
    mat L, U, P_total;
    /*lu(L, U, P_total, A);
    A.print("Original Matrix A:");
    L.print("Lower Triangular Matrix L:");
    U.print("Upper Triangular Matrix U:");
    P_total.print("Overall Permutation Matrix P from lu():");
*/
    L = eye(row_count, row_count); // Lower Triangular Matrix

    mat P1 = {
        {0, 1, 0},
        {1, 0, 0},
        {0, 0, 1}
    };

    //P.swap_rows(0,1);  // Update Overall Permutation Matrix

//    mat Prod = P1 * A;
//    Prod.print("After 1st Pivoting:");

    mat M3 = eye(3,3);
    M3(1,0) = -A(1,0) / A(0,0);
    M3(2,0) = -A(2,0) / A(0,0);
    M3.print("1st Elimination Matrix M3:");
    L(1,0) = -M3(1,0); // Update L
    L(2,0) = -M3(2,0); // Update L

    mat R1 = M3 * A;
    R1.print("After 1st Elimination:");

    mat P2 = {
        {1, 0, 0},
        {0, 0, 1},
        {0, 1, 0}
    };

    P.swap_rows(1,2);  // Update Overall Permutation Matrix
    mat Prod = P2 * R1;
    Prod.print("After 2nd Pivoting:");
/*
    P.swap_rows(1,2);  // Update Overall Permutation Matrix
    Prod = P2 * R1;
    Prod.print("After 2nd Pivoting:");

    M3 = eye(3,3);
    M3(2,1) = -Prod(2,1) / Prod(1,1);
    L(2,1) = -M3(2,1); // Update L
    mat R2 = M3 * Prod;
    R2.print("After 2nd Elimination:");
*/
    P.print("Overall Permutation Matrix P:");
    L.print("Lower Triangular Matrix L:");
    Prod.print("Upper Triangular Matrix U (Modified A):");
    return 0;
}
#endif
