
#include <iostream>
#include <vector>
#include <map>
using namespace std;

int fib_tabulation(int n);
int fib_memoization(int n, map<int, int>& memo);

// Fib Sequence:  1 1 2 3 5 8 13 21 34 55
int main() {
    //Checks for Tabulation 
    cout << fib_tabulation(1) << endl;
    cout << fib_tabulation(5) << endl;
    cout << fib_tabulation(10) << endl;
    cout << fib_tabulation(15) << endl;

    //Checks for Memoization 
    map<int, int> memo;
    cout << fib_memoization(1, memo) << endl;
    cout << fib_memoization(5, memo) << endl;
    cout << fib_memoization(10, memo) << endl;
    cout << fib_memoization(15, memo) << endl;
}

//Tabulation Approach to Dynamic Programming
int fib_tabulation(int n) {
    if (n <= 1) {
        return n;
    }
    vector<int> fib_table(n + 1);
    fib_table[0] = 0;
    fib_table[1] = 1;
    for (int i = 2; i <= n; ++i) {
        fib_table[i] = fib_table[i - 1] + fib_table[i - 2];
    }
    return fib_table[n];
}

//Memoization Approach to Dynamic Programming
int fib_memoization(int n, map<int, int>& memo) {
    if (n <= 1) {
        return n;
    }
    memo[n] = fib_memoization(n - 1, memo) + fib_memoization(n - 2, memo);
    return memo[n];
}
