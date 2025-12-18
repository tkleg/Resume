#include "../Section1/gaussianElim.h"

#ifdef PROB_13
int main(){
    DoubleMatrix A = {
        {0.03, 58.9, 59.2},
        {5.31, -6.1, 47}
    };

    vector<double> solution = gaussianElimPartialPivot(A, false, false, CHOP, 3);
    cout << "Chopped Solution (3 sig figs):" << endl;
    for( double val : solution )
        cout << val << endl;

    return 0;
}
#endif