#include<iostream>
#include<armadillo>
#include<cmath>
#include<iomanip>
#include<functional>
#include<vector>
using namespace std;
using namespace arma;

typedef function<double(double, double)> Func;
typedef vector<vector<Func>> Jacobian;

int main(){
    Func g1 = [](double x1, double x2) { return log( (x1*x1 + x2*x2 ) / ( 2 * M_PI ) ) - sin( x1 * x2 ); };
    Func g2 = [](double x1, double x2) { return exp(x1 - x2) + cos(x1 * x2); };
    Jacobian J = {
        { [](double x1, double x2) { return 2 * x1 / ( x1*x1 + x2*x2 ) - x2 * cos( x1 * x2 ); },
          [](double x1, double x2) { return 2 * x2 / ( x1*x1 + x2*x2 ) - x1 * cos( x1 * x2 ); }
        },
        { [](double x1, double x2) { return exp( x1 - x2 ) - x2 * sin( x1 * x2 ); },
          [](double x1, double x2) { return -exp( x1 - x2 ) - x1 * sin( x1 * x2 );} 
        }
    };
    vec x = {2, 2};
    int max_iter = 10000000;
    int k = 0;
    while( ++k <= max_iter ){
        double x1 = x(0);
        double x2 = x(1);
        mat J_eval(2, 2);
        J_eval(0, 0) = J[0][0](x1, x2);
        J_eval(0, 1) = J[0][1](x1, x2);
        J_eval(1, 0) = J[1][0](x1, x2);
        J_eval(1, 1) = J[1][1](x1, x2);

        vec F(2);
        F(0) = g1(x1, x2);
        F(1) = g2(x1, x2);
        J_eval.print("Jacobian:");
        F.print("Function values:");
        vec y = solve(J_eval, -F);
        x += y;
        x.print("New approximation:");
        if( norm(y, 2) < 1e-6 ){
            cout << "Converged in " << k << " iterations." << endl;
            cout << fixed << setprecision(6) << "Solution: x1 = " << x(0) << ", x2 = " << x(1) << endl;
            break;
        }
    }
    return 0;
}