#include"naturalSpline.h"

long double splineEval( vector<NaturalSplineCoefficients> coeffs, vector< long double > xVals, long double x){
    int n = coeffs.size();
    int i = n - 1;
    for( int j = 0; j < n; j++ ){
        if( x >= xVals[j] && x <= xVals[j+1] ){
            i = j;
            break;
        }
    }
    long double dx = x - xVals[i];
    return coeffs[i].a + coeffs[i].b * dx + coeffs[i].c * dx * dx + coeffs[i].d * dx * dx * dx;
}

long double splineDerivativeEval( vector<NaturalSplineCoefficients> coeffs, vector< long double > xVals, long double x){
    int n = coeffs.size();
    int i = n - 1;
    for( int j = 0; j < n; j++ ){
        if( x >= xVals[j] && x <= xVals[j+1] ){
            i = j;
            break;
        }
    }
    long double dx = x - xVals[i];
    return coeffs[i].b + 2 * coeffs[i].c * dx + 3 * coeffs[i].d * dx * dx;
}

vector<NaturalSplineCoefficients> naturalSplineCoeffs( vector< pair<long double, long double> > data ){
    int n = data.size() - 1;
    vector<NaturalSplineCoefficients>coeffs(n+1);
    vector<long double> h(n+1);
    vector<long double> alpha(n+1);

    for( int i = 0; i < n; i++ )
        h[i] = data[i + 1].first - data[i].first;
    
    for( int i = 1; i < n; i++ )
        alpha[i] = 3.0 / h[i] * (data[i+1].second - data[i].second) -
            3.0 / h[i-1] * ( data[i].second - data[i-1].second );
    
    vector<long double> l(n+1);
    vector<long double> mu(n+1);
    vector<long double> z(n+1);

    l[0] = 1;
    mu[0] = 0;
    z[0] = 0;

    for( int i = 1; i < n; i++ ){
        l[i] = 2 * ( data[i+1].first - data[i-1].first ) - h[i-1] * mu[i-1];
        mu[i] = h[i] / l[i];
        z[i] = ( alpha[i] - h[i-1] * z[i-1] ) / l[i];
    }

    l[n] = 1;
    z[n] = 0;
    coeffs[n].c = 0;

    for( int j = n-1; j >= 0; j-- ){
        coeffs[j].c = z[j] - mu[j] * coeffs[j+1].c;
        coeffs[j].b = ( data[j+1].second - data[j].second ) / h[j] - 
            h[j] * ( coeffs[j+1].c + 2 * coeffs[j].c ) / 3;
        coeffs[j].d = ( coeffs[j+1].c - coeffs[j].c ) / ( 3 * h[j] );
        coeffs[j].a = data[j].second;
    }
    coeffs.pop_back(); // Remove the last element which is not needed
    return coeffs;
}