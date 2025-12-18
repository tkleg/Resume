#ifndef INTEGRALS_H
#define INTEGRALS_H

#include<iostream>
#include<cmath>
#include<functional>
#include<utility>
#include<algorithm>
#include<fstream>
#include<iomanip>
#include"common.h"
#include"naturalSpline.h"
using namespace std;

const double epsilon = 1e-7;
const int epsilon_multiplier = 6;
extern int newton_cotes_n;
extern int romberg_n;

double gauss_legendre_64pt( function<double(double)> f, double a, double b );
/*
    @param f: function to integrate
    @param a: lower limit of integration
    @param b: upper limit of integration

    @return: approximate value of the integral from a to b using 64-point Gauss-Legendre quadrature
*/

vector< vector<double> > romberg_extrapolation( function<double(double)> f, double a, double b, int n, bool printTable=false );
/*
    @param f: function to integrate
    @param a: lower limit of integration
    @param b: upper limit of integration
    @param n: number of Romberg levels
    @param printTable: whether to print the Romberg table

    @return: Romberg table as a 2D vector with integrals approximations on the diagonal
*/

double tolerant_romberg_extrapolation( function<double(double)> f, double a, double b, double tolerance );
/*
    @param f: function to integrate
    @param a: lower limit of integration
    @param b: upper limit of integration
    @param tolerance: tolerance for the approximation

    @return: approximate value of the integral from a to b using Romberg extrapolation within the specified tolerance

    Works by iteratively enlarging the Romberg table until the change in the integral approximation is within the specified tolerance.
*/

double simpson_rule_third( function<double(double)> f, double a, double b );
/*
    @param f: function to integrate
    @param a: lower limit of integration
    @param b: upper limit of integration

    @return: approximate value of the integral from a to b using Simpson's rule
*/

double tolerant_composite_simpsons_rule( function<double(double)> f, double a, double b, double tol, int maxIterations = 200 );
/*
    @param f: function to integrate
    @param a: lower limit of integration
    @param b: upper limit of integration
    @param tol: tolerance for the approximation
    @param maxIterations: maximum number of iterations to prevent infinite loops

    @return: approximate value of the integral from a to b using composite trapezoid rule within the specified tolerance

    Works by iteratively increasing the number of subintervals until the change in the integral approximation is within the specified tolerance or the maximum number of iterations is reached.
*/

double composite_simpsons_rule( function<double(double)> f, double a, double b, int n );
/*
    @param f: function to integrate
    @param a: lower limit of integration
    @param b: upper limit of integration
    @param n: number of subintervals (must be even and >= 2)

    @return: approximate value of the integral from a to b using composite Simpson's rule
*/

double adaptive_quadrature( function<double(double)> f, double a, double b, double tol );
/*
    @param f: function to integrate
    @param a: lower limit of integration
    @param b: upper limit of integration
    @param tol: tolerance for adaptive quadrature
    @param depth: current recursion depth (default is 0)

    @return: approximate value of the integral from a to b

    Uses adaptive quadrature to approximate the integral of f from a to b within the specified tolerance.
*/

double f1_integrals(double x);
double f2_integrals(double x);
double f3_integrals(double x);
/*
    @param x: the x value to evaluate the function at
    @return: the function value at x

    These functions are simple mathematical f(x) functions meant to test the integrals and are not utilized in the main program.
*/

#endif