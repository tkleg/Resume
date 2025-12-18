#include<vector>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<iomanip>
#include<functional>
#include <utility>
using namespace std;

double composite_simpsons_rule( function<double(double)> f, double a, double b, int n );

pair<double, int> tolerant_composite_simpsons_rule( function<double(double)> f, double a, double b, double tol );

int main(){
    function<double(double)> part1 = []( double x ){ return 1 / ( 1.0 + pow(x, 4) ); };
    double a = 0, b = 1;
    double tol = 1e-9;
    int n1 = 2;
    pair<double, int> answer1 = tolerant_composite_simpsons_rule(part1, a, b, tol);
    cout << setprecision(10) << answer1.first << " " << answer1.second << endl;

    function<double(double)> part2 = []( double t ){  
        return t * t / ( pow(t, 4) + 1 ); };
    pair<double, int> answer2 = tolerant_composite_simpsons_rule(part2, a, b, tol);
    cout << setprecision(10) << answer2.first << " " << answer2.second << endl;
    cout << answer1.first + answer2.first << endl;
    return 0;
}

// Returns the integral approximation and the number of subintervals used
//First is the integral approximation, second is the number of subintervals used
pair<double, int> tolerant_composite_simpsons_rule( function<double(double)> f, double a, double b, double tol ){
    int n = 2;
    double integral_n = composite_simpsons_rule(f, a, b, 2);
    double integral_n2 = composite_simpsons_rule(f, a, b, 4);
    n = 4;
    while( abs( integral_n2 - integral_n ) > tol ){
        n += 2;
        integral_n = integral_n2;
        integral_n2 = composite_simpsons_rule(f, a, b, n);
    }
    return make_pair(integral_n2, n);
}

double composite_simpsons_rule( function<double(double)> f, double a, double b, int n ){
    double h = ( b - a ) / n;
    double sum = f(a) + f(b);
    for( int j = 1; j <= n/2 - 1; j++ ){
       sum += 2 * f( a + (2 * j) * h );
    }
    for( int j = 1; j <= n/2; j++ ){
        sum += 4 * f( a + (2 * j - 1) * h );
    }
    
    return h / 3 * sum;
}