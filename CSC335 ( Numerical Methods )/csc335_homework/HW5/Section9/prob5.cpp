#include "runge_kutta_systems.h"

#ifdef PROB_5
int main(){
    double a = 0;
    double b = 100;
    double k1 = 3, k2 = 0.002, k3 = 0.0006, k4 = 0.5;
    vector< function<double( double, vector<double> )> > funcs = {
        [k1, k2]( double t, vector<double> y ){ return k1*y[0] - k2*y[0]*y[1]; },
        [k3, k4]( double t, vector<double> y ){ return k3*y[0]*y[1] - k4*y[1]; }
    };
    vector<double> y0 = { 1000, 500 };
    double h = 0.01;
    double result = runge_system_solver( a, b, funcs, nullopt, y0, nullopt, h, "prob5.dat", true );
    return 0;
}
#endif