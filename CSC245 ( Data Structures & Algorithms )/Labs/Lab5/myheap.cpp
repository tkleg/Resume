#include<iostream>
#include "BinaryHeap.h"
#include "dsexceptions.h"


int main(){

	BinaryHeap<char> PQ;
	char c = 'A';
	for( int x = 0; x < 10; x++ ){
		PQ.insert( c++ );

	}
	PQ.deleteMin();
	cout << "Printing the Left Subtree of the Root of Heap: ";
	PQ.printLeft();
	cout << endl << "The Hiehgt of Heap is: " << PQ.height() << endl;
	cout << "The Maximum Value of Heap Is: " << PQ.findMax() << endl;
}
