#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;

int main() {
    vector<double> v = {1.0, 2.0, 3.0};
    vector<double> v2(v.size());
    transform(v.begin(), v.end(), v2.begin(), [](double x) { return x * 0.5; });
    for (double val : v) {
        cout << val << " ";
    }
    cout << endl;
    for (double val : v2) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}