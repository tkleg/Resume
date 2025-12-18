#ifndef  EULERS_H
#define  EULERS_H

#include<iostream>
#include<functional>
#include<iomanip>
#include<optional>
#include<cmath>
#include<fstream>
using namespace std;

double eulers_method(function<double(double, double)> f, double y0, double x0, 
    optional<double> x_start, optional<double> x_end, optional<int> N, 
    optional<double> h, optional< function<double(double)> > real, 
    bool print_all, string filename = "" );

#endif