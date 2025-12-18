#include<iostream>
#include<cmath>
#include<functional>
#include<vector>
#include<iomanip>
using namespace std;

struct romberg_return{
    double value;
    int n;
};

double romberg_extrapolation( function<double(double)> f, double a, double b, int n );
romberg_return romberg_extrapolation_limits( function<double(double)> f, double a, double b, int n_limit, double tolerance, bool tolerance_only );

struct integral_info{
    function<double(double)> f;
    double a, b;
    string desc;
    double actual_value;
};

int main(){

    vector<integral_info> integrals = {
        {[](double x){ return 2 / ( x * x - 4 ); }, 0, 0.35, "2 / ( x^2 - 4 )", -0.176820020122},
        {[](double x){ return exp( 3 * x ) * sin( 2 * x ); }, 0, acos(-1)/4, "exp(3x) * sin(2x)", 2.58862863251}
    };

    cout << setprecision(10);

    cout << "Problem 1:" << endl;
    for( integral_info integral : integrals )
        cout << "R_3,3 approximation of integral of " << integral.desc << " from " << integral.a << " to " << integral.b << " is "
            << romberg_extrapolation( integral.f, integral.a, integral.b, 3 ) << endl;

    cout << endl << "Problem 5:" << endl;
    for( integral_info integral : integrals ){
        cout << "R_n,n approximation of integral of " << integral.desc << " from " << integral.a << " to " << integral.b 
            << " with tolerance 1e-6 and n limit 10 is ";
        romberg_return romberg_results = romberg_extrapolation_limits( integral.f, integral.a, integral.b, 99999, 1e-6 , false);
        cout << romberg_results.value << " with n = " << romberg_results.n << endl;
        cout << "Actual value is " << integral.actual_value << endl;
        cout << "Absolute Error is " << abs( romberg_results.value - integral.actual_value ) << endl;
        cout << "Relative error is " << abs( romberg_results.value - integral.actual_value ) / abs(integral.actual_value) << endl << endl;
    }
    c

    cout << setprecision(15);
    //Estimating error function at x = 1
    cout << "Problem 14:" << endl;
    function<double(double)> f = [](double x){ return exp( -x*x ); };
    double erf_1 = 2 / sqrt(acos(-1)) * romberg_extrapolation_limits( f, 0, 1, 9999, 1e-7, true).value;
    cout << "Estimated erf(1) = " << erf_1 << endl;
    cout << "Actual erf(1) = " << erf(1) << endl;
    cout << "Absolute Error = " << abs( erf_1 - erf(1) ) << endl;
    cout << "Relative error = " << abs( erf_1 - erf(1) ) / abs( erf(1) ) << endl;

    return 0;
}

double romberg_extrapolation( function<double(double)> f, double a, double b, int n ){
    vector< vector<double> > R( n + 1, vector<double>(n + 1, 0.0) );
    
    double h = b - a;
    R[1][1] = h / 2.0 * ( f(a) + f(b) );
    
    for( int i = 2; i <= n; i++ ){
        double sum = 0.0;
        for( int k = 1; k <= (int) pow(2, i-2); k++)
            sum += f( a + (k - 0.5) * h );
        
        R[i][1] = ( R[i-1][1] + h * sum ) / 2.0;

        for( int j = 2; j <= i; j++ )
            R[i][j] = R[i][j-1] + ( R[i][j-1] - R[i-1][j-1] ) / ( pow(4, j-1) - 1 );

        h = h / 2.0;
    }
    
    return R.back().back();
}

romberg_return romberg_extrapolation_limits( function<double(double)> f, double a, double b, int n_limit, double tolerance, bool tolerance_only ){
    vector< vector<double> > R( n_limit + 1, vector<double>(n_limit + 1, 0.0) );
    
    double h = b - a;
    R[1][1] = h / 2.0 * ( f(a) + f(b) );
    
    int i = 2;
    for( i = 2; i <= n_limit || tolerance_only; i++ ){
        if( i > n_limit )
            R.push_back( vector<double>(n_limit + 1, 0.0) );

        double sum = 0.0;
        for( int k = 1; k <= (int) pow(2, i-2); k++)
            sum += f( a + (k - 0.5) * h );
        
        R[i][1] = ( R[i-1][1] + h * sum ) / 2.0;

        for( int j = 2; j <= i; j++ )
            R[i][j] = R[i][j-1] + ( R[i][j-1] - R[i-1][j-1] ) / ( pow(4, j-1) - 1 );

        h = h / 2.0;
        if( abs( R[i][i] - R[i-1][i-1] ) < tolerance )
            return {R[i][i], i};
    }

    return {R[n_limit][n_limit], n_limit};
}