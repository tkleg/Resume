#include<iostream>
#include<vector>
#include<functional>
#include<cmath>
#include<iomanip>
using namespace std;

struct Result{
    vector<double> solution;
    int iterations;
};

Result fixed_point_2_var(function<double(double, double)> g1,
    function<double(double, double)> g2, vector<double> initial_guesses,
    double tol, int max_iter);

double inf_norm( vector<double> v1, vector<double> v2 );

int main(){
    cout << fixed << setprecision(8);
    double tol = 1e-5;
    int max_iter = 1000;

    function<double(double, double)> f1 = [](double x1, double x2) { return 
        sqrt(-x1 + 2*x2 - 18); };
    function<double(double, double)> f2 = [](double x1, double x2) { return
        sqrt(25 - pow( x1 - 1, 2 ) ) + 6; };
    Result result = fixed_point_2_var(f1, f2, {2, 12}, tol, max_iter);
    cout << "Approximate solution: x1 = " << result.solution[0] << ", x2 = " << result.solution[1] 
        << endl << "Found in " << result.iterations << " iterations." << endl;

    result = fixed_point_2_var([f1](double x1, double x2){ return -f1(x1, x2); }, f2, {-1, 9}, tol, max_iter);
    cout << "Approximate solution: x1 = " << result.solution[0] << ", x2 = " << result.solution[1] 
        << endl << "Found in " << result.iterations << " iterations." << endl;
    return 0;
}

Result fixed_point_2_var(function<double(double, double)> g1,
    function<double(double, double)> g2, vector<double> initial_guesses,
    double tol, int max_iter){
    
    vector<double> current_guesses = initial_guesses;
    vector<double> next_guesses(2);
    int iter = 0;

    while(iter < max_iter){
        iter++;
        next_guesses[0] = g1(current_guesses[0], current_guesses[1]);
        next_guesses[1] = g2(current_guesses[0], current_guesses[1]);

        if(inf_norm(current_guesses, next_guesses) < tol){
            return {next_guesses, iter};
        }
        current_guesses = next_guesses;
        //cout << "Iteration " << iter << ": x1 = " << current_guesses[0]
        //     << ", x2 = " << current_guesses[1] << endl;
    }

    cout << "Maximum iterations reached without convergence." << endl;
    return {next_guesses, -1};
}

double inf_norm( vector<double> v1, vector<double> v2 ){
    double max_diff = NAN;
    for(size_t i = 0; i < v1.size(); i++){
        double diff = abs(v1[i] - v2[i]);
        if(diff > max_diff || isnan(max_diff))
            max_diff = diff;
    }
    return max_diff;
}