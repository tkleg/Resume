#include <iostream>
using namespace std;

int main(){

	long f1 = 0, f2 = 1, hold;
	cout << f1 << endl;
	int x = 0;
	while( true ){
		hold = f1 + f2;
		f1 = f2;
		f2 = hold;
		cout << x << ": " << f1 << endl;
		x++;
		if( f1 < 0 ){
			break;
		}
	}
	return 0;
}
