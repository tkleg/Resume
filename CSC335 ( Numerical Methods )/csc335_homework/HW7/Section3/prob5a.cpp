#include<iostream>
#include<armadillo>
#include<cmath>
#include<vector>
#include<iomanip>
using namespace std;
using namespace arma;

#ifdef PROB_5A

const double tol = 1e-3;
double norm_inf(vec a, vec b);

int main(){
    mat A = {
        {3, -1, 1, 1},
        {3, 6, 2, 0},
        {3, 3, 7, 4}
    };
    /*mat A = {
        {10, -1, 2, 0, 6},
        {-1, 11, -1, 3, 25},
        {2, -1, 10, -1, -11},
        {0, 3, -1, 8, 15}
    };*/
    // Convert to T and C by dividing each row by the diagonal element then setting the diagonal to 0
    for( int i = 0; i < A.n_rows; i++){
        A.row(i) /= -A(i,i);
        A(i,i) = 0;
    }
    mat T = A.cols(0, A.n_cols - 2);
    vec X = zeros<vec>(A.n_rows);
    // C is the negative of the last column of A. The constants were divided by -1 in the loop above so we are undoing that here.
    vec C = -A.col(A.n_cols - 1);
    T.print("T:");
    C.print("C:");
    vec X_new = T * X + C;
    int count = 0;
    while( norm_inf(X_new, X) > tol ){
        count++;
        X = X_new;
        X_new = T * X + C;
    }
    vector<double> solution;
    for( int i = 0; i < X_new.n_elem; i++)
        solution.push_back(X_new(i));

    cout << fixed << setprecision(7);
    cout << "Solution: ";
    for(int x = 0; x < solution.size()-1; x++)
        cout << solution[x] << ", ";
    cout << solution[solution.size()-1] << endl;
    cout << "Number of iterations: " << count << endl;
    return 0;
}
#endif

double norm_inf(vec a, vec b){
    double max = fabs(a(0) - b(0));
    for( int i = 1; i < a.n_elem; i++){
        double diff = fabs(a(i) - b(i));
        if( diff > max )
            max = diff;
    }
    return max;
}