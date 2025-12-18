#include<cmath>
#include<functional>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<cmath>
using namespace std;

double gauss_laguerre(function<double(double)> f, int n);

int main(){

    cout << setprecision(20) << fixed;
    double outside_integral = pow(10, 5) * sqrt( 2 * M_PI / 0.529 );
    for( int n : {3, 7, 15} )
        cout << "n = " << n << ", integral = " << outside_integral * gauss_laguerre( [](double x){ return 1 - x; }, n) << endl;

}

double gauss_laguerre(function<double(double)> f, int n) {
    double sum = 0;
    double x, w;
    ifstream data_in("GLa_" + to_string(n) + "_Points.txt");
    for( int j = 0; j < n; j++ ) {
        data_in >> x >> w;
        sum += (1-x) * w;
    }
    return sum;
}