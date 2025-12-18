#ifndef GAUSSIANELIM_H
#define GAUSSIANELIM_H

#include<vector>
#include<iomanip>
#include<iostream>
#include<algorithm>
#include "roundingCalc.h"
using namespace std;

typedef vector< vector<double> > DoubleMatrix;
typedef vector< vector<float> > FloatMatrix;

vector<double> gaussianElimPartialPivot( DoubleMatrix augmentedMatrix, bool scaled = false, bool printAfterElim = false, 
    RoundingMode mode = NONE, int precision = -1 );

DoubleMatrix gaussianElim( DoubleMatrix augmentedMatrix, bool enableSwaps = true, bool printAfterElim = false, 
    RoundingMode mode = NONE, int precision = -1 );

vector<float> gaussianElim( FloatMatrix augmentedMatrix, bool enableSwaps = true, bool printAfterElim = false, 
    RoundingMode mode = NONE, int precision = -1 );

vector<double> vector_sum(vector<double> v1, vector<double> v2, RoundingMode mode = NONE, int precision = -1 );

vector<float> vector_sum(vector<float> v1, vector<float> v2, RoundingMode mode = NONE, int precision = -1 );

void printMatrix( DoubleMatrix matrix );

void printMatrix( FloatMatrix matrix );

#endif // GAUSSIANELIM_H