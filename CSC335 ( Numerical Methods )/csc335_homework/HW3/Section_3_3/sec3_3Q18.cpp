#include"dividedDifferences.h"
#include<iostream>
#include<vector>
#include<utility>
using namespace std;

int main() {
    vector< pair<double, double> > data = { {1.25, 119.4}, {0.25, 25.2},
        {0.5, 49.5}, {1, 96.4}};

    vector<double> coeffs = dividedDifferencesCoefficients(data);
    cout << "Divided differences coefficients: " << endl;
    for( double val : coeffs )
        cout << val << " ";
    cout << endl << endl;
    vector<double> xVals;
    for( pair<double, double> p : data )
        xVals.push_back( p.first );

    double actualTime = 73;
    double estimatedTime = dividedDifferences(coeffs, xVals, 0.75);
    cout << "Predicted time at 3/4 mile: " 
        << estimatedTime << " seconds" << endl;
    cout << "Absolute error: " 
        << abs( estimatedTime - actualTime ) 
        << " seconds" << endl;
    cout << "Relative error: " 
        << abs( estimatedTime - actualTime ) / actualTime 
        << endl;
    cout << endl;

    double diff = 1e-6;
    double predictedSecondsPerMile = 
        ( dividedDifferences(coeffs, xVals, 1.25 + diff) - 
          dividedDifferences(coeffs, xVals, 1.25 ) ) / diff;
    double predictedSpeed = 1 / predictedSecondsPerMile;
    cout << "Predicted speed at end of race (1.25 miles): " 
        << predictedSpeed * 3600 << " mph" << endl;
    return 0;
}