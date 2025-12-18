#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include <functional>
#include <cmath>
using namespace std;

double trapezoid_rule( function<double(double)> f, double a, double b );

double trapezoid_error_bound( function<double(double)> f2, double a, double b );

double simpson( function<double(double)> f, double a, double b );

double simpson_error_bound( function<double(double)> f_4, double a, double b );

#endif