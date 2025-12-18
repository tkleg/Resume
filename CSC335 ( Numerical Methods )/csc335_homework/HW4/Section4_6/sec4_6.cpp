#include<vector>
#include<functional>
#include<cmath>
#include<iostream>
#include<iomanip>
#include<cstdio>
using namespace std;

double simpson_rule_third( function<double(double)> f, double a, double b );

double adaptive_quadrature( function<double(double)> f, double a, double b, double tol, double actual_value = -1, bool root_call = false );

struct integral_data{
    double estimate;
    double abs_error;
    double rel_error;
};

int main(){
    cout << fixed << setprecision(15);
    cout << "Problem 1a: " << endl;
    function< double(double) > f1 = []( double x ){ return x * x * log(x); };
    double actual = 0.19225935;
    double answer = adaptive_quadrature( f1, 1, 1.5, 1e-6, actual, true );

    cout << fixed;
    actual = 2.58862863251;
    cout << "\nProblem 2a: " << endl;
    function< double(double) > f2 = []( double x ){ return exp( 3 * x ) * sin( 2 * x ); };
    answer = adaptive_quadrature( f2, 0, M_PI/4, 1e-6, actual, true);

    cout << "\nProblem 3a: " << endl;
    actual = 0.19225935;
    answer = adaptive_quadrature( f1, 1, 1.5, 1e-3, actual );
    cout << "Estimated Integral = " << answer << endl;

    cout << "Problem 4a: " << endl;
    actual = 2.58862863251;
    answer = adaptive_quadrature( f2, 0, M_PI/4, 1e-8, actual  );
    cout << "Estimated Integral = " << answer << endl;

    cout << "\nProblem 10: " << endl;
    function<double(double)> c = [](double t){ return cos( M_PI / 2.0 * t * t); };
    function<double(double)> s = [](double t){ return sin( M_PI / 2.0 * t * t); };
    cout << fixed << setprecision(6);

    printf(" %-10s | %-15s | %-15s \n", "t", "c(t)", "s(t)");
    printf("--------------------------------------------\n");
    for( int t = 1; t <= 10; t++ ){
        double real_t = t / 10.0;
        double c_t = adaptive_quadrature( c, 0, real_t, 15 * 1e-4 );
        double s_t = adaptive_quadrature( s, 0, real_t, 15 * 1e-4 );
        printf(" %-10.1f | %-15.10f | %-15.10f \n", real_t, c_t, s_t);    
    }
}

double simpson_rule_third( function<double(double)> f, double a, double b ){
    return ( b - a ) / 6.0 * ( f(a) + 4 * f( (a+b)/2 ) + f(b) );
}

double adaptive_quadrature( function<double(double)> f, double a, double b, double tol, double actual_value, bool root_call ){
    double parent = simpson_rule_third(f, a, b);
    double middle = ( a + b ) / 2;
    double left_child = simpson_rule_third(f, a, middle);
    double right_child = simpson_rule_third(f, middle, b);
    
    if( root_call ){
        cout << "S(a,b) = " << parent << "\nS(a,m) = " << left_child << "\nS(m,b) = " << right_child << endl;
        cout << "Actual value: " << actual_value << endl;
        cout << resetiosflags(ios::fixed);
        cout << "Estimated error: " << abs( parent - left_child - right_child ) / 15.0 << endl;
        cout << "Actual Error: " << abs( actual_value - left_child - right_child ) << endl;
    }

    if( abs( parent - left_child - right_child ) < tol )
        return left_child + right_child;
    else
        return adaptive_quadrature(f, a, middle, tol / 2 ) + adaptive_quadrature(f, middle, b, tol / 2 );
}