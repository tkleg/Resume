#include "lagrange.h"

long double lagrange( vector< pair<long double, long double> > data, long double x ){
    long double sum = 0;
    vector<long double> xVals;
    for( pair<long double, long double> p : data )
        xVals.push_back( p.first );
    
    for( int k = 0; k < data.size(); k++ )
        sum += data[k].second * lFunction( xVals, x, k );

    return sum;
}

long double lFunction( vector<long double> vals, long double x, int k ){
    long double product = 1;
    for( int i = 0; i < vals.size(); i++ ){
        if( i == k )
            continue;
        product *= ( x - vals[i] ) / ( vals[k] - vals[i] );
    }
    return product;
}

long double lFunctionDerivative( vector<long double> vals, long double x, int k ){
    long double sum =  0;
    for(int j = 0; j < vals.size(); j++ )
        sum += 1.0 / ( x - vals[j] );
    return lFunction(vals, x, k) * sum;
}