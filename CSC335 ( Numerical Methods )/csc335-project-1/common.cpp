#include "common.h"

function<double(double)> splineFunction( vector<NaturalSplineCoefficients> coeffs, vector<double> xVals){
    return [coeffs, xVals]( double x ){
        return splineEval( coeffs, xVals, x );
    };
}

vector< pair<double, double> > readDataFromFile(const string filename) {
    ifstream infile(filename);
    vector<pair<double, double>> data;

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

void writeDataToFile( vector< pair<double, double> > data, string filename ){
    ofstream outfile("writtenData/" + filename);
    if( !outfile ){
        cerr << "Error opening output file" << filename << endl;
        exit(1);
    }
    for( int x = 0; x < data.size(); x++ )
        outfile << data[x].first << " " << data[x].second << endl;
    outfile.close();
}
