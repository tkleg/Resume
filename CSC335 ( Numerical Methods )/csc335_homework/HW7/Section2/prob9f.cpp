#include<iostream>
#include<armadillo>
#include<cmath>
#include<optional>
#include<iomanip>
using namespace std;
using namespace arma;

#ifdef PROB_9F
int main(){
    mat A = {
        {2, 1, 1},
        {2, 3, 2},
        {1, 1, 2}
    };
    mat At = A.t();
    mat M = At * A;
    cx_vec eigval;
    cx_mat eigvec;
    eig_gen(eigval, eigvec, M);
    cout << fixed << setprecision(10);
    cout << "2-Norm of matrix A = " << sqrt( abs( real(eigval) ).max() ) << endl;

    return 0;
}
#endif