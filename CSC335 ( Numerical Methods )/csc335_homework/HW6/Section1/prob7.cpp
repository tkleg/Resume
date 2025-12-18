#include "gaussianElim.h"

#ifdef PROB_7
int main(){
    //Copied wrong matrix from textbook, oops
    /*FloatMatrix augmentedMatrix = {
        {2.0f, 1.0f, -1.0f, 1.0f, -3.0f, 7.0f},
        {1.0f, 0.0f, 2.0f, -1.0f, 1.0f, 2.0f},
        {0.0f, -2.0f, -1.0f, 1.0f, -1.0f, -5.0f},
        {3.0f, 1.0f, -4.0f, 0.0f, 5.0f, 6.0f},
        {1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 3.0f}
    };*/

    FloatMatrix augmentedMatrix = {
        {1.0f, 1.0f/2.0f, 1.0f/3.0f, 1.0f/4.0f, 1.0f/6},
        {1.0f/2.0f, 1.0f/3.0f, 1.0f/4.0f, 1.0f/5.0f, 1.0f/7.0f},
        {1.0f/3.0f, 1.0f/4.0f, 1.0f/5.0f, 1.0f/6.0f, 1.0f/8.0f},
        {1.0f/4.0f, 1.0f/5.0f, 1.0f/6.0f, 1.0f/7.0f, 1.0f/9.0f}
    };
    
    vector<float> solution = gaussianElim( augmentedMatrix );
    cout << setprecision(16);
    cout << "Solution Vector Float:" << endl;
    for( float val : solution )
        cout << val << endl;
    
    DoubleMatrix augmentedMatrixD = {
        {1.0, 1.0/2, 1.0/3, 1.0/4, 1.0/6},
        {1.0/2, 1.0/3, 1.0/4, 1.0/5, 1.0/7},
        {1.0/3, 1.0/4, 1.0/5, 1.0/6, 1.0/8},
        {1.0/4, 1.0/5, 1.0/6, 1.0/7, 1.0/9}
    };
    DoubleMatrix solutionD = gaussianElim( augmentedMatrixD );
    cout << setprecision(16);
    cout << "\nSolution Vector Double:" << endl;
    printMatrix(solutionD);

    return 0;
}

#endif // PROB_7