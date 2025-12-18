#include "richardsons.h"


struct richardsInfo{
    double x0;
    double h;
    function<double(double)> f;
};

int main(){
    cout << setprecision(10);
    richardsInfo data_a = { 1, 0.4, [](double x){ return log(x); } };
    richardsInfo data_c = { 1.05, 0.4, [](double x){ return pow(2, x) * sin(x); } };

    cout << "Problem 1:" << endl;
    cout << "a) f(x) = ln(x), x0 = 1, and h = 0.4 gives N_3(h) = " << richardson( data_a.f, data_a.x0, data_a.h, 3 ) << endl;
    cout << "c) f(x) = 2^x * sin(x), x0 = 1.05, and h = 0.4 gives N_3(h) = " << richardson( [](double x){ return pow(2, x) * sin(x); }, 1.05, 0.4, 3 ) << endl;

    cout << endl << "Problem 2:" << endl;
    cout << "a) f(x) = ln(x), x0 = 1, and h = 0.4 gives N_3(h) = " << richardson( data_a.f, data_a.x0, data_a.h, 4 ) << endl;
    cout << "c) f(x) = 2^x * sin(x), x0 = 1.05, and h = 0.4 gives N_3(h) = " << richardson( [](double x){ return pow(2, x) * sin(x); }, 1.05, 0.4, 4 ) << endl;
}