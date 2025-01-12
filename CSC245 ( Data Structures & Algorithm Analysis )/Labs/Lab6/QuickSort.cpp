
#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;
#include "Sort.h"

void FillUp (vector<int>& array, int SIZE);

int main(int argc, char *argv[])
{
        int SIZE = atoi(argv[1]);
	vector<int> array(SIZE);

	FillUp (array, SIZE);	
	quicksort (array);
	return 0;
}

void FillUp (vector<int>& array, int SIZE)
{
	int i = 0;

	while (i < SIZE)
		cin >> array[i++];
}
