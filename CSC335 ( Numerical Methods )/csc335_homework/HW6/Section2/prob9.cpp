#include "../Section1/gaussianElim.h"

#ifdef PROB_9
int main(){
    DoubleMatrix A = {
        {0.03, 58.9, 59.2},
        {5.31, -6.1, 47}
    };

    DoubleMatrix solution = gaussianElim(A);
    cout << "Actual Solution:" << endl;
    for( int x = 0; x < solution.size(); x++ )
        cout << solution[x][0] << endl;

    cout << "\n-------------------------" << endl;

    solution = gaussianElim(A, true, false, CHOP, 3);
    cout << "\nChopped Solution (3 sig figs):" << endl;
    for( int x = 0; x < solution.size(); x++ )
        cout << solution[x][0] << endl;
    return 0;
}
#endif