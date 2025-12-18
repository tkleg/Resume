#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <iomanip>
#include "lagrange.h"
using namespace std;

vector< pair<long double, long double> > readDataFromFile(const string filename); 

int main() {
    cout << fixed << setprecision(0);
    //Read data into a vector of pairs
    vector< pair<long double, long double> > data = readDataFromFile("../chapterStartData.dat");

    for( long double year : { 1950, 1975, 2014, 2020 } ){
        long double estimate = lagrange( data, year );
        cout << "Year: " << year << ". Estimate: " << estimate << endl;
    }

    return 0;
}

vector< pair<long double, long double> > readDataFromFile(const string filename) {
    ifstream infile(filename);
    vector<pair<long double, long double>> data;

    if (!infile) {
        cerr << "Error opening file: " << filename << endl;
        return data;
    }

    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        long double x, y;
        ss >> x >> y;
        data.push_back(make_pair(x, y));
    }

    infile.close();
    return data;
}