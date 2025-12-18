#include<vector>
#include<utility>
#include<iostream>
using namespace std;

struct NaturalSplineCoefficients {
    long double a;
    long double b;
    long double c;
    long double d;
};

vector<NaturalSplineCoefficients> naturalSplineCoeffs( vector< pair<long double, long double> > data );

long double splineDerivativeEval( vector<NaturalSplineCoefficients> coeffs, vector< long double > xVals, long double x);

long double splineEval( vector<NaturalSplineCoefficients> coeffs, vector< long double > xVals, long double x);