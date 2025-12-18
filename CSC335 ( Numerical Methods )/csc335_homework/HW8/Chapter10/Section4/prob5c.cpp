#ifdef Q5C

#include<vector>
#include<functional>
#include<iostream>
#include<armadillo>
#include<cmath>
#include<iomanip>
using namespace std;
using namespace arma;

typedef function<double(double, double, double)> func3d;
typedef vector< func3d > gradient;

int main(){
    func3d g = [](double x1, double x2, double x3){
        return x1*x1 + 2*x2*x2 + x3*x3 - 2*x1*x2 + 2*x1 - 2.5*x2 - x3 + 2;
    };
    gradient grad_g = {
        [](double x1, double x2, double x3){
            return 2*(x1 - x2 + 1);
        },
        [](double x1, double x2, double x3){
            return (8*x2 - 4*x1 - 5) / 2;
        },
        [](double x1, double x2, double x3){
            return 2*x3 - 1;
        }
    };
    int n_vars = 3;
    int k = 1;
    int maxIter = 1e5;
    vec x = {0, 0, 0};// initial guess
    double tol = 0.005;
    while(k <= maxIter){
        double g1 = g( x(0), x(1), x(2) );
        vec z = {
            grad_g[0]( x(0), x(1), x(2) ),
            grad_g[1]( x(0), x(1), x(2) ),
            grad_g[2]( x(0), x(1), x(2) )
        };
        double z0 = norm( z, 2 );
        if( z0 == 0 ){
            cout << "Zero gradient. Stopping." << endl;
            break;
        }
        z /= z0;
        double alpha1 = 0;
        double alpha3 = 1;
        vec x_minus_alpha3z = x - alpha3 * z;
        double g3 = g( x_minus_alpha3z(0), x_minus_alpha3z(1), x_minus_alpha3z(2) );
        while( g3 >= g1 ){
            alpha3 /= 2;
            x_minus_alpha3z = x - alpha3 * z;
            g3 = g( x_minus_alpha3z(0), x_minus_alpha3z(1), x_minus_alpha3z(2) );
        }
        double alpha2 = alpha3 / 2;
        vec x_minus_alpha2z = x - alpha2 * z;
        double g2 = g( x_minus_alpha2z(0), x_minus_alpha2z(1), x_minus_alpha2z(2) );
        double h1 = (g2 - g1) / alpha2;
        double h2 = (g3 - g2) / (alpha3 - alpha2);
        double h3 = (h2 - h1) / alpha3;
        double alpha0 = 0.5 * (alpha2 - h1 / h3);
        vec x_alpha0_z = x - alpha0 * z;
        double g0 = g( x_alpha0_z(0), x_alpha0_z(1), x_alpha0_z(2) );

        double alpha_picked;
        if( g0 < g3 )
            alpha_picked = alpha0;
        else
            alpha_picked = alpha3;
        x -= alpha_picked * z;
        double g_new = g( x(0), x(1), x(2) );
        if( abs(g_new - g1) < tol ){
            cout << "Converged in " << k << " iterations." << endl;
            break;
        }
        k++;
        if( k > maxIter ){
            cout << "Reached maximum iterations." << endl;
            cout << "Current approximation: " << x.t();
        }

    }
    cout << "Optimal point: " << fixed << setprecision(12);
    for( int i = 0; i < n_vars; i++ )
        cout << x(i) << " ";
    cout << "\nFinal function value: " << g( x(0), x(1), x(2) ) << endl;
    return 0;
}

#endif