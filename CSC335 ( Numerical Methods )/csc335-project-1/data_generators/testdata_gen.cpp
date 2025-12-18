#include<fstream>
#include<iostream>
#include<vector>
#include<utility>
#include<functional>
#include<algorithm>
#include<set>
#include"../integrals.h"
#include"../naturalSpline.h"
using namespace std;

function<double(double)> geometricFunc(vector<pair<double,double>> points);

void writetrigData();

#ifdef SHAPED_DATA_GEN
int main(){
    double start = -20, end = 20, step = 0.001;

    //Trapezoid points: 1, 2, 3, 4
    //Triangle points: 5, 6, 7
    //End points: 0, 8
    vector<pair<double,double>> points = {
        {-20, 0},
        {-10, 0},
        {1, 10000},
        {4, 10000},
        {7, 0},
        {13, 0},
        {16, 5000},
        {19, 0},
        {20, 0}
    };

    double baseline;
    cout << "Enter baseline value: ";
    cin >> baseline;

    ofstream pointsOut("geometric_points.dat");
    for(auto &p : points){
        //p.second -= baseline;
        //if (p.second < 0.0)
        //    p.second = 0.0;
        pointsOut << p.first << " " << p.second << endl;
     //   cout << "(" << p.first << ", " << p.second << ")" << endl;
    }
    pointsOut.close();

    function<double(double)> geometric_help = geometricFunc(points);

    ofstream exactOut("geometric_exact.dat");
    function<double(double)> geometric = [geometric_help](double x){
        return geometric_help(x);
    };

    //ofstream fout("geometric_data.dat");
    for(double x = start; x <= end; x += step)
        exactOut << x << " " << geometric(x) << endl;
    exactOut.close();

    double tol = 1e-8;
    cout << "Adaptive Quadrature Approximation: " 
         << adaptive_quadrature(geometric, start, end, tol) << endl;
    cout << "Romberg Integration Approximation: " 
         << romberg_extrapolation(geometric, start, end, 10).back().back() << endl;
    cout << "Gauss-Legendre Quadrature Approximation: " 
         << gauss_legendre_64pt(geometric, start, end) << endl;

    int numPoints = 1329 - points.size();
    set<pair<double,double>> uniquePoints(points.begin(), points.end());
    double myStep = (end - start) / numPoints;
    for(double x = start; x <= end; x += myStep)
        uniquePoints.insert( make_pair(x, geometric(x)) );
    vector< pair<double, double> > data( uniquePoints.begin(), uniquePoints.end() );
    vector<NaturalSplineCoefficients> coeffs = naturalSplineCoeffs( data );

    vector<double> xVals;
    for( pair<double, double> point : data )
        xVals.push_back(point.first);

    function<double(double)> spline = splineFunction( coeffs, xVals );

    ofstream splineOut("geometric_spline.dat");
    for(double x = start; x <= end; x += step)
        splineOut << x << " " << spline(x) << endl;
    splineOut.close();

    double start_spline = -20, end_spline = 20;
    cout << "Spline Integrations 1:" << endl;
    cout << "Before Adaptive Quadrature Approximation: " << endl;
    cout << "Adaptive Quadrature Approximation: " 
         << adaptive_quadrature(spline, start_spline, end_spline, 1e-8) << endl;
    cout << "After Adaptive Quadrature Approximation: " << endl;
    cout << "Romberg Integration Approximation: " 
         << romberg_extrapolation(spline, start_spline, end_spline, 10).back().back() << endl;
    cout << "Gauss-Legendre Quadrature Approximation: " 
         << gauss_legendre_64pt(spline, start_spline, end_spline) << endl;

    writetrigData();

    return 0;
}
#endif

void writetrigData(){
    ofstream fout("writtenData/trig_data.dat");
    double start = -20, end = 20, step = 0.01;
    for(double x = start; x <= end; x += step)
        fout << x << " " << ( 3 * sin(0.5 * x) + 5 * cos(x) + 2 ) << endl;
    fout.close();
}
function<double(double)> geometricFunc(vector<pair<double,double>> points) {
    return [points](double x) {
        if( x <= points[1].first )
            return points[1].second;
        else if( x <= points[2].first )
            return ( points[2].second - points[1].second ) / ( points[2].first - points[1].first ) * ( x - points[1].first ) + points[1].second;
        else if( x <= points[3].first )
            return points[2].second;
        else if ( x <= points[4].first )
            return ( points[4].second - points[3].second ) / ( points[4].first - points[3].first ) * ( x - points[3].first ) + points[3].second;
        else if ( x <= points[5].first )
            return points[5].second;
        else if ( x <= points[6].first )
            return ( points[6].second - points[5].second ) / ( points[6].first - points[5].first ) * ( x - points[5].first ) + points[5].second;
        else if ( x <= points[7].first )
            return ( points[7].second - points[6].second ) / ( points[7].first - points[6].first ) * ( x - points[6].first ) + points[6].second;
        else if ( x <= points[8].first )
            return points[8].second;
        else
            throw invalid_argument("x value out of bounds");
    };
}