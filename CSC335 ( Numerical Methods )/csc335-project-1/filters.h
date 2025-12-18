#ifndef FILTERS_H
#define FILTERS_H

#include<sstream>
#include<vector>
#include<iostream>
#include<fstream>
using namespace std;

struct SavitzkyGolayData {
    int windowSize;
    int norm;
    vector<int> coefficients;
};

SavitzkyGolayData getSavitzkyGolayData(int windowSize);
/*
    @param windowSize: size of the Savitzky-Golay window (must be odd)

    @return: struct containing window size, normalization factor, and coefficients
*/

vector< pair<double, double> > savGolFilter( vector< pair<double, double> > data, int windowSize, int numPasses );
/*
    @param data: data points to be smoothed
    @param windowSize: size of the Savitzky-Golay window
    @param numPasses: number of times to apply the filter

    @return: smoothed data points
*/

vector< pair<double, double> > boxCarFilter( vector< pair<double, double> > data, int windowSize, int numPasses );
/*
    @param data: data points to be smoothed
    @param windowSize: size of the boxcar window
    @param numPasses: number of times to apply the filter

    @return: smoothed data points
*/

#endif