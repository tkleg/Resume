#ifndef RUNGE_KUTTA_SYSTEMS_H
#define RUNGE_KUTTA_SYSTEMS_H

#include<functional>
#include<iostream>
#include<iomanip>
#include<vector>
#include<cmath>
#include<optional>
#include<algorithm>
#include<fstream>
using namespace std;

double runge_system_solver( double a, double b, vector< function<double( double, vector<double> )> > funcs,
    optional< vector< function<double(double)> > > actual_funcs, vector<double> y0, optional<int> N,
    optional<double> h, optional<string> data_filename, bool print_all=false );

vector<double> vector_sum(vector<double> v1, vector<double> v2);

#endif