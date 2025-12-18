#include<cmath>
#include "runge_kutta.h"

#ifdef PROB_27
int main(){
    function<double(double, double)> f = [](double t, double x){
        double n1 = 2e3;
        double n2 = 2e3;
        double n3 = 3e3;
        double k = 6.22e-19;
        return k * pow( n1 - x / 2, 2 ) * pow( n2 - x / 2, 2 ) * pow( n3 - 3* x / 4, 3 );
    };
    double y0 = 0;
    double x0 = 0;
    double x_end = 0.2;
    double h = 1e-5;
    double result = runge_kutta_4th_order( f, y0, x0, x_end, nullopt, h, nullopt, false );
    cout << "The approximate solution at x = " << x_end << " is y = " << result << endl;
    return 0;
}
#endif