//#include "../Section1/gaussianElim.h"
#include<armadillo>
using namespace arma;

#ifdef PROB_8
int main(){
    /*DoubleMatrix augmentedMatrix = {
        {2, -3, 1, 2, 6, 0, -1},
        {1, 1, -1, -1, 4, 1, 0},
        {-1, 1, -3, 0, 5, -3, 0}
    };

    DoubleMatrix solution = gaussianElim( augmentedMatrix );
    cout << setprecision(10);
    cout << "Part A:" << endl;
    printMatrix(solution);
    cout << "-------------------------" << endl;*/
    
    mat A = {
        {2, -3, 1},
        {1, 1, -1},
        {-1, 1, -3}
    };

    //A.print("Matrix A:");

    mat Ai = inv(A);

    //Ai.print("Inverse of A:");

    //b is the right hand side of the equations
    mat b = {
        {2, 6, 0, -1},
        {-1, 4, 1, 0},
        {0, 5, -3, 0}
    };

    mat x = solve(A, b);
    x.print("Part A: Solution using solve():");

    x = Ai * b;
    x.print("Part B: Solution using A^-1 * b:");

    
    return 0;
}
#endif