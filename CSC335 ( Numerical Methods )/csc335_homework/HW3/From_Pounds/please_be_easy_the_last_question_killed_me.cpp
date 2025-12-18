#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <iomanip>
#include <algorithm>
#include "naturalSpline.h"
#include "lagrange.h"
using namespace std;

vector< pair<long double, long double> > readDataFromFile();

void writeToFiles( vector< pair<long double, long double> > data, long double start, long double end );

bool comparePairs( pair<long double, long double> a, pair<long double, long double> b ){
    return a.first < b.first;
}

int main(){

    vector< pair<long double, long double> > data = readDataFromFile();

    sort( data.begin(), data.end(), comparePairs );

    writeToFiles( data, data.front().first, data.back().first );

    return 0;
}

void writeToFiles( vector< pair<long double, long double> > data, long double start, long double end ){
    vector<NaturalSplineCoefficients> splineCoeffs = naturalSplineCoeffs(data);

    vector<long double> xVals;
    for( pair<long double, long double> p : data )
        xVals.push_back( p.first );

    const long double step = 1e-3;
    ofstream lagrangeFile("lagrange.dat");
    ofstream splineFile("naturalSpline.dat");

    long double curPoint = start;

    while( curPoint <= end ){
        lagrangeFile << curPoint << " " << lagrange( data, curPoint ) << endl;
        splineFile << curPoint << " " << splineEval( splineCoeffs, xVals, curPoint ) << endl;
        curPoint += step;
    }

}

vector< pair<long double, long double> > readDataFromFile() {
    ifstream infile("interp_points.dat");
    vector<pair<long double, long double>> data;

    if (!infile) {
        cerr << "Error opening input file: " << "interp_points.dat" << endl;
        return data;
    }

    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        long double x, y;
        ss >> x >> y;
        data.push_back(make_pair(x, y));
    }

    infile.close();
    return data;
}