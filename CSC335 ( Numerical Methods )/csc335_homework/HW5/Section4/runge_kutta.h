#include<iostream>
#include<iomanip>
#include<functional>
#include<optional>
#include<fstream>
using namespace std;

double runge_kutta_4th_order(function<double(double, double)> f, double y0, double x0,
    double x_end, optional<int> N, optional<double> h, optional<string> data_filename, bool print_all=false, double function_constants = 1 );