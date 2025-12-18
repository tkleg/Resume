#include<iostream>
#include<armadillo>
using namespace arma;
using namespace std;

#ifdef PROB_5
int main() {
    mat A = {
        {2, -1, 1},
        {3, 3, 9},
        {3, 3, 5}
    };
    /*mat A = {
        {1.012, -2.132, 3.104},
        {-2.132, 4.096, -7.013},
        {3.104, -7.013, 00.014}
    };*/
    int n = A.n_rows;
    mat L = eye<mat>(n,n);
    mat U = zeros<mat>(n,n);

    for(int j = 1; j <= n; j++ )
        U(0,j-1) = A(0,j-1);
    for(int i = 2; i <= n; i++ )
        L(i-1,0) = A(i-1,0) / U(0,0);

    for(int i = 2; i <= n; i++ ){  // Changed to n, not n-1
        // Compute U elements (including diagonal)
        for(int j = i; j <= n; j++ ){
            double sumU = 0.0;
            for(int k = 1; k <= i-1; k++ )
                sumU += L(i-1,k-1) * U(k-1,j-1);
            U(i-1,j-1) = A(i-1,j-1) - sumU;
        }
        
        // Compute L elements (below diagonal only)
        for(int j = i+1; j <= n; j++ ){
            double sumL = 0.0;
            for(int k = 1; k <= i-1; k++ )
                sumL += L(j-1,k-1) * U(k-1,i-1);
            L(j-1,i-1) = (A(j-1,i-1) - sumL) / U(i-1,i-1);
        }
    }
    
    L.print("Lower Triangular Matrix L:");
    U.print("Upper Triangular Matrix U:");
    
    // Verify
    mat verify = L * U;
    bool isEqual = approx_equal(A, verify, "absdiff", 1e-10);
    if(isEqual)
        cout << "LU decomposition verified: A = L * U" << endl;
    else
        cout << "LU decomposition failed verification." << endl;
    
    return 0;
}
#endif