#include <vector>
#include <utility>
using namespace std;

long double lagrange( vector< pair<long double, long double> > data, long double x);
long double lagrangeDerivative( vector< pair<long double, long double> > data, long double x );
long double lFunction( vector<long double> vals, long double x, int k );
long double lFunctionDerivative( vector<long double> vals, long double x, int k );