#include<vector>
#include<utility>
#include<iostream>
#include"naturalSpline.h"
#include<iomanip>
#include<fstream>
#include<cmath>
using namespace std;

void writeData( vector<NaturalSplineCoefficients> coeffs, vector<long double> xVals, long double start, long double end, string filename );

void processSample( vector< pair<long double, long double> > data, int numSample );

long double bisectionMethod( vector<NaturalSplineCoefficients> coeffs, vector<long double> xVals, long double a0, long double b0, long double tol, int maxIter );

int main(){
    vector< pair<long double, long double> > sample1Data = {
        {0, 6.67}, {6, 17.33},
        {10, 42.67}, {13, 37.33},
        {17, 30.10}, {20, 29.31},
        {28, 28.74}
    };

    vector< pair<long double, long double> > sample2Data = {
        {0, 6.67}, {6, 16.11},
        {10, 18.89}, {13, 15.00},
        {17, 10.56}, {20, 9.44},
        {28, 8.89}
    };

    processSample( sample1Data, 1 );
    processSample( sample2Data, 2 );
    return 0;
}

void processSample( vector< pair<long double, long double> > data, int numSample ){
    vector<long double> xVals;
    for( pair<long double, long double> p : data )
        xVals.push_back( p.first );

    cout << "Sample " << numSample << " process: " << endl;
    vector<NaturalSplineCoefficients> coeffs = naturalSplineCoeffs( data );
    cout << setw(3) << "x_i" << setw(8) << "a_i" << setw(12) << "b_i" << setw(14) << "c_i" << setw(14) << "d_i" << endl;
    for( int x = 0; x < coeffs.size(); x++ )
        cout << setw(3) << data[x].first << setw(8) << coeffs[x].a << setw(12) << coeffs[x].b << setw(15) << coeffs[x].c << setw(15) << coeffs[x].d << endl;

    writeData( coeffs, xVals, 0, 28, "q25Sample" + to_string(numSample) );

    //I plotted the data in gnuplot to see approximate maxes to pick my 'a' and 'b' values for bisection
    //They were both clearly between 9 and 11 so the bounds are the same for both samples
    double maxDay = bisectionMethod( coeffs, xVals, 9, 11, 1e-10, 1000 );
    cout << "Max of Sample " << numSample << " at x = " << maxDay << endl;
    cout << "Average weight of Sample " << numSample << " on exact moment of max day " << maxDay << " is " << splineEval( coeffs, xVals, maxDay ) << endl;
    cout << "Average weight of Sample " << numSample << " on day " << floor(maxDay) << " is " << splineEval( coeffs, xVals, floor(maxDay) ) << endl;
    cout << "Average weight of Sample " << numSample << " on day " << ceil(maxDay) << " is " << splineEval( coeffs, xVals, ceil(maxDay) ) << endl << endl;

}

long double bisectionMethod( vector<NaturalSplineCoefficients> coeffs, vector<long double> xVals, long double a, long double b, long double tol, int maxIter ){
    int i = 1;
    long double fa = splineDerivativeEval( coeffs, xVals, a );
    while( i <= maxIter ){
        long double p = ( a + b ) / 2.0;
        long double fp = splineDerivativeEval( coeffs, xVals, p );
        if( abs(fp) == 0 || (b - a) / 2.0 < tol )
            return p;
        i++;
        if( fa * fp > 0 ){
            a = p;
            fa = fp;
        } else 
            b = p;
    }
    return NAN;
}

void writeData( vector<NaturalSplineCoefficients> coeffs, vector<long double> xVals, long double start, long double end, string filename ){
    ofstream outfile( "processedData/" + filename + ".dat" );
    for( long double x = start; x <= end; x += 0.1 ){
        long double y = splineEval( coeffs, xVals, x );
        outfile << x << " " << y << endl;
    }
    outfile.close();
    ofstream outfileDeriv( "processedData/" + filename + "Deriv.dat" );
    for( long double x = start; x <= end; x += 0.1 ){
        long double dydx = splineDerivativeEval( coeffs, xVals, x );
        outfileDeriv << x << " " << dydx << endl;
    }
    outfileDeriv.close();
}