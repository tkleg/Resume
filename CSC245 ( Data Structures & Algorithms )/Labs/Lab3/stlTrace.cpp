
#include <deque>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int main()
{
	deque<int>	d(2);
        d[0] = 8;	d[1] = 25;
        d.push_front(-8);       d.push_back(14);
        d.push_front(-2);       d.push_back(-4);
	d.push_front(-8);	d.push_back(14);
	cout << endl << "Size is " << d.size() << endl;
	for (int i=0;  i < d.size(); i++)
		cout << d[i] << " ";
        cout << endl;

        int list[] = {-2, -6, -4, -1, -7};
        vector<int> v(list, list+5);

        for (int i=0;  i < v.size();  i++)     
           v[i] = list[i];

        sort(v.begin(), v.end());
        for (int i = 0; i < v.size();  i++)
           cout << v[i] << " ";
        cout << endl;	

        bool foundIt = binary_search(v.begin(), v.end(), -2);
        if (foundIt)
          cout << "Found the -2" << endl;	
        return 0;
}
