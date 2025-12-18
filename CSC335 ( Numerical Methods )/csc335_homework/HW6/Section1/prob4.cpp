#include "gaussianElim.h"

#ifdef PROB_4
int main(){
    DoubleMatrix augmentedMatrix = {
        {-1, 4, 1, 8},
        {safeBasicOps(5.0, 3, ROUND, DIVIDE, 2), safeBasicOps(2.0, 3, ROUND, DIVIDE, 2), safeBasicOps(2.0, 3, ROUND, DIVIDE, 2), 1},
        {2, 1, 4, 11}
    };
    cout << "Augmented Matrix:" << endl;
    printMatrix(augmentedMatrix);
    DoubleMatrix solution = gaussianElim(augmentedMatrix, false, true, ROUND, 2);
    cout << "Solution:" << endl;
    printMatrix(solution);

    return 0;
}
#endif