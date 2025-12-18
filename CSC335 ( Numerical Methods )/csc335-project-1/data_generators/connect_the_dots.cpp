#include<vector>
#include<utility>
#include<functional>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<iomanip>
using namespace std;

vector< pair<double, double> > readDataFromFile( string filename );

function<double(double)> connectTheDots( vector< pair<double, double> > data );

#ifdef CONNECT_THE_DOTS_MAIN
int main() {
    cout << "Enter the data file name: ";
    string filename;
    cin >> filename;
    vector< pair<double, double> > data = readDataFromFile(filename);
    sort( data.begin(), data.end(), []( const pair<double, double>& a, const pair<double, double>& b ) {
        return a.first < b.first;
    } );
    function<double(double)> interpFunc = connectTheDots( data );
    double start = data.front().first;
    double end = data.back().first;
    double current = start;
    int numPoints = 1329;
    double step = (end - start) / (numPoints - 1);
    ofstream outfile( "connected.dat" );
    outfile << fixed << setprecision(8);
    while( current <= end ){
        outfile << current << " " << interpFunc( current ) << endl;
        current += step;
    }
    return 0;
}
#endif

vector< pair<double, double> > readDataFromFile( string filename ) {
    ifstream infile( filename );
    vector< pair<double, double> > data;
    double x, y;
    while( infile >> x >> y ) {
        data.push_back( make_pair(x, y) );
    }
    infile.close();
    return data;
}

function<double(double)> connectTheDots( vector< pair<double, double> > data ) {
    return [data]( double x ) {
        for( size_t i = 0; i < data.size() - 1; ++i ) {
            if( x >= data[i].first && x <= data[i+1].first ) {
                double x0 = data[i].first;
                double y0 = data[i].second;
                double x1 = data[i+1].first;
                double y1 = data[i+1].second;
                double slope = (y1 - y0) / (x1 - x0);
                return y0 + slope * (x - x0);
            }
        }
        cerr << "Warning: x value " << x << " is out of bounds." << endl;
        exit(1);
    };
}