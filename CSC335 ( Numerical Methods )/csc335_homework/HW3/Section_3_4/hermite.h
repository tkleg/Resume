#include<vector>
#include<cmath>
#include<iostream>
using namespace std;

struct HermiteNode {
    long double x;
    long double fx;
    long double dfx;
};

//create table of coefficients for hermite interpolation
vector< vector<long double> > createHermiteData( vector<HermiteNode> data );

long double hermite( vector<long double> xVals, vector< vector<long double> > hermiteData, long double x );