#include<iostream>
#include<armadillo>
#include<cmath>
using namespace std;
using namespace arma;

#ifdef PROB_1A
int main(){
    vec v = {3, -4, 0, 1.5};
    double norm_inf = abs(v).max();
    double norm_2 = sqrt( dot( v, v ) );
    cout << "Infinity Norm: " << norm_inf << endl;
    cout << "2-Norm: " << norm_2 << endl;
    return 0;
}
#endif