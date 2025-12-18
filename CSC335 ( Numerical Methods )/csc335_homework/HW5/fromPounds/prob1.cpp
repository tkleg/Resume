#include<cmath>
#include "../Section4/runge_kutta.h"

#ifdef PROB_1
int main(){
    function<double( double, double )> f = []( double x, double y ){ return 5*y - 6 * exp( -x ); };
    double b = 4;
    double y0 = 1;
    double x0 = 0;

    vector<double> h_to_try = { 0.2, 0.1, 0.05, 0.01, 0.001 };
    for( double h : h_to_try )
        runge_kutta_4th_order( f, y0, x0, b, nullopt, h, "prob1/"+to_string(h)+".dat", false );

    function<double(double)> exact_solution = []( double x ){ return exp( -x ); };
    ofstream exact_file( "prob1/exact_solution.dat" );
    exact_file << fixed << setprecision(8);
    for( double x = x0; x <= b; x += 0.001 )
        exact_file << x << " " << exact_solution(x) << endl;
    exact_file.close();
    return 0;
}
#endif