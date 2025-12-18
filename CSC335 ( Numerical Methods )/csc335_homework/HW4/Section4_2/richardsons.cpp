#include "richardsons.h"

#ifdef RICHARDSONS
int main() {
    cout << "Enter n: ";
    int n; 
    cin >> n;
    cout << "Testing Richardson Extrapolation:" << endl;
    function<double(double)> f = [](double x) { return x * cos(x); };
    cout << "Approximate derivative of f(x) = x*cos(x) at x=1 with h=0.2 and n=3:" << endl;
    cout << setprecision(10);
    double result = richardson(f, 1.0, 0.2, n, true);
    cout << "Result: " << result << endl;
    return 0;
}
#endif

double richardson( function<double(double)> f, double x, double h, int n, bool print_table ){
    vector<vector<double>> N(n, vector<double>(n, 0.0));

    for(int i = 0; i < n; i++){
        double diff = h / pow(2, i);
        N[i][0] = (f(x + diff) - f(x - diff)) / (2 * diff);
    }

    for(int j = 1; j < n; j++)
        for(int i = j; i < n; i++)
            N[i][j] = N[i][j-1] + (N[i][j-1] - N[i-1][j-1]) / (pow(4, j) - 1);

    if(print_table){
        cout << "Richardson Extrapolation Table:" << endl;
        for( int i = 0; i < n; i++ ){
            for( int j = 0; j <= i; j++ )
                cout << setw(15) << N[i][j] << " ";
            cout << endl;
        }
    }

    return N.back().back();
}