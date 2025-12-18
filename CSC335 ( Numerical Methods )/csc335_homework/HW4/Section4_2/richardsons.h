#ifndef RICHARDSON_H
#define RICHARDSON_H

#include<vector>
#include<functional>
#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

double richardson( function<double(double)> f, double x, double h, int n, bool print_table = false );

#endif