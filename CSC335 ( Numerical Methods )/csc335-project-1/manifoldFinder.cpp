#include"manifoldFinder.h"
#include"common.h"

#ifdef MANIFOLD_FINDER_TEST
int main(){
    string filename;
    cout << "Enter the filename containing the data points: ";
    cin >> filename;
    vector< pair< double, double > > data = readDataFromFile( filename );

    //sort data by x values
    sort( data.begin(), data.end(), []( pair<double, double> a, pair<double, double> b ){
        return a.first < b.first;
    } );

    vector<NaturalSplineCoefficients> coeffs = naturalSplineCoeffs( data );

    vector<double> xValues;
    for( pair<double, double> point : data )
        xValues.push_back( point.first );
    function<double(double)> splineFunc = splineFunction( coeffs, xValues );
 
    vector<pair<double, double>> integralBounds = getIntegralBounds( splineFunc, 1e-7, make_pair( data.front().first, data.back().first ) );

    for( auto rootPair : integralBounds )
        cout << "Integration: " << rootPair.first << ", " << rootPair.second << endl;
    return 0;
}
#endif

//Pairs of points on the spline with x difference being 0.01 that cross the x-axis
vector< pair< pair<double, double>, pair<double, double> > > getCrossingBounds( function<double(double)> splineFunc, double tol, pair<double, double> domainBounds ){
    double startX = domainBounds.first;
    double endX = domainBounds.second;
    double currentX = startX;
    vector< pair< pair<double, double>, pair<double, double> > > crossingBounds;
    pair<double, double> firstPoint = make_pair( currentX, splineFunc(currentX) );
    double step = 0.01;

    //See if f(x) and f(x + step) have different signs. If so, there is a crossing between these two points.
    //Tolerance is used to avoid counting points that are both very close to zero as crossings.
    while( currentX + step <= endX ){
        pair<double, double> secondPoint = make_pair( currentX + step, splineFunc(currentX + step) );
        if( firstPoint.second * secondPoint.second < 0 && !(abs(firstPoint.second) < tol && abs(secondPoint.second) < tol ) ) // True if there is a crossing between these two points
            crossingBounds.push_back( make_pair( firstPoint, secondPoint ) );
        currentX += step;
        firstPoint = secondPoint;
    }
    return crossingBounds;
}

double bisection( function<double(double)> f, double a, double b, double tol, int maxIter ){
    //Algorithm taken from textbook

    int i = 1;
    double p = a;
    double fp, fa = f(a);
    while( i <= maxIter ){
        p = (a + b) / 2.0;
        fp = f(p);
        if( fp == 0 || abs(b - a) / 2.0 < tol ){
            return p;
        }
        i++;
        if( fa * fp > 0 ){
            a = p;
            fa = fp;
        } else
            b = p;
    }
    return NAN;
}

vector<pair<double, double>> getIntegralBounds( function<double(double)> splineFunc, double tol, pair<double, double> domainBounds ){
    
    //Pairs of points on the spline that bound the root
    vector< pair< pair< double, double >, pair<double, double> > >  crossingBounds = getCrossingBounds( splineFunc, tol, domainBounds );
    
    vector<pair<double, double>> roots;
    int index = 0;
    
    //Given each pair of crossing bounds, check if the first is increasing and the second is decreasing.
    //This ensures that we only get integral bounds that contain all positive y values.
    while( index < crossingBounds.size() - 1 ){
        bool bound1Increasing = crossingBounds[index].first.second < 0 &&
            crossingBounds[index].second.second > 0;
        bool bound2Increasing = crossingBounds[index+1].first.second < 0 && 
            crossingBounds[index+1].second.second > 0;
        if( bound1Increasing && !bound2Increasing ){
            double leftRoot = bisection( splineFunc, crossingBounds[index].first.first, crossingBounds[index].second.first, tol, 100000 );
            double rightRoot = bisection( splineFunc, crossingBounds[index+1].first.first, crossingBounds[index+1].second.first, tol, 100000 );
            roots.push_back( make_pair( leftRoot, rightRoot ) );
        }
        index++;
    }

    //Optional: Write integral bounds to file for debugging
    //The makefile creates an executable called "main_write" that defines WRITE_ALL
    #ifdef WRITE_ALL
        ofstream bounds("writtenData/integralBounds.dat");
        for( pair< double, double > rootPair : roots )
            bounds << rootPair.first << " " << rootPair.second << endl;
        bounds.close();

        ofstream singleColumn("writtenData/singleColumnIntegralBounds.dat");
        for( pair< double, double > rootPair : roots )
            singleColumn << rootPair.first << endl << rootPair.second << endl;
        singleColumn.close();
    #endif

    return roots;
}