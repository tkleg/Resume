#include<iostream>
#include<armadillo>
using namespace arma;
using namespace std;

#ifdef PROB_1
int main(){
    mat A = {
        {1, 2, 0},
        {2, 1, -1},
        {3, 1, 1}
    };
    cout << "Determinant of A: " << det(A) << endl;

    mat B = {
        {4, 0, 1},
        {2, 1, 0},
        {2, 2, 3}
    };
    cout << "Determinant of B: " << det(B) << endl;

    mat C = {
        {1, 1, -1, 1},
        {1, 2, -4, -2},
        {2, 1, 1, 5},
        {-1, 0, -2, -4}
    };
    cout << "Determinant of C: " << det(C) << endl;

    mat D = {
        {2, 0, 1, 2},
        {1, 1, 0, 2},
        {2, -1, 3, 1},
        {3, -1, 4, 3}
    };
    cout << "Determinant of D: " << det(D) << endl;
    
    return 0;
}
#endif