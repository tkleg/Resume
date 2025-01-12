#include <iostream>

using namespace std;

bool identicalValues( double *ptr1, double *ptr2 );

bool identicalAddresses( double *ptr1, double *ptr2 );

int main(){

	double *ptr1 = new double;
	*ptr1 = 5;
	double *ptr2 = new double;
	*ptr2 = 5;
	
	cout << "The two pointers do ";
	if( ! (identicalValues( ptr1, ptr2 )) )
		cout << "not ";
	cout << "have identical values" << endl;

	cout << "The two pointers do ";
	if ( ! ( identicalAddresses( ptr1, ptr2 ) ) )
		cout << "not ";
	cout << "point to the same variable" << endl;

}

bool identicalValues( double *ptr1, double *ptr2 ){
	return *ptr1 == *ptr2;
}

bool identicalAddresses( double *ptr1, double *ptr2 ){
	return ptr1 == ptr2;
}
