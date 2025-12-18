#include<iostream>
#include<armadillo>
#include<cmath>
#include<optional>
#include<iomanip>
using namespace std;
using namespace arma;

#ifdef PROB_8A
int main(){
    mat A = {
        {3.9, 1.5},
        {6.8, -2.9}
    };
    vec x = {1, 1};
    vec b = {5.4, 3.9};
    vec x_approx = {0.98, 1.02};

    cout << fixed << setprecision(10);
    
    double dist_inf_1 = max( abs( x - x_approx ) );
    cout << "Infinity-norm distance for x - x_approx: " << dist_inf_1 << endl;

    double dist_inf_2 = max( abs( A * x_approx - b ) );
    cout << "Infinity-norm distance for A*x_approx - b: " << dist_inf_2 << endl;


    return 0;
}
#endif