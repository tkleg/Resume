#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
#include<armadillo>
#include<limits>
using namespace std;
using namespace arma;

//typedef vector< vector<double> > d2Array;

//mat d2ArrayToMat( d2Array A );

//mat hilbertMatrixArma(int n);

int factorial(int n){
    if( n <= 1)
        return 1;
    return n * factorial( n - 1 );
}

mat hilbertExtend( mat A, int extensionSize = 1 );

double nthHilbertDeterminant( int n );

mat invertElements( mat A );

#ifdef HILBERT
int main(){

    int n = 1;
    mat H(1, 1, fill::ones);
    cout << scientific << setprecision(20);
    
    double sign;
    double val;
    bool detOk = log_det( val, sign, H );
    if( !detOk ){
        cout << "Initial determinant computation failed." << endl;
        return 1;
    }
    double determinant = exp(val);
    double minLog = log( numeric_limits<double>::min() );

    while( val > minLog ){
        cout << "n = " << n << ", det = " << exp(val) * sign << endl;

        n += 1;
        H = hilbertExtend( H );
        if( !H.is_symmetric() ){
            cout << "Matrix is not symmetric at n = " << n << endl;
            return 1;
        }
        
        detOk = log_det( val, sign, H );
        if( !detOk ){
            cout << "Determinant computation failed at n = " << n << endl;
            invertElements( H ).print("H inverse elements:");
            return 1;
        }
        determinant = exp(val) * sign;
    }
    cout << "n = " << n << ", det = " << determinant << endl;

    return 0;
}
#endif

double nthHilbertDeterminant( int n ){
    double numerator = 1.0;
    double denominator = 1.0;
    for(int i = 1; i < n; i++)
        numerator *= factorial(i);
    for(int i = 1; i < 2*n; i++)
        denominator *= factorial(i);
    return pow(numerator, 4) / denominator;
}

mat invertElements( mat A ){
    int n = A.n_rows;
    mat Ainv(n,n);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            Ainv(i,j) = 1.0 / A(i,j);
    return Ainv;
}

mat hilbertExtend( mat A, int extensionSize ){
    int n = A.n_rows;
    A.resize(n+extensionSize, n+extensionSize);
    for(int i = n; i < n + extensionSize; i++){
        for(int j = 0; j < n + extensionSize; j++){
            A(i,j) = 1.0 / ((i+1) + (j+1) - 1);
            A(j,i) = A(i,j);
        }
    }
    return A;
}