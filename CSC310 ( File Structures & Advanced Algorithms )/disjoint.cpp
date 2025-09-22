#include <iostream>
#include <iomanip>
using namespace std;

class DisjSets {
  public :
     DisjSets (int numelements);
     ~DisjSets();
     int find (int x);
     int compress (int x);
     void unionSets (int root1, int root2);
     void printSet();
  protected :
     int *a;
     int n;
};

DisjSets::DisjSets(int numelements)
{
  int i;

  n = numelements;
  a = new int[n];
  for (i = 0;  i < n;  i++)
       a[i] = -1;
}

DisjSets::~DisjSets()
{
  delete a;
}

void DisjSets::unionSets(int root1, int root2)
{
  a[find(root2)] = find(root1);
}

int DisjSets::find(int x)
{
  if (a[x] < 0)
     return x;
  else
     return find(a[x]);
}

int DisjSets::compress(int x)
{
  if (a[x] < 0 )
      return x;

  a[x] = compress(a[x]);

  return a[x];
}

void DisjSets::printSet(){
	cout << setfill('-') << setw(10) << "" << endl;
	for( int x = 0; x < n; x++ )
		cout << x << ": " << a[x] << endl;
        cout << setfill('-') << setw(10) << "" << endl;
}

int main(){
	DisjSets set(17);
	int x, y;
	while( true ){
		cin >> x >> y;
		if( x < 0 )
			set.compress(y);
		else
			set.unionSets(x, y);
		set.printSet();
	}
	return 0;
}
