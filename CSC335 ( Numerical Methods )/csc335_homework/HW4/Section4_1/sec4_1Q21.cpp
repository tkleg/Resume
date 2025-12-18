#include <vector>
#include <iostream>
#include <functional>
#include "methods.h"
using namespace std;

double twenty_one_vals(double x);

int main(){
    
    cout << "Problem 21:" << endl;
    cout << "a: f'(0.2) \u2248 " << five_pt_endpoint( twenty_one_vals, 0.2, 0.2 ) << endl;
    cout << "b: f'(1) \u2248 " << five_pt_endpoint( twenty_one_vals, 1, -0.2 ) << endl;
    cout << "c: f'(0.6) \u2248 " << five_pt_midpoint( twenty_one_vals, 0.6, 0.2 ) << endl;
    return 0;
}

double twenty_one_vals(double x){
    double ans = -1;
    if (abs( x - 0.2 ) < 1e-5)
        ans = 0.9798652;
    else if (abs( x - 0.4 ) < 1e-5)
        ans = 0.9177710;
    else if (abs( x - 0.6 ) < 1e-5)
        ans = 0.8080348;
    else if (abs( x - 0.8 ) < 1e-5)
        ans = 0.6386093;
    else if (abs( x - 1.0 ) < 1e-5)
        ans = 0.3842735;
    else
        cout << "Error: function called with invalid x value." << endl;
    return ans;
}

