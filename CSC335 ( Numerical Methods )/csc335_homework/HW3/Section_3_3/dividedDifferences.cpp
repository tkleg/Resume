#include"dividedDifferences.h"

double dividedDifferences(vector<double> coefs, vector<double> xVals, double x){
    double sum = 0;
    for( int i = 0; i < coefs.size(); i++ ){
        double product = coefs[i];
        for( int j = 0; j < i; j++ )
            product *= x - xVals[j];
        sum += product;
    }
    return sum;
}


vector<double> dividedDifferencesCoefficients(const vector< pair<double, double> > data){
    vector<vector<double>> matrix(data.size(), vector<double>(data.size()));
    //Fill the F_0,0 , F_0,1 , etc.
    for(int x = 0; x < data.size(); x++)
        matrix[x][0] = data[x].second;

    for( int i = 1; i < data.size(); i++ )
        for( int j = 1; j <= i; j++ )
            matrix[i][j] = ( matrix[i][j-1] - matrix[i-1][j-1] ) / 
                ( data[i].first - data[i-j].first );
    
    vector<double> coeffs;
    for( int i = 0; i < data.size(); i++ )
        coeffs.push_back( matrix[i][i] );
    
    return coeffs;
}