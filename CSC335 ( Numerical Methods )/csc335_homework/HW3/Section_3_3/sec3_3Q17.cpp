#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<utility>
#include<iomanip>
#include "dividedDifferences.h"
using namespace std;

vector< pair<double, double> > readDataFromFile(const string filename); 

int main() {

    vector< pair<double, double> > data = readDataFromFile("../chapterStartData.dat");

    vector<double> coeffs = dividedDifferencesCoefficients(data);
    cout << "Divided differences coefficients: " << endl;
    cout << fixed;
    for( double val : coeffs )
        cout << val << " ";
    cout << endl << endl;

    vector<double> xVals;
    for( pair<double, double> p : data )
        xVals.push_back( p.first );
        
    //Prevents populations from being printed in scientific notation
    cout << fixed << setprecision(0);
    
    cout << "Predicted populations: " << endl;
    for( double x : {1950, 1975, 2014, 2020} )
        cout << x << ": " << dividedDifferences(coeffs, xVals, x) << endl;

    return 0;
}

vector< pair<double, double> > readDataFromFile(const string filename) {
    ifstream infile(filename);
    vector<pair<double, double>> data;

    if (!infile) {
        cerr << "Error opening file: " << filename << endl;
        return data;
    }

    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        double x, y;
        ss >> x >> y;
        data.push_back(make_pair(x, y));
    }

    infile.close();
    return data;
}