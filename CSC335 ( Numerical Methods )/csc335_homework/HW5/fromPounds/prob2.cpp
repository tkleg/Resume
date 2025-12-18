#include "../Section4/runge_kutta.h"
#include "../Section2/eulers.h"

#ifdef PROB_2
int main(){
    function<double(double, double)> f = [](double t, double y){ return exp(t) * sin(y); };
    double y0 = 5;
    double x0 = 0;
    double x_start_a = 0;
    double x_end = 10;
    vector<double> h_values_a = {0.1, 0.001};
    for( double h : h_values_a ){
        eulers_method(f, y0, x_start_a, x_start_a, x_end, nullopt, h, nullopt, true, "prob2/a_eulers_" + to_string(h) + ".dat");
        runge_kutta_4th_order(f, y0, x_start_a, x_end, nullopt, h, "prob2/a_rk4_" + to_string(h) + ".dat", true);
    }

    vector<double> h_values_b = {0.1, 0.001, 0.00001};
    for( double h : h_values_b ){
        eulers_method(f, y0, x_start_a, x_start_a, x_end, nullopt, h, nullopt, true, "prob2/b_eulers_" + to_string(h) + ".dat");
        runge_kutta_4th_order(f, y0, x_start_a, x_end, nullopt, h, "prob2/b_rk4_" + to_string(h) + ".dat", true);
    }
    double h = 0.00001;
    double exact_start = 0;
    double exact_end = 10;
    string exact_data = "prob2/exact_solution.dat";
    runge_kutta_4th_order(f, y0, exact_start, exact_end, nullopt, h, exact_data, false);
    
    return 0;
}
#endif