#include<iostream>
#include<iomanip>
#include<functional>
#include<optional>
#include<cmath>
using namespace std;

double area( double x ){
    return M_PI * x * x;
}

double xprime( double t, double x ){
    return -0.6 * M_PI * 0.1 * 0.1 * sqrt( 2 * 32.1 ) * sqrt( x ) / area( x );
}

#ifdef PROB_28
int main(){
    function<double(double, double)> f = []( double t, double x ){
        return -0.6 * 0.1*0.1 * sqrt( 2 * 32.1 ) / pow( x, 1.5 );
    };
    double y0 = 8;//initial height
    double x0 = 0;//initial time
    double x_end = 10 * 60; // 10 minutes in seconds
    double h = 20; // step size of 20 seconds
    
    //Part A
    double t = x0;
    double x = y0;
    while( x >= 0 && t < x_end && t >= x0 ){
        double k1 = h * f( t, x );
        double k2 = h * f( t + h / 2, x + k1 / 2 );
        double k3 = h * f( t + h / 2, x + k2 / 2 );
        double k4 = h * f( t + h, x + k3 );
        x += ( k1 + 2 * k2 + 2 * k3 + k4 ) / 6;
        t += h;
        cout << "t: " << t << " x: " << x << endl;
    }
    cout << "a) After 10 minutes with h = " << h << ", the water height is " << x << " feet." << endl;

    //Part B
    t = x0;
    x = y0;
    while( x >= 0 ){
        double k1 = h * f( t, x );
        double k2 = h * f( t + h / 2, x + k1 / 2 );
        double k3 = h * f( t + h / 2, x + k2 / 2 );
        double k4 = h * f( t + h, x + k3 );
        x += ( k1 + 2 * k2 + 2 * k3 + k4 ) / 6;
        t += h;
    }
    cout << "b) The tank will be empty after " << round(t) << " seconds." << endl;

    return 0;
}
#endif