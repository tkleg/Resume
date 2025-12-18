#include<iostream>
#include<armadillo>
#include<cmath>
using namespace arma;
using namespace std;

#ifdef PROB_5
int main(){
    mat A = {
        {6, 2, 1, -1},
        {2, 4, 1, 0},
        {1, 1, 4, -1},
        {-1, 0, -1, 3}
    };
    int n = A.n_rows;
    //Commented out to show manual computation
    mat L = eye<mat>(n, n);
    //L = chol(A).t(); // Get lower triangular matrix from Cholesky
    L(0,0) = sqrt( A(0,0) );
    for( int j = 2; j <= n; j++ )
        L(j-1,0) = A(j-1,0) / L(0,0);
    for( int i = 2; i <= n-1; i++ ){
        double sum = 0.0;
        for( int k = 1; k <= i-1; k++ )
            sum += pow( L(i-1,k-1), 2 );
        L(i-1,i-1) = sqrt( A(i-1,i-1) - sum );
        for( int j = i+1; j <= n; j++ ){
            sum = 0.0;
            for( int k = 1; k <= i-1; k++ )
                sum += L(j-1,k-1) * L(i-1,k-1);
            L(j-1,i-1) = ( A(j-1,i-1) - sum ) / L(i-1,i-1);
        }
    }
    // Last diagonal element
    double sum = 0.0;
    for( int k = 1; k <= n-1; k++ )
        sum += pow( L(n-1,k-1), 2 );
    L(n-1,n-1) = sqrt( A(n-1,n-1) - sum );
    L.print("L = ");
    return 0;
}
#endif