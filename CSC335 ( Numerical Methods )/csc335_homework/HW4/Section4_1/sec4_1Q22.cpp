#include<iostream>
#include<functional>
#include "methods.h"
using namespace std;

double twenty_two_vals(double x);

double twenty_two_voltage( double x );

int main(){
    cout << "Problem 22:" << endl;
    double point = 1;
    for( int x = 0; x < 5; x++ )
        cout << "The voltage at " << point + 0.01*x << " seconds is " << twenty_two_voltage( point + 0.01*x ) << " V" << endl;
    
    return 0;
}

double twenty_two_voltage( double x ){
    double slope = -1;
    if ( abs(x - 1) < 1e-4 )
        slope = three_pt_endpoint( twenty_two_vals, x, 0.01 );
    else if ( abs(x - 1.01) < 1e-4 )
        slope = three_pt_midpoint( twenty_two_vals, x, 0.01 );
    else if ( abs(x - 1.02) < 1e-4 )
        slope = three_pt_midpoint( twenty_two_vals, x, 0.01 );
    else if ( abs(x - 1.03) < 1e-4 )
        slope = three_pt_midpoint( twenty_two_vals, x, 0.01 );
    else
        slope = three_pt_endpoint( twenty_two_vals, x, -0.01 );

    return 0.98*slope + 0.142 * twenty_two_vals(x);
}

double twenty_two_vals(double x){
    double ans = -1;
    if (abs( x - 1 ) < 1e-4)
        ans = 3.10;
    else if (abs( x - 1.01 ) < 1e-4)
        ans = 3.12;
    else if (abs( x - 1.02 ) < 1e-4)
        ans = 3.14;
    else if (abs( x - 1.03 ) < 1e-4)
        ans = 3.18;
    else if (abs( x - 1.04 ) < 1e-4)
        ans = 3.24;
    if( ans == -1 )
        cout << "Error: x = " << x << " not found!" << endl;
    return ans;
}