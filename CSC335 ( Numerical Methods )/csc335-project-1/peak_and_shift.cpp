#include "peak_and_shift.h"

vector< pair<double, double> > shiftDataHorizontal( vector< pair<double, double> > data, double shiftAmount ){
    for( int x = 0; x < data.size(); x++ )
        data[x].first -= shiftAmount;
    return data;
}

vector< pair<double, double> > shiftDataVertical( vector< pair<double, double> > data, double shiftAmount ){
    for( int x = 0; x < data.size(); x++ )
        data[x].second -= shiftAmount;
    return data;
}

optional< pair<double, double> > getPeak(vector< pair<double, double> > data, double baseline){
    bool baselinePassed = false;
    pair<double, double> maxPoint;
    //Note: Assumes data is sorted by x value in ascending order
    for( int x = data.size() - 1; x >= 0; x-- ){
        //Looking for the first point above the baseline
        if( !baselinePassed && data[x].second > baseline ){
            baselinePassed = true;
            maxPoint = data[x];
            continue;
        }

        //Looking for the first point after the original first point above the baseline that is below the original first point
        if( baselinePassed ){
            if( data[x].second >= maxPoint.second )
                maxPoint = data[x];
            else
                return maxPoint;
        }
    }
    return nullopt; 
}