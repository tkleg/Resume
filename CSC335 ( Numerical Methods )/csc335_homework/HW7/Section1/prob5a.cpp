#include<iostream>
#include<armadillo>
#include<cmath>
#include<optional>
using namespace std;
using namespace arma;

#ifdef PROB_5A
int main(){
    mat A = {
        {10, 15},
        {0, 1}
    };
    double norm_inf = NAN;
    for (int i = 0; i < A.n_rows; i++) {
        double row_sum = 0;
        for (int j = 0; j < A.n_cols; j++)
            row_sum += fabs(A(i, j));
        if (row_sum > norm_inf || isnan(norm_inf)) 
            norm_inf = row_sum;
    }
    cout << "Infinity norm of matrix A: " << norm_inf << endl;
    return 0;
}
#endif