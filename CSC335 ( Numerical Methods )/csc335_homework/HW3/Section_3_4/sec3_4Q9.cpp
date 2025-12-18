#include"hermite.h"
#include<iostream>
#include<fstream>

int main() {

    vector< HermiteNode > data = 
    { { 0, 0, 75}, {3, 225, 77}, {5, 383, 80}, 
    {8, 623, 74}, {13, 993, 72} };

    vector< vector<long double> > hermiteData = createHermiteData( data );

    vector<long double> xVals;
    for( HermiteNode n : data )
        xVals.push_back( n.x );

    cout << "The position of the car at 10 seconds is " << hermite( xVals, hermiteData, 10 ) << " feet" << endl;

    //55mph to feet per second
    long double goalSpeed = 55 * 5280.0 / 3600.0;
    long double goalX = 0;
    long double maxSpeed = 0;
    long double maxX = 0;
    bool goalFound = false;
    const long double step = 1e-4;
    ofstream outputFile("q9.dat");
    for( long double x = 0; x <= 13; x += step ){
        long double derivative = (hermite( xVals, hermiteData, x + step ) - hermite( xVals, hermiteData, x )) / step;
        outputFile << x << " " << derivative / 5280.0 * 3600.0 << endl;
        if( derivative > maxSpeed ){
            maxSpeed = derivative;
            maxX = x;
        }
        if( !goalFound && derivative >= goalSpeed ){
            goalX = x;
            goalFound = true;
        }
    }
    cout << "The velocity of the car reaches 55 mph for the first time at time " << goalX << " seconds" << endl;
    cout << "The exact velocity at the time is " << (hermite( xVals, hermiteData, goalX + step ) - hermite( xVals, hermiteData, goalX )) / step << " feet per second" << endl;
    cout << "The maximum velocity of the car is " << maxSpeed / 5280.0 * 3600.0 << " mph at time " << maxX << " seconds" << endl;
    return 0;
}