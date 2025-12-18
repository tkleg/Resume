#include "runge_kutta_systems.h"

#ifdef PROB_6
int main(){
    double a = 0;
    double b = 15;
    vector< function<double( double, vector<double> )> > funcs = {
        []( double t, vector<double> y ){ return y[0]*( 4 - 0.0003*y[0] - 0.0004*y[1] ); },
        []( double t, vector<double> y ){ return y[1]*( 2 - 0.0002*y[0] - 0.0001*y[1] ); }
    };
    vector<double> y0 = { 10000, 10000 };
    double h = 0.001;
    double result = runge_system_solver( a, b, funcs, nullopt, y0, nullopt, h, "prob6.dat", true );
    return 0;
}
#endif