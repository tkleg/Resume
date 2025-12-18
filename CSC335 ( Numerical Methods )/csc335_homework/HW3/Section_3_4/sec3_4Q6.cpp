#include<iostream>
#include<vector>
#include<utility>
#include<cmath>
#include<iomanip>
#include<functional>
#include"hermite.h"
using namespace std;

long double f( long double x );

long double df( long double x );

long double errorTerm( function<long double(long double)> func, vector<long double> xVals, long double x, long double e );

//long double hermite( vector< pair<long double, long double> > data, long double x );

long double nthDerivative( long double x, int n );


int main() {

    vector< HermiteNode > data;
    vector<long double> xVals = { 1, 1.05 };

    for( long double x : xVals ) {
        HermiteNode node;
        node.x = x;
        node.fx = f(x);
        node.dfx = df(x);
        data.push_back( node );
    }


    for( int count = 0; count <= 1; count++ ){
        cout << "Using these x values: ";
        for( long double x : xVals )
            cout << x << ", ";
        cout << endl;
        cout << fixed << setprecision(15);
        vector< vector<long double> > hermiteData = createHermiteData( data );
        long double hermiteVal = hermite( xVals, hermiteData, 1.03 );
        long double actual = f(1.03);
        cout << "Hermite interpolation at x = 1.03: " 
            << hermiteVal << endl;
        cout << "Actual value at x = 1.03: " 
            << actual << endl;
        cout.unsetf( ios::fixed | ios::scientific);
        cout << "Absolute error: " 
            << abs( hermiteVal - actual ) << endl;
        cout << "Relative error: " 
            << abs( hermiteVal - actual ) / actual << endl;

        long double minErr = errorTerm( f, xVals, 1.03, 0 );
        long double minErrX = 0;
        long double maxErr = minErr;
        long double maxErrX = 0;
        long double errX = 0;
        for( int steps = 0; steps <= 1030000; steps++ ){
            if( errX > 1.03 )
                errX = 1.03;
            long double err = errorTerm( f, xVals, 1.03, errX );
            if( err < minErr ){
                minErr = err;
                minErrX = errX;
            }
            if( err > maxErr ){
                maxErr = err;
                maxErrX = errX;
            }
            errX += 1e-6;
        }
        cout << "Minimum error term: " << minErr << " at x = " << minErrX << endl;
        cout << "Maximum error term: " << maxErr << " at x = " << maxErrX << endl;
        cout << endl << endl;

        data.push_back( HermiteNode{ 
            1.07, f(1.07), df(1.07) } );
        xVals.push_back( 1.07 );
    }
    //Check that data was created correctly
    //for( HermiteNode n : data )
    //    cout << "x: " << n.x << " f(x): " << n.fx << " f'(x): " << n.dfx << endl;
/*
    cout << "Hermite interpolation at x = 1.03: " 
        << hermite( data, 1.03 ) << endl;
    cout << "Actual value at x = 1.03: " 
        << f(1.03) << endl;
    cout << "Absolute error: " 
        << abs( hermite( data, 1.03 ) - f(1.03) ) << endl;
    cout << "Relative error: " 
        << abs( hermite( data, 1.03 ) - f(1.03) ) / f(1.03) << endl;
*/    
    return 0;
}

long double nth_derivative(long double x, int n) {
    return 3 * (x + n) * exp(x) - pow(2.0, n) * exp(2 * x);
}

long double errorTerm( function<long double(long double)> func, vector<long double> xVals, long double x, long double errX ){
    long double product = 1;
    for( long double val : xVals )
        product *= pow( x - val, 2 );
    int factorial = 1;
    for( int i = 2 * (xVals.size()-1) + 2; i > 1; i-- )
        factorial *= i;
    return product / factorial * nth_derivative( errX, 2 * (xVals.size()-1) + 2 );
}

/*long double hermite( vector< pair<long double, long double> > data, long double x ){

    vector<long double> xVals;
    for( pair<long double, long double> p : data )
        xVals.push_back( p.first );

    long double sum = 0;
    for( int j = 0; j < data.size(); j++ ){
        long double term1 = data[j].second;
        term1 *= 1 - 2 * ( x - data[j].first );
        term1 *= lFunctionDerivative( xVals, data[j].first, j );
        term1 *= pow( lFunction( xVals, x, j), 2 );
        sum += term1;
    }

    for( int j = 0; j < data.size(); j++ )
        sum += ( x - data[j].first ) * pow (lFunction( xVals, x, j ), 2 );

    return sum;
}*/

long double f( long double x ){
    return 3 * x * exp( x ) - exp( 2 * x );
}

long double df( long double x ){
    return 3 * exp( x ) + 3 * x * exp( x ) - 2 * exp( 2 * x );
}