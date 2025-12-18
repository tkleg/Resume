#ifndef MANIFOLD_FINDER_H
#define MANIFOLD_FINDER_H

#include<vector>
#include<utility>
#include <iostream>
#include <fstream>
#include<functional>
#include"naturalSpline.h"
using namespace std;

vector< pair< pair< double, double >, pair<double, double> > > getCrossingBounds( function<double(double)> splineFunc, double tol, pair<double, double> domainBounds );
/*
@param splineFunc: function representing the spline
@param tol: tolerance for crossing detection
@param domainBounds: the bounds of the domain to search for crossings of y=0

Finds all pairs of points (x1, y1) and (x2, y2) that cross the baseline
*/


double bisection( function<double(double)> f, double a, double b, double tol, int maxIter );
/*
@param f: function for which to find the root
@param a: left bound of the interval
@param b: right bound of the interval
@param tol: tolerance for stopping
@param maxIter: maximum number of iterations

@return: approximate root of f within [a, b]
*/

vector<pair<double, double>> getIntegralBounds( function<double(double)> splineFunc, double tol, pair<double, double> domainBounds );
/*
@param splineFunc: function representing the spline
@param tol: tolerance for bisection method and crossing detection
@param domainBounds: the bounds of the domain to search for crossings of y=0

@return: pairs of points which straddle y=0

It is y=0 and not y=baseline since the function is shifted vertically before making the spline.
*/

#endif