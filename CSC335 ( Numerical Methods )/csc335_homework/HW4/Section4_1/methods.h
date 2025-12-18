#ifndef METHODS_H
#define METHODS_H

#include <functional>
#include <iostream>
using namespace std;

double five_pt_endpoint( function<double(double)> f, double a, double h, bool print_debug = false );

double five_pt_midpoint( function<double(double)> f, double x0, double h, bool print_debug = false );

double three_pt_endpoint( function<double(double)> f, double x0, double h );

double three_pt_midpoint( function<double(double)> f, double x0, double h );

#endif