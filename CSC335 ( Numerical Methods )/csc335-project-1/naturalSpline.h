#ifndef NATURAL_SPLINE_H
#define NATURAL_SPLINE_H

#include<vector>
#include<utility>
#include<iostream>
#include<cmath>
#include<functional>
#include<ostream>
#include<iomanip>
#include<numeric>
#include<algorithm>
using namespace std;

struct NaturalSplineCoefficients {
    double a;
    double b;
    double c;
    double d;
};
//Struct to hold the coefficients of a natural spline segment

vector<NaturalSplineCoefficients> naturalSplineCoeffs( vector< pair<double, double> > data );
/*
@param data: data points to generate the spline from
@return: vector of natural spline coefficients for each interval between data points

Generates the natural spline coefficients for the given data points.
*/

double splineEval( vector<NaturalSplineCoefficients> coeffs, vector< double > xVals, double x);
/*
@param coeffs: spline coefficients
@param xVals: x values corresponding to the data points used to generate the spline
@param x: the x value to evaluate the spline at

@return: the value of the spline at x

Evalutes the natural spline using the provided coefficients, x values, and the value to evaluate at.
coeffs and xVals must correspond to the same data set.
*/

double f0(double x);
double f1(double x);
double f2(double x);
double f3(double x);
double f4(double x);
double f5(double x);
double f6(double x);
/*
@param x: value to evaluate the function at

@return: the function value at x

These functions are simple mathematical f(x) functions meant to test the spline and are not utilized in the main program.
*/

#endif
