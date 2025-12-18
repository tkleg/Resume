#include "eulers.h"

#ifdef EULERS_TEST
int main() {
    double h = 0.1;
    double x_start = 0.0;
    double x_end = 2.0;
    double y0 = 1.0; // Initial condition y(0) = 1
    double result = 0;
    function<double(double, double)> f = [](double x, double y) { return x + y; }; // dy/dx = x + y
    result = eulers_method(f, y0, x_start, x_start, x_end, nullopt, h, nullopt, true);

    f = [](double x, double y) { return y - x*x + 1; }; // dy/dx = y - x^2 + 1
    function<double(double)> real = [](double x) { return (x + 1)*(x + 1) - 0.5*exp(x); }; // Real solution y = (x+1)^2 - 0.5e^x
    x_start = 0.0;
    x_end = 2.0;
    y0 = 0.5; // Initial condition y(0) = 0.5
    int N = 10;
    result = eulers_method(f, y0, x_start, x_start, x_end, N, nullopt, real, true);
    return 0;
}
#endif

double eulers_method(function<double(double, double)> f, double y0, double x0, optional<double> x_start, optional<double> x_end, optional<int> N, optional<double> h, optional< function<double(double)> > real, bool print_all, string filename  ){
    cout << fixed << setprecision(8);
    if ( !N )
        N = (int) ((x_end.value() - x_start.value()) / h.value());
    if( !h )
            h = (x_end.value() - x_start.value()) / N.value();
    double t = x_start.value();
    double y = y0;

    if( print_all ){
        cout << left << setw(4) << 0 << setw(10) << t << " " << setw(10) << y;
        if( real )
            cout << " " << setw(10) << real.value()(t) << " " << setw(10) << abs(y - real.value()(t));
        cout << endl;
    }

    ofstream out_file;
    if( filename != "" )
        out_file.open( filename );

    for(int i = 1; i <= N.value(); ++i){
        y = y + h.value() * f(t, y);
        t = x_start.value() + i * h.value();
        if( print_all ){
            cout << left << setw(4) << i << setw(10) << t << " " << setw(10) << y;
            if( real )
                cout << " " << setw(10) << real.value()(t) << " " << setw(10) << abs(y - real.value()(t));
            cout << endl;
        }
        if( filename != "" )
            out_file << t << " " << y << endl;
    }
    
    if( filename != "" )
        out_file.close();

    return y;
}