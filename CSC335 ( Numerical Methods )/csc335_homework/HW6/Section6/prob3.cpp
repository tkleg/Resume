#include<iostream>
#include<armadillo>
#include<cmath>
using namespace arma;
using namespace std;

#ifdef PROB_3
int main(){
    mat A = {
        {6, 2, 1, -1},
        {2, 4, 1, 0},
        {1, 1, 4, -1},
        {-1, 0, -1, 3}
    };

    int n = A.n_rows;
    vec v(n);
    vec D = zeros<vec>(n);
    mat L = eye<mat>(n,n);

    for( int i = 1; i <= n; i++ ){
        for(int j = 1; j <= i-1; j++)
            v(j-1) = L(i-1,j-1) * D(j-1);
        for(int j = 1; j <= i-1; j++)
            D(i-1) -= L(i-1,j-1) * v(j-1);
        D(i-1) += A(i-1,i-1);
        for(int j = i+1; j <= n; j++){
            L(j-1,i-1) = A(j-1,i-1);
            for(int k = 1; k <= i-1; k++)
                L(j-1,i-1) -= L(j-1,k-1) * v(k-1);
            L(j-1,i-1) /= D(i-1);
        }
    }
    L.print("L = ");
    D.print("D = ");

    return 0;
}
#endif