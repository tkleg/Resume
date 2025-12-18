#include<iostream>
#include<armadillo>
using namespace arma;
using namespace std;

#ifdef PROB_1
int main(){
    mat A = {
        {1, 0, 0},
        {2, 1, 0},
        {-1, 0, 1}
    };
    mat B = {
        {2, 3, -1},
        {0, -2, 1},
        {0, 0, 3}
    };
    vec S = {2, -1, 1};
    mat C = A * B;
    vec X = solve(C, S);
    X.print("Solution X:");
    return 0;
}
#endif