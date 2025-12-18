#include<iostream>
#include<armadillo>
#include<iomanip>
#include<vector>
#include<fstream>
using namespace std;
using namespace arma;

vec least_squares_polynomial( vec x, vec y, int degree );

int main(){
    vec x = {1, 1.1, 1.3, 1.5, 1.9, 2.1};
    vec y = {1.84, 1.96, 2.21, 2.45, 2.94, 3.18};
    cout << fixed << setprecision(7);
    vector<vec> coeffs_list;
    for( int degree : {1, 2, 3} ){
        vec coeffs = least_squares_polynomial( x, y, degree );
        coeffs_list.push_back( coeffs );
        vector<double> coeffs_vec( coeffs.begin(), coeffs.end() );
        cout << "Degree " << degree << " polynomial coefficients (constant term first):\n";
        for( double c : coeffs_vec )
            cout << "    " << c << endl;
        double error = 0;
        for( int i = 0; i < x.n_elem; i++ ){
            double poly_val = 0.0;
            for( int j = 0; j < coeffs.n_elem; j++ )
                poly_val += coeffs(j) * pow(x(i), j);
            error += pow( y(i) - poly_val, 2 );
        }
        cout << scientific << setprecision(3);
        cout << "Least squares error: " << error << endl;
        cout << endl;
        cout << fixed << setprecision(7);
    }

    ofstream outfile("Q3_points.dat");
    for( int i = 0; i < x.n_elem; i++ )
        outfile << x(i) << " " << y(i) << endl;
    outfile.close();

    ofstream polyfile("Q3_polynomials.dat");
    double start = x.min()-0.1, end = x.max()+0.1, step = 1e-4;
    for( double cur = start; cur <= end; cur += step ){
        polyfile << cur << " ";
        for( vec coeffs : coeffs_list ){
            double poly_val = 0.0;
            for( int j = 0; j < coeffs.n_elem; j++ )
                poly_val += coeffs(j) * pow(cur, j);
            polyfile << poly_val << " ";
        }
        polyfile << endl;
    }
    polyfile.close();

    return 0;
}

vec least_squares_polynomial( vec x, vec y, int degree ){
    int n = x.n_elem;
    mat A(degree+1, degree+1);
    vec c = zeros<vec>(degree+1);
    //Compute sums of powers of x
    vec x_sums(2*degree + 1);
    for(int k=1; k<=2*degree+1; k++)
        x_sums(k-1) = accu( pow(x, k) );
    vec xy_sums(degree+1);
    //% does element-wise multiplication of x and y
    for(int k=0; k<=degree; k++)
        xy_sums(k) = dot( y, pow(x, k) );

    //Fill matrix A
    A(0,0) = n;
    for( int i = 0; i <= degree; i++ )
        for( int j = 0; j <= degree; j++ ){
            if( i == 0 && j == 0 )
                continue;
            A(i, j) = x_sums(i+j-1);    
        }

    return solve(A, xy_sums);
}