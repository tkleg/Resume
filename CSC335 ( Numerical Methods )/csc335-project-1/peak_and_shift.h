#include<vector>
#include<utility>
#include<optional>
using namespace std;


vector< pair<double, double> > shiftDataHorizontal( vector< pair<double, double> > data, double shiftAmount );
/*
@param data: vector of (x,y) pairs representing the data to be shifted
@param shiftAmount: amount to shift the x-values by

@returns: shifted data

Returns a copy of data with every x-value having shiftAmount subtracted from it.
*/

vector< pair<double, double> > shiftDataVertical( vector< pair<double, double> > data, double shiftAmount );
/*
@param data: vector of (x,y) pairs representing the data to be shifted
@param shiftAmount: amount to shift the y-values by

@returns: shifted data

Returns a copy of data with every y-value having shiftAmount subtracted from it.
*/

optional< pair<double, double> > getPeak(vector< pair<double, double> > data, double baseline);
/*
@param data: vector of (x,y) pairs representing the data to search for a peak
@param baseline: minimum y-value for a peak to be considered valid

@returns: optional pair<double, double> representing the (x,y) coordinates of the peak

Data must be in ascending order of x-values.
Returns nullopt if no peak is found above the baseline.
Otherwise, returns a pair<double, double> representing the (x,y) coordinates of the peak.
Process for finding the peak:
    1. Find the first coordinate where y > baseline.
    2. From that coordinate, continue until y starts to decrease. The last coordinate before the decrease is the peak.
*/