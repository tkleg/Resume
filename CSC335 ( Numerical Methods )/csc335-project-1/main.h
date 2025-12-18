#include<fstream>
#include<iostream>
#include<vector>
#include<utility>
#include<sstream>
#include<algorithm>
#include<functional>
#include<iomanip>
#include<optional>
#include<chrono>
#include"filters.h"
#include"naturalSpline.h"
#include"manifoldFinder.h"
#include"input_processor.h"
#include"common.h"
#include"integrals.h"
#include"peak_and_shift.h"
#include"dft.h"
#include"dualStream.h"

struct PeakData{
    int index;
    double begin;
    double end;
    double loc;
    double top;
    double area;
    int hydrogenCount;
};

void printResults( vector<PeakData> peaks, DualStream& out, InputParams params, double shift_amount );
/*
    Prints a formatted summary of the NMR analysis results to the provided output file stream.
*/

void writeAll( FilterType filter_type, int filter_window_size, vector< pair<double, double> > shiftedData,
    vector< pair<double, double> > filteredData, vector< pair<double, double> > splineData, ofstream& outfile );
/*
    @param data: original data
    @param params: input parameters
    @param outfile: output file stream

    Applies the specified filter to the NMR data and returns the filtered data.
*/

vector< pair<double, double> > filterData( vector< pair<double, double> > data, InputParams params, ofstream& outfile );
/*
    @param data: data points
    @param params: input parameters
    @param outfile: output file stream
    @return: filtered data points

    Filters the data, or not, based on the input parameters and identifies peaks.
*/


vector<PeakData> getPeaks( function<double(double)> splineFunc, vector< pair<double, double> > integralBounds, InputParams params );
/*
    @param splineFunc: spline function representing the data
    @param integralBounds: bounds for integration
    @param params: input parameters
    @return: vector of PeakData structs containing peak information

    Gets the PeakData structs that will be used for output.
*/