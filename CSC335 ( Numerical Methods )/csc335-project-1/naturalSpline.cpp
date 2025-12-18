#include"naturalSpline.h"

#ifdef NATURAL_SPLINE_TEST
int main(){ 

    cout << fixed << setprecision(20);

    vector<double> xVals;
    double start = -1000, end = 1000, step = .1;

    vector< function<double(double)> > functions = {f0, f1, f2, f3, f4, f5, f6};
    int num_func = functions.size();

    vector< vector<pair<double, double>> > allFunctionsData(num_func);

    for( double x = start; x <= end; x += step ){
        xVals.push_back(x);
        allFunctionsData[0].push_back( make_pair(x, f0(x)) );
        allFunctionsData[1].push_back( make_pair(x, f1(x)) );
        allFunctionsData[2].push_back( make_pair(x, f2(x)) );
        allFunctionsData[3].push_back( make_pair(x, f3(x)) );
        allFunctionsData[4].push_back( make_pair(x, f4(x)) );
        allFunctionsData[5].push_back( make_pair(x, f5(x)) );
        allFunctionsData[6].push_back( make_pair(x, f6(x)) );
    }

    vector<vector<NaturalSplineCoefficients>> coeffs(num_func);
    for( int i = 0; i < num_func; i++ )
        coeffs[i] = naturalSplineCoeffs( allFunctionsData[i] );

    step = 0.75;
    vector< vector<double> > relative_differences(num_func);
    vector< vector<double> > absolute_differences(num_func);
    for( double x = start; x <= end; x += step ){
        for( int i = 0; i < num_func; i++ ){
            double realVal = functions[i](x);
            if( isnan(realVal) )
                cout << "NaN detected at function " << i << " at x = " << x << endl;
            double splineVal = splineEval( coeffs[i], xVals, x );
            if( isnan(splineVal) )
                cout << "NaN detected in spline at function " << i << " at x = " << x << endl;
            if( realVal != splineVal ){
                absolute_differences[i].push_back( abs( realVal - splineVal ) );
                if( realVal != 0 )
                    relative_differences[i].push_back( abs( ( realVal - splineVal ) / realVal) );
            }
        }
        
    }
    for( int i = 0; i < num_func; i++ ){
        if (relative_differences[i].empty()) {
            cout << "Function " << i << " has no relative_differences recorded." << endl << endl;
            continue;
        }
        double avg = accumulate(relative_differences[i].begin(), relative_differences[i].end(), 0.0) / relative_differences[i].size();
        cout << "Function " << i << " average relative difference between spline and real function: " << avg << endl;
        cout << "Function " << i << " max relative difference between spline and real function: " << *max_element(relative_differences[i].begin(), relative_differences[i].end()) << endl;
        cout << "Function " << i << " min relative difference between spline and real function: " << *min_element(relative_differences[i].begin(), relative_differences[i].end()) << endl;
        cout << "Function " << i << " average absolute difference between spline and real function: " 
             << accumulate(absolute_differences[i].begin(), absolute_differences[i].end(), 0.0) / absolute_differences[i].size() << endl;
        cout << "Function " << i << " max absolute difference between spline and real function: " 
             << *max_element(absolute_differences[i].begin(), absolute_differences[i].end()) << endl;
        cout << "Function " << i << " min absolute difference between spline and real function: " 
             << *min_element(absolute_differences[i].begin(), absolute_differences[i].end()) << endl;
        cout << "Function " << i << " number of relative_differences recorded: " << relative_differences[i].size() << endl << endl;
    }

    return 0;
}
#endif

double f3(double x) {
    return 243 * pow(x, 3) - 486 * pow(x, 2) + 351 * x - 90;
}

double f2(double x) {
    return 81 * pow(x, 2) - 5234 * x + 351;
}

double f1(double x) {
    return 162 * x - 423;
}

double f0(double x) {
    return 48190.24;
}

double f4(double x) {
    return cbrt(x) * sin(x);
}

double f5(double x) {
    return cos(x) / log( x + 9999 );
}

double f6(double x) {
    return pow( x + 9999, x / 99 );
}


double splineEval( vector<NaturalSplineCoefficients> coeffs, vector< double > xVals, double x){
    int n = coeffs.size();
    int i = n - 1;
    for( int j = 0; j < n; j++ ){
        if( x >= xVals[j] && x <= xVals[j+1] ){
            i = j;
            break;
        }
    }
    double dx = x - xVals[i];
    return coeffs[i].a + coeffs[i].b * dx + coeffs[i].c * dx * dx + coeffs[i].d * dx * dx * dx;
}

vector<NaturalSplineCoefficients> naturalSplineCoeffs( vector< pair<double, double> > data ){
    //Algorithm taken from textbook
    
    int n = data.size() - 1;
    vector<NaturalSplineCoefficients>coeffs(n+1);
    vector<double> h(n+1);
    vector<double> alpha(n+1);

    for( int i = 0; i < n; i++ )
        h[i] = data[i + 1].first - data[i].first;
    
    for( int i = 1; i < n; i++ )
        alpha[i] = 3.0 / h[i] * (data[i+1].second - data[i].second) -
            3.0 / h[i-1] * ( data[i].second - data[i-1].second );
    
    vector<double> l(n+1);
    vector<double> mu(n+1);
    vector<double> z(n+1);

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