#include"hermite.h"

vector< vector<long double> > createHermiteData( vector<HermiteNode> data ){
    
    //create a 2D vector to hold the new data
    int n = data.size() - 1;
    vector< vector<long double> > hermiteData( 2 * n + 2, vector<long double>(2 * n + 2) );
    vector<long double> z( n * 2 + 2 );
    for( int i = 0; i <= n; i++ ){
        z[2*i] = data[i].x;
        z[2*i+1] = data[i].x;
        hermiteData[2*i][0] = data[i].fx;
        hermiteData[2*i+1][0] = data[i].fx;
        hermiteData[2*i+1][1] = data[i].dfx;
        if( i != 0 )
            hermiteData[2*i][1] = 
                ( hermiteData[2*i][0] - hermiteData[2*i-1][0] ) 
                / ( z[2*i] - z[2*i-1] );
    }


    for( int i = 2; i <= 2*n+1; i++ )
        for( int j = 2; j <= i; j++ )
            hermiteData[i][j] = 
                ( hermiteData[i][j-1] - hermiteData[i-1][j-1] ) 
                / ( z[i] - z[i-j] );

    return hermiteData;
}

long double hermite( vector<long double> xVals, vector< vector<long double> > hermiteData, long double x ){
    long double answer = hermiteData[0][0];
    for( int i = 1; i < hermiteData.size(); i++ ){
        long double product = hermiteData[i][i];
        if( i % 2 == 0 ){
            for( int j = 0; j <= (i-1)/2; j++ )
                product *= pow(x - xVals[j], 2);
        }else{
            for( int j = 0; j <= (i-1)/2; j++ )
                product *= x - xVals[j];
            for( int j = 0; j <= (i-1)/2-1; j++ )
                product *= x - xVals[j];
        }
        answer += product;
    }
    return answer;
}