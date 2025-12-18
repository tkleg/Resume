#include<iostream>
#include<iomanip>
#include<cmath>
#include "newtons.h"

struct integral_info{
    function<double(double)> f;
    function<double(double)> f_err;
    double a;
    double b;
    string function_def_str;
};

#ifdef Q_ALL
int main(){
    vector<integral_info> integrals = {
        { [](double x){ return x * x * log(x); }, [](double x){ return 2 * log(x) + 3; }, 1, 1.5, "x^2 * ln(x)"},
        { [](double x){ return exp( 3 * x ) * sin( 2 * x ); },
            [](double x){ return exp( 3 * x ) * (5 * sin( 2 * x ) + 12 * cos( 2 * x ) ); },
            0, acos(-1) / 4, "e^(3x) * sin(2x)" }
    };

    cout << "Problems 1 and 3: Using Trapezoid Rule" << endl;
    for( integral_info data : integrals ){
        double estimate = trapezoid_rule( data.f, data.a, data.b );
        double estimate_error = trapezoid_error_bound( data.f_err, data.a, data.b );
        cout << "Approximation of " << data.function_def_str << " from " << data.a << " to " << data.b << " is "
             << estimate << " with error bound "
             << estimate_error << endl;
    }
             


    integrals[0].f_err = [](double x){ return -2 / (x*x); };
    integrals[1].f_err = [](double x){ return - exp( 3 * x ) * (119 * sin( 2 * x ) - 120 * cos( 2 * x ) ); };

    cout << endl << "Problems 5 and 7: Using Simpson's Rule" << endl;
    for( integral_info data : integrals ){
        double estimate = simpson( data.f, data.a, data.b );
        double estimate_error = simpson_error_bound( data.f_err, data.a, data.b );
        cout << "Approximation of " << data.function_def_str << " from " << data.a << " to " << data.b << " is "
             << estimate << " with error bound "
             << estimate_error << endl;
    }
    return 0;
}
#endif