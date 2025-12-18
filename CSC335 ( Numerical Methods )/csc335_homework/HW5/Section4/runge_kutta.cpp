#include"runge_kutta.h"

double runge_kutta_4th_order(function<double(double, double)> f, double y0, double x0, double x_end, optional<int> N, optional<double> h, optional<string> data_filename, bool print_all, double function_constants ){
    if( !h )
        h = (x_end - x0) / N.value();
    if( !N )
        N = (int) ( (x_end - x0) / h.value() );
    double t = x0;
    double y = y0;
    ofstream data_file;
    if( data_filename ){
        data_file.open( data_filename.value() );
        data_file << fixed << setprecision(8);
    }
    for( int i = 1; i <= N.value(); i++ ){
        double k1 = h.value() * f(t, y);
        double k2 = h.value() * f(t + h.value()/2.0, y + k1/2.0);
        double k3 = h.value() * f(t + h.value()/2.0, y + k2/2.0);
        double k4 = h.value() * f(t + h.value(), y + k3);
        y = y + function_constants * (k1 + 2*k2 + 2*k3 + k4) / 6.0;
        t = x0 + i * h.value();
        if( print_all )
            cout << left << setw(4) << i << setw(12) << t << " " << setw(12) << y << endl;
        if( data_filename )
            data_file << t << " " << y << endl;
    }
    if( data_filename )
        data_file.close();
    return y;
}

#ifdef RUNGE_KUTTA_TEST
int main(){
    function<double(double, double)> f = [](double x, double y) { return x + y; };
    double y0 = 1.0;
    double x0 = 0.0;
    double x_end = 0.5;
    int N = 5;
    cout << fixed << setprecision(8);
    cout << "Runge-Kutta 4th Order Method:" << endl;
    double result = runge_kutta_4th_order(f, y0, x0, x_end, N, nullopt, nullopt, true);
    cout << "Approximate solution at x = " << x_end << " is y = " << result << endl;
    return 0;
}
#endif