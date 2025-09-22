#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
vector<vector<int> > floydWarshall(vector<vector<int> > dist); 
void printMe(vector<vector<int> > shortestPaths);
int findMin(int dist1, int dist2);

int main() {
    vector<vector<int> > dist = {
        {0, 3, 8, INT_MAX, -4},
        {INT_MAX, 0, INT_MAX, 1, 7},
        {INT_MAX, 4, 0, INT_MAX, INT_MAX},
        {2, INT_MAX, -5, 0, INT_MAX},
        {INT_MAX, INT_MAX, INT_MAX, 6, 0}
    };

    vector<vector<int> > shortestPaths = floydWarshall(dist);

    return 0;
}

vector<vector<int> > floydWarshall(vector<vector<int> > dist) {
    int numVertices = dist.size();
    cout << "numVertices = " << numVertices << endl;

    cout << "k = " << 0 << endl;
    printMe(dist);
    for (int k = 0; k < numVertices; ++k) {
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                 if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    dist[i][j] = findMin(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
     cout << "k = " << k+1 << endl;
     printMe(dist);
   }

   return dist;
}


void printMe(vector<vector<int> > shortestPaths)
{
    for (int i = 0; i < shortestPaths.size();  i++) {
       for (int j = 0; j < shortestPaths[i].size();  j++) {
            if (i == j)
                cout << 0 << " ";
            else if (shortestPaths[i][j] == INT_MAX)
                cout << "INF" << " ";
            else
                cout << shortestPaths[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int findMin(int dist1, int dist2)
{
	if (dist1 < dist2)
		return dist1;
	else	
		return dist2;
}
