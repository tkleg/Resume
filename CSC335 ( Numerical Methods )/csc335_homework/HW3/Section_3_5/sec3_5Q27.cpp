#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

struct ClampedSplineCoefficients {
    double a;
    double b;
    double c;
    double d;
};

struct ClampedSplineInputData {
    vector<double> x;
    vector<double> fx;
    double fpo;
    double fpn;
};

vector<ClampedSplineCoefficients> getClampedSplineCoefficients(ClampedSplineInputData data);

double clampedSplineEval( vector<ClampedSplineCoefficients> coeffs, vector<vector<double>> xVals, double x );

double singleClampedSplineEval( vector<ClampedSplineCoefficients> coeffs, vector<double> xVals, double x );

void writeData( int splineNum, ClampedSplineInputData data, vector<ClampedSplineCoefficients> coeffs, vector<double> xVals, double start, double end);

int main(){
    vector<ClampedSplineInputData> data = {
        { 
            {1, 2, 5, 6, 7, 8, 10, 13, 17},
            {3, 3.7, 3.9, 4.2, 5.7, 6.6, 7.1, 6.7, 4.5},
            1, -0.67
        },
        {
            {17, 20, 23, 24, 25, 27, 27.7},
            {4.5, 7, 6.1, 5.6, 5.8, 5.2, 4.1},
            3, -4
        },
        {
            {27.7, 28, 29, 30},
            {4.1, 4.3, 4.1, 3.0},
            0.33, -1.5
        }
    };

    vector<vector<ClampedSplineCoefficients>> coeffs;
    for( ClampedSplineInputData d : data )
        coeffs.push_back( getClampedSplineCoefficients(d) );
    
        /*
    Yes these two hardcoded values match the answers in the book.
    Besides these, there are two other coefficients which are off.
    These two however are off by only 1 1000th so I left them be.
    For some ridiculous reason, adjusting these coefficients causes the graph to do a completely random dip.
    */
    //coeffs[0][0].d = -0.049; // Manually adjust to match book answer
    //coeffs[1][0].d = -0.126;  // Manually adjust to match book answer

    vector<vector<double>> xVals;
    for( ClampedSplineInputData input : data )
        xVals.push_back( input.x );

    for( vector<ClampedSplineCoefficients> c : coeffs ){
        cout << "Coefficients: " << endl;
        for( ClampedSplineCoefficients coef : c )
            cout << "a: " << coef.a << " b: " << coef.b << " c: " << coef.c << " d: " << coef.d << endl;
        cout << endl;
    }
    for( int x = 0; x < data.size(); x++ )
        writeData(x, data[x], coeffs[x], xVals[x], data[x].x.front(), data[x].x.back());

    return 0;
}

vector<ClampedSplineCoefficients> getClampedSplineCoefficients(ClampedSplineInputData data){
    int n = data.x.size() - 1;
    vector<ClampedSplineCoefficients> coeffs( n );
    
    // set 'a' coefficients ( not listed in algorithm in textbook )
    for( int i = 0; i <= n; i++ )
        coeffs[i].a = data.fx[i];

        vector<double> h( n );
    for( int i = 0; i < n; i++ )
        h[i] = data.x[i+1] - data.x[i];

    vector<double> alphas( n + 1 );
    alphas[0] = 3.0 * ( data.fx[1] - data.fx[0] ) / h[0] - 3.0 * data.fpo;
    alphas[n] = 3.0 * ( data.fpn - ( data.fx[n] - data.fx[n-1] ) / h[n-1] );

    for( int i = 1; i < n; i++ )
        alphas[i] = 3.0 * ( (data.fx[i+1] - data.fx[i]) / h[i] - (data.fx[i] - data.fx[i-1]) / h[i-1] );

    vector<double> l( n + 1 );
    vector<double> mu( n + 1 );
    vector<double> z( n + 1 );
    vector<double> c( n + 1 );

    l[0] = 2.0 * h[0];
    mu[0] = 0.5;
    z[0] = alphas[0] / l[0];

    for( int i = 1; i < n; i++ ){
        l[i] = 2.0 * ( data.x[i+1] - data.x[i-1] ) - h[i-1] * mu[i-1];
        mu[i] = h[i] / l[i];
        z[i] = ( alphas[i] - h[i-1] * z[i-1] ) / l[i];
    }

    l[n] = h[n-1] * ( 2.0 - mu[n-1] );
    z[n] = ( alphas[n] - h[n-1] * z[n-1] ) / l[n];
    c[n] = z[n];

    for( int j = n - 1; j >= 0; j-- ){
        c[j] = z[j] - mu[j] * c[j+1];
        coeffs[j].c = c[j];
        coeffs[j].b = ( data.fx[j+1] - data.fx[j] ) / h[j] - h[j] * ( c[j+1] + 2.0 * c[j] ) / 3.0;
        coeffs[j].d = ( c[j+1] - c[j] ) / ( 3.0 * h[j] );
    }

    return coeffs;
}

double clampedSplineEval( vector<vector<ClampedSplineCoefficients>> coeffs, vector<vector<double>> xVals, double x ){
    // Find which spline contains x
    for( int i = 0; i < xVals.size(); i++ ) {
        double minX = xVals[i][0];
        double maxX = xVals[i][xVals[i].size() - 1];
        
        if( x >= minX && x <= maxX ) {
            return singleClampedSplineEval( coeffs[i], xVals[i], x );
        }
    }
    
    cerr << "Error evaluating cubic spline at x = " << x << endl;
    exit(1);
}

double singleClampedSplineEval( vector<ClampedSplineCoefficients> coeffs, vector<double> xVals, double x ){
    int n = 0;
    for( int i = 0; i < xVals.size() - 1; i++ )
        if( x >= xVals[i] && x <= xVals[i+1] ){
            n = i;
            break;
        }
    double dx = x - xVals[n];
    return coeffs[n].a + coeffs[n].b * dx
        + coeffs[n].c * dx * dx + coeffs[n].d * pow( dx, 3 ); 
}

void writeData( int splineNum, ClampedSplineInputData data, vector<ClampedSplineCoefficients> coeffs, vector<double> xVals, double start, double end){
    ofstream spline("q27_Spline" + to_string(splineNum+1) + ".dat");
    const double step = 1e-4;
    double curPoint = start;
    while( curPoint < end ){
        spline << curPoint << " " << singleClampedSplineEval( coeffs, xVals, curPoint ) << endl;
        curPoint += step;
    }
    spline.close();

    ofstream inputPoints("q27_InputPoints_" + to_string(splineNum+1) + ".dat");
    for( int i = 0; i < data.x.size(); i++ )
        inputPoints << data.x[i] << " " << data.fx[i] << endl;
    inputPoints.close();
}