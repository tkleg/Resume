#include<iostream>
#include<iomanip>
#include<functional>
#include<cmath>
#include<vector>
using namespace std;

struct roots_coeffs{
    double root;
    double coeff;
};

struct integral{
    double a;
    double b;
    function<double(double)> f;
    string message;
};

double gaussian_legendre_quadrature_n2( function<double(double)> f, double a, double b );

double gaussian_legendre_quadrature_n5( function<double(double)> f, double a, double b );

int main(){

    function<double(double)> a = [](double x){ return x*x*log(x); };
    integral partA = {1.0, 1.5, a, "Problem 1a"};

    function<double(double)> d = [](double x){ return x*x*sin(x); };
    integral partD = {0.0, M_PI/4.0, d, "Problem 1d"};

    
    cout << setprecision(10);
    vector<integral> integrals = {partA, partD};
    for( integral in : integrals ){
        double result = gaussian_legendre_quadrature_n2( in.f, in.a, in.b );
        cout << in.message << ": " << result << endl;
    }

    integrals[0].message = "Problem 7a";
    integrals[1].message = "Problem 7d";
    for( integral in : integrals ){
        double result = gaussian_legendre_quadrature_n5( in.f, in.a, in.b );
        cout << in.message << ": " << result << endl;
    }
    return 0;
}

double gaussian_legendre_quadrature_n2( function<double(double)> f, double a, double b ){
    vector<roots_coeffs> coeffs_n2 = {
        {-5.773502691896257e-1, 9.999999999999996e-1},
        {5.773502691896257e-1, 9.999999999999996e-1}
    };

    double integral = 0.0;
    for( roots_coeffs rc : coeffs_n2 )
        integral += rc.coeff * f( ( (b - a) * rc.root + a + b ) / 2 ) * (b - a) / 2;

    return integral;
}

double gaussian_legendre_quadrature_n5( function<double(double)> f, double a, double b ){
    vector<roots_coeffs> coeffs_n5 = {
        {0.0000000000000000, 0.5688888888888889},
        {-0.5384693101056831, 0.4786286704993665},
        {0.5384693101056831, 0.4786286704993665},
        {-0.9061798459386640, 0.2369268850561891},
        {0.9061798459386640, 0.2369268850561891}
    };

    double integral = 0.0;
    for( roots_coeffs rc : coeffs_n5 )
        integral += rc.coeff * f( ( (b - a) * rc.root + a + b ) / 2 ) * (b - a) / 2;

    return integral;
}