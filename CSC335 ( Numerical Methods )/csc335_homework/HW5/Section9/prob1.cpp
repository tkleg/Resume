#include "runge_kutta_systems.h"

#ifdef PROB_1B
int main(){
    double a = 0;
    double b = 2;
    vector< function<double( double, vector<double> )> > funcs = {
        []( double t, vector<double> y ){ return -4 * y[0] - 2 * y[1] + cos(t) + 4 * sin(t); },
        []( double t, vector<double> y ){ return 3 * y[0] + y[1] - 3 * sin(t); }
    };
    vector< function<double(double)> > actual_funcs = {
        []( double t ){ return 2*exp(-t) - 2*exp(-2*t) + sin(t); },
        []( double t ){ return -3*exp(-t) + 2*exp(-2*t); }
    };
    vector<double> y0 = { 0, -1 };
    double h = 0.1;
    double result = runge_system_solver( a, b, funcs, actual_funcs, y0, nullopt, h, nullopt, true );
    return 0;
}
#endif