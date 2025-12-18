#include<vector>
#include<utility>
#include<iostream>
#include"naturalSpline.h"
#include<iomanip>
#include<fstream>
#include<cmath>
using namespace std;

int main(){

    vector< pair<long double, long double> > miles = {
        {0,0}, {0.25, 23.04}, {0.5, 47.37}, {1, 97.45}, {1.25, 123.66}
    };
    vector<long double> xVals;
    for( pair<long double, long double> p : miles )
        xVals.push_back( p.first );

    vector<NaturalSplineCoefficients> coeffs = naturalSplineCoeffs( miles );
    cout << setw(6) << "x_i" << setw(8) << "a_i" << setw(12) << "b_i" << setw(14) << "c_i" << setw(14) << "d_i" << endl;
    for( int x = 0; x < coeffs.size(); x++ )
        cout << setw(6) << miles[x].first << setw(8) << coeffs[x].a << setw(12) << coeffs[x].b << setw(14) << coeffs[x].c << setw(14) << coeffs[x].d << endl;

    long double guessAt3Quarters = splineEval( coeffs, xVals, 0.75 );
    cout << endl << "Estimate at 0.75 miles: " << guessAt3Quarters << " seconds" << endl;
    long double actualAt3Quarters = 71.8;
    cout << "Actual at 0.75 miles: " << actualAt3Quarters << " seconds" << endl;
    cout << "Absolute error: " << abs( guessAt3Quarters - actualAt3Quarters ) << " seconds" << endl;
    cout << "Relative error: " << abs( guessAt3Quarters - actualAt3Quarters ) / actualAt3Quarters << endl << endl;

    long double predictedStartSpeed = splineDerivativeEval( coeffs, xVals, 0 );
    cout << "Predicted starting speed: " << predictedStartSpeed << " seconds per mile" << endl;

    long double predictedEndSpeed = splineDerivativeEval( coeffs, xVals, 1.25 );
    cout << "Predicted ending speed: " << predictedEndSpeed << " seconds per mile" << endl;


    ofstream outFile("q26Spline.dat");
    ofstream outDerivFile("q26SplineDeriv.dat");
    for( long double x = 0.0; x <= 1.25; x += 1e-4 ){
        outFile << x << " " << splineEval( coeffs, xVals, x ) << endl;
        outDerivFile << x << " " << splineDerivativeEval( coeffs, xVals, x ) << endl;
    }
    outFile.close();
    outDerivFile.close();

    return 0;
}