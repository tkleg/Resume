#include<iostream>
#include<armadillo>
#include<cmath>
using namespace arma;
using namespace std;

bool isSymmetric(mat A){
    return all(vectorise(A == A.t()));
}

bool isSingular(mat A){
    return det(A) == 0;
}

bool strictlyDiagonallyDominant(mat A);

bool positiveDefinite(mat A);

void testCase(mat A, char c);

#ifdef PROB_1
int main(){
    mat A = {
        {2, 1},
        {1, 3}
    };
    testCase(A, 'A');
    mat B = {
        {2, 1, 0},
        {0, 3, 0},
        {1, 0, 4}
    };
    testCase(B, 'B');
    mat C = {
        {4, 2, 6},
        {3, 0, 7},
        {-2, -1, -3}
    };
    testCase(C, 'C');
    mat D = {
        {4, 0, 0, 0},
        {6, 7, 0, 0},
        {9, 11, 1, 0},
        {5, 4, 1, 1}
    };
    testCase(D, 'D');
    return 0;
}
#endif

bool positiveDefinite(mat A){ 
    bool symmetric = isSymmetric(A);
    if( !symmetric )
        return false;

    vec eigenVals;
    eig_sym(eigenVals, A);
    for( int i = 0; i < eigenVals.n_elem; i++ )
        if( eigenVals(i) <= 0 )
            return false;
    return true;
    /*int n = A.n_rows;

    //Invertible check
    mat Ainv;
    bool invertible = inv(Ainv, A);
    if( !invertible )
        return false;
    for(int i = 0; i <n; i++ )
        if( A(i, i) <= 0 )
            return false;
    
    //Check a_ij^2 < a_ii * a_jj
    for(int i = 0; i < n; i++ )
        for( int j = 0; j < n; j++ ){
            if( i == j )
                continue;
            if( pow(A(i,j), 2) >= A(i,i) * A(j,j) )
                return false;
        }
    
    //Check max|a_ij| < max|a_ii|
    vec diag = A.diag();
    double matrixMax = abs(A).max();
    double diagMax = diag.max();
    if( matrixMax > diagMax )
        return false;
    
    //Check all diagonal entries positive
    for( int i = 0; i < n; i++ )
        if( diag(i) <= 0 )
            return false;
    
    return true;*/
} 

void testCase(mat A, char c){
    cout << "Matrix " << c << endl;
    //A.print();
    cout << "Is " << c << " symmetric? " << (isSymmetric(A) ? "Yes" : "No") << endl;
    cout << "Is " << c << " singular? " << (isSingular(A) ? "Yes" : "No") << endl;
    cout << "Is " << c << " strictly diagonally dominant? " << (strictlyDiagonallyDominant(A) ? "Yes" : "No") << endl;
    cout << "Is " << c << " positive definite? " << (positiveDefinite(A) ? "Yes" : "No") << endl;
    cout << endl;
}

bool strictlyDiagonallyDominant(mat A){
    int n = A.n_rows;
    for(int x = 0; x < n; x++ ){
        double rowSum = 0;
        for( int y = 0; y < A.n_cols; y++ ){
            if( x == y )
                continue;
            rowSum += fabs(A(x,y));
        }
        if( abs(A(x,x)) <= rowSum )
            return false;
    }
    return true;
}