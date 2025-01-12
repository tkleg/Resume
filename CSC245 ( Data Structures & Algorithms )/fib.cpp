#include<iostream>
#include<vector>
#include<cstdlib>
using namespace std;
int fib( int num );


int main(){
	cout << fib(10);
	return 0;
}

int fib( int num ){
	if( num == 0 )
		return 0;
	if( num == 1 )
		return 1;
	return fib( num - 1 ) + fib( num - 2 );
}
