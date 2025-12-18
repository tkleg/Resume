#ifdef Q2D

#include<vector>
#include<functional>
#include<iostream>
#include<armadillo>
#include<cmath>
using namespace std;
using namespace arma;

typedef function<double(double, double, double)> func3d;
typedef vector< vector< func3d > > func3d_mat;

mat Jacobian_eval( func3d_mat J, vec x );

int main(){
    vector<func3d> funcs = {
        [](double x1, double x2, double x3){ return x1 + cos(x1*x2*x3) - 1; },
        [](double x1, double x2, double x3){ return pow(1 - x1, 0.25) + x2 + 0.05 * x3 * x3 - 0.15 * x3 - 1; },
        [](double x1, double x2, double x3){ return -x1*x1 - 0.1 * x2 * x2 + 0.01 * x2 + x3 - 1; }
    };
    func3d g = [funcs](double x1, double x2, double x3){
        double x = 0;
        for(int i = 0; i < funcs.size(); i++)
            x += pow( funcs[i](x1, x2, x3), 2 );
        return x;
    };
    func3d_mat Jacobian = {
        {
            [](double x1, double x2, double x3){ return 1 - x2 * x3 * sin(x1*x2*x3); },
            [](double x1, double x2, double x3){ return -x1 * x3 * sin(x1*x2*x3); },
            [](double x1, double x2, double x3){ return -x1 * x2 * sin(x1*x2*x3); }
        },
        {
            [](double x1, double x2, double x3){ return -0.25 / pow(1-x1,0.75); },
            [](double x1, double x2, double x3){ return 1; },
            [](double x1, double x2, double x3){ return 0.1 * x3 - 0.15; }
        },
        {
            [](double x1, double x2, double x3){ return -2 * x1; },
            [](double x1, double x2, double x3){ return -0.2 * x2 + 0.01; },
            [](double x1, double x2, double x3){ return 1; }
        }
    };
    int n_vars = 3;
    int k = 1;
    int maxIter = 1e5;
    vec x = {0, 0, 0};// initial guess
    double tol = 0.05;
    while(k <= maxIter){
        double g1 = g( x(0), x(1), x(2) );
        mat J_eval = Jacobian_eval( Jacobian, x );
        vec F( n_vars );
        for(int i = 0; i < n_vars; i++)
            F(i) = funcs[i]( x(0), x(1), x(2) );
        vec z = 2 * J_eval.t() * F;
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
            cout << "Solution: " << x.t();
            break;
        }
        k++;
        if( k > maxIter ){
            cout << "Reached maximum iterations." << endl;
            cout << "Current approximation: " << x.t();
        }

    }
    return 0;
}

#endif

mat Jacobian_eval( func3d_mat J, vec x ){
    int n = J.size();
    int m = J[0].size();
    mat J_eval(n, m);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            J_eval(i,j) = J[i][j]( x(0), x(1), x(2) );
    return J_eval;
}