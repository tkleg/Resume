#include<iostream>
#include<armadillo>
#include<cmath>
#include<fstream>
#include<iomanip>
#include<vector>
using namespace arma;
using namespace std;

cx_dmat matrix(int N);

complex<double> f(int j, int k, int N);

cx_double sumOfDiagonal( cx_dmat M );

double PI = acos(-1);

#ifdef COMPLEX
int main(){

    #ifdef GRAPH
        cout << "Enter Max N: ";
        int N, MaxN;
        cin >> MaxN;
        N = 1;
        ofstream fout("diag_sums.dat");
        while( N <= MaxN ){
            cout << "N = " << N << endl;
            cx_dmat M = matrix(N);
            //M.print("M = ");
            cx_dmat I = M * inv(M);
            //I.print("M * M^-1 = ");
            cx_double diagSum = sumOfDiagonal( I );
            //cout << "Sum of diagonal elements: " << diagSum << endl;
            fout << N << " " << real(diagSum) << " " << imag(diagSum) << endl;
            N++;
        }
        fout.close();
    #endif
    #ifdef FIND_MAX
    
        int N = 1;
        cx_dmat M = matrix(N);
        cx_dmat Mi = inv(M);
        cx_dmat I = M * Mi;
        cx_double diagSum = sumOfDiagonal( I );
        while( abs(real(diagSum) - max(N-1, 1)) < 1e-5 ){
            if( N < 10 ){
                I.print("M * M^-1 = ");
            }
            //I.print("M * M^-1 = ");
            diagSum = sumOfDiagonal( I );
            if( isnan(real(diagSum)) || isnan(imag(diagSum)) ||
                isinf(real(diagSum)) || isinf(imag(diagSum)) ){
                cout << "Diagonal sum became NaN or Inf at N = " << N << endl;
                break;
            }
            cout << "N = " << N << ", Sum of diagonal elements: " << diagSum << endl;
            N += 1;
            M = matrix(N);
            Mi = inv(M);
            I = M * Mi;
        }
        cout << scientific << setprecision(20);
        cout << "Maximum N before failure: " << N-1 << endl;
        cout << "Final diagonal sum real value: " << real(diagSum) << endl;
    #endif


    return 0;
}
#endif

cx_double sumOfDiagonal( cx_dmat M ){
    cx_double sum(0.0,0.0);
    for( int i = 0; i < M.n_rows; i++ )
        sum += M(i,i);
    return sum;
}

cx_dmat matrix(int N){
    cx_dmat M(N,N);
    for( int j = 0; j < N; j++ )
        for( int k = 0; k < N; k++ )
            M(j,k) = f(j,k,N);
    if( M.has_nan() || M.has_inf() ){
        cout << "Matrix has NaN or Inf values!" << endl;
        exit(1);
    }
    return M;
}

complex<double> f(int j, int k, int N){
    // Increment j and k by 1 to avoid zero indexing
    j = j + 1;
    k = k + 1;
    cx_double result(0.0,0.0);
    double alphap1 = cos( j*j*k*PI / pow( N, 3) );
    double alphap2 = sin( 2*j*j*k*PI / pow( N, 3) );
    if( isnan(alphap1) || isnan(alphap2) || isinf(alphap1) || isinf(alphap2) ){
        cout << "Encountered NaN or Inf in alpha calculations for j=" << j << ", k=" << k << ", N=" << N << endl;
        exit(1);
    }
    double alpha = 1.0 / sqrt( alphap1*alphap1 + alphap2*alphap2 );
    if( isnan(alpha) || isinf(alpha) ){
        cout << "Encountered NaN or Inf in alpha calculation for j=" << j << ", k=" << k << ", N=" << N << endl;
        exit(1);
    }
    double result_realp1 = j*j*k*PI / pow( N, 3);
    if( isnan(result_realp1) || isinf(result_realp1) ){
        cout << "Encountered NaN or Inf in result real part calculation for j=" << j << ", k=" << k << ", N=" << N << endl;
        exit(1);
    }
    double result_imagp1 = 2*j*j*k*PI / pow( N, 3);
    if( isnan(result_imagp1) || isinf(result_imagp1) ){
        cout << "Encountered NaN or Inf in result imaginary part calculation for j=" << j << ", k=" << k << ", N=" << N << endl;
        exit(1);
    }
    double result_realp12 = cos( result_realp1 );
    double result_imagp12 = sin( result_imagp1 );
    if( isnan(result_realp12) || isnan(result_imagp12) || isinf(result_realp12) || isinf(result_imagp12) ){
        cout << "Encountered NaN or Inf in final result calculations for j=" << j << ", k=" << k << ", N=" << N << endl;
        exit(1);
    }
    return complex<double>(
        alpha * result_realp12,
        alpha * result_imagp12
    );
}