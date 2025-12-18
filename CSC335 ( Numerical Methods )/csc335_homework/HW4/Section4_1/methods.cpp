#include "methods.h"

double three_pt_endpoint( function<double(double)> f, double x0, double h ){
    return ( -3.0 * f(x0) + 4.0 * f(x0+h) - f(x0+2*h) ) / (2.0 * h);
}

double three_pt_midpoint( function<double(double)> f, double x0, double h ){
    return ( f(x0+h) - f(x0-h) ) / (2.0 * h);
}

double five_pt_endpoint( function<double(double)> f, double x0, double h, bool print_debug ){
    if(print_debug)
        printf("(%f,%f), (%f,%f), (%f,%f), (%f,%f), (%f,%f)\n", x0, f(x0), x0+h, f(x0+h), x0+2*h, f(x0+2*h), x0+3*h, f(x0+3*h), x0+4*h, f(x0+4*h));
    return ( -25.0 * f(x0) + 48.0 * f(x0+h) - 36.0 * f(x0+2*h) + 16.0 * f(x0+3*h) - 3.0 * f(x0+4*h) ) / (12.0 * h);
}

double five_pt_midpoint( function<double(double)> f, double x0, double h, bool print_debug ){
    if(print_debug)
        printf("(%f,%f), (%f,%f), (%f,%f), (%f,%f)\n", x0-2*h, f(x0-2*h), x0-h, f(x0-h), x0+h, f(x0+h), x0+2*h, f(x0+2*h));
    return ( f(x0-2*h) - 8.0 * f(x0-h) + 8.0 * f(x0+h) - f(x0+2*h) ) / (12.0 * h);
}