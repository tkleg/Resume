#include<functional>
#include<cmath>
#include<iostream>
#include<vector>
#include <iomanip>
using namespace std;

double composite_trapezoid_rule( function<double(double)> f, double a, double b, int n );
double composite_simpsons_rule( function<double(double)> f, double a, double b, int n );

struct integral_info{
    function<double(double)> f;
    double a;
    double b;
    int n;
    string desc;
};

int main(){
    vector<integral_info> integrals = {
        { [](double x){ return 2 / ( x * x + 4 ); }, 0, 2, 6, "2 / ( x^2 + 4 )" },
        { [](double x){ return tan(x); }, 0, 3 * acos(-1) / 8, 8, "tan(x)" }
    };
    cout << setprecision(10);
    cout << "Problem 1:" << endl;
    for( integral_info data : integrals )
        cout << "Composite Trapezoid's approximation of integral of " << data.desc << " from " << data.a << " to " << data.b << " is "
             << composite_trapezoid_rule( data.f, data.a, data.b, data.n ) << endl;
    cout << endl;

    cout << "Problem 3:" << endl;
    for( integral_info data : integrals )
        cout << "Composite Simpson's approximation of integral of " << data.desc << " from " << data.a << " to " << data.b << " is "
             << composite_simpsons_rule( data.f, data.a, data.b, data.n ) << endl;

    double m = 10;
    double v0 = 10, v_end = 5;
    function<double(double)> R = [](double x){ return -pow(x, 1.5); };
    cout << endl << "Problem 19:" << endl;
    cout << "Time to fall from " << v0 << " m/s to " << v_end << " m/s is "
         << - composite_simpsons_rule( [m, R](double x){ return m / R(x); }, v_end, v0, 20 ) << " seconds using Composite Simpson Rule" << endl;
    
    return 0;
}


double composite_trapezoid_rule( function<double(double)> f, double a, double b, int n ){
    double h = ( b - a ) / n;
    double sum = f(a) + f(b);
    for( int j = 1; j < n; j++ )
        sum += 2 * f( a + j * h );
    return h / 2 * sum;
}

double composite_simpsons_rule( function<double(double)> f, double a, double b, int n ){
    double h = ( b - a ) / n;
    double sum = f(a) + f(b);
    vector<double> xVals = { a, b };
    for( int j = 1; j <= n/2 - 1; j++ ){
       sum += 2 * f( a + (2 * j) * h );
    }
    for( int j = 1; j <= n/2; j++ ){
        sum += 4 * f( a + (2 * j - 1) * h );
    }
    
    return h / 3 * sum;
}