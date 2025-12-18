#include "eulers.h"

#ifdef PROB_1
int main(){
    function<double(double, double)> f = [](double x, double y) { return x * exp(3 * x) - 2 * y; };
    double y0 = 0;
    double x0 = 0;
    double x_end = 1;
    double h = 0.5;
    bool print_all = true;
    function<double(double)> real = [](double x) { return ( exp(3*x) * (5*x-1) )/25 + 1.0/( 25 * exp(2*x) ); };
    double result = eulers_method(f, y0, x0, x0, x_end, nullopt, h, real, print_all);
    cout << endl << "----------------------------------------" << endl << endl;
    f = [](double x, double y) { return cos(2*x) + sin(3*x); };
    y0 = 1;
    x0 = 0;
    x_end = 1;
    h = 0.25;
    print_all = true;
    real = [](double x) { return 0.5*sin(2*x) - 1.0/3.0 * cos(3*x) + 4.0/3.0; };
    result = eulers_method(f, y0, x0, x0, x_end, nullopt, h, real, print_all);
    return 0;
}
#endif