#ifndef COMMON_H
#define COMMON_H

#include<vector>
#include<functional>
#include<utility>
#include<fstream>
#include<iostream>
#include<tuple>
#include<cmath>
#include"naturalSpline.h"
using namespace std;

function<double(double)> splineFunction( vector<NaturalSplineCoefficients> coeffs, vector<double> xVals);
/*
    @param coeffs: coefficients of the natural spline
    @param xVals: x values corresponding to the coefficients

    @return: function representing the natural spline

    This function is used to allow passing 1 parameter to a function to evaluate the spline at any x in the domain.
    Without this you would need to pass both coeffs and xVals every time you wanted to evaluate the spline.
*/

vector< pair<double, double> > readDataFromFile(const string filename);
/*
    @param filename: name of file to read from

    Data should be two columns of whitespace seperated doubles with x in the first column.
*/

void writeDataToFile( vector< pair<double, double> > data, string filename );
/*
    @param data: data to write to file
    @param filename: name of file to write to (will be placed in writtenData/)

    Data should be two columns of whitespace seperated doubles with x in the first column.
*/

#endif