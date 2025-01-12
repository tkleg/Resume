#include<iostream>
#include "bst.h"
using namespace std;

const int ITEM_NOT_FOUND = 0;

int main(){
	
	BinarySearchTree<int> T( 0 );
	
	T.insert( 6 );
	T.insert( 2 );
	T.insert( 8 );
	T.insert( 1 );
	T.insert( 4 );
	T.insert( 3 );

	T.postOrder();
	cout << endl;

	if( T.isEmpty() )
		cout << "The tree is empty so no height can be computed" << endl;
	else
		cout << T.height() << endl;
	
	if ( T.isBalanced() )
		cout << "It's Balanced!" << endl;
	else
		cout << "It's Not Balanced!." << endl;
	
	T.insert( 9 );
	
	if ( T.isBalanced() )
                cout << "It's Balanced!" << endl;
        else
                cout << "It's Not Balanced!." << endl;
	return 0;	

}
