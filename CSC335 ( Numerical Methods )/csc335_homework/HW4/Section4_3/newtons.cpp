#include "newtons.h"

double trapezoid_rule( function<double(double)> f, double a, double b ){
    return (b - a) / 2 * ( f(a) + f(b) );
}

double trapezoid_error_bound( function<double(double)> f2, double a, double b ){
    double max_f2 = max( abs( f2(a) ), abs( f2(b) ) );
    return ( pow( b - a, 3) / 12 ) * max_f2;
}

double simpson( function<double(double)> f, double a, double b ){
    return (b - a) / 6 * ( f(a) + 4 * f( (a + b) / 2 ) + f(b) );
}

double simpson_error_bound( function<double(double)> f_4, double a, double b ){
    double max_f4 = max( abs( f_4(a) ), abs( f_4(b) ) );
    return ( pow( (b - a) / 2, 5) / 90 ) * max_f4;
}