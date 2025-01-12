#include<string>
#include<cstdlib>
#include<climits>
#include<iostream>
#include<fstream>
#include<vector>
#include<stack>
#include"queue.h"
#include"graph.h"
#include<set>
using namespace std;

enum AlgorithmType{ dijkstra, prim };

struct VertNode{
	string name;
	bool mark;
	int dist;
	string prev;
};

const string invCommandLine = "The command line inputs were not correct.\nPlease try again.";
const string invFileName = "The File Name included is incorrect.\nPlease try again.";
const string clearScreen = "\033[2J\033[1;1H";
const int NO_EDGE = 0;

void getFileName( int argc, char* argv[] );
//preconditions: none
//postconditions: terminates the program and prints a message if the string at argv[1] is not a nonempty file or argc != 2

vector<string> buildGraph( Graph<string> & graph, int argc, char* argv[] );//returns a vector with the names of all the vertices
//preconditions: graph has been declared and getFileName has run, confirming that the fileName given at argv[1] is a valid nonempty file
//postcondition: graph is filled with vertexes and edges according to the text within the file whos name is stored in argv[1]. A vector containing all of the vertex names in the graph is returned

void printVerts( vector<string> vertList );
//preconditions: vertList is filled with all of the vertices in the file passed in the command line at argv[1]
//postconditions: all the elements in vertList are printed in a formatted manner so that there is space between each vertex and a new line starts after 3 vertices have been printed

vector<VertNode> getNodes( vector<string> vertList );
//preconditions: vertList has been filled with the vertices of the graph
//postconditions: a vector of VertNodes is returned. Every VertNode in the list has a name from vertList. For every VertNode the mark is false, dist is INT_MAX, and prev is an empty string

int getStartVert( vector<string> vertList );
//preconditions: nodes has been filled and all the names are vertices of the graph
//postcondition: The index of a user entered string within vertList is returned. The method does not stop until the user enters a vertex wihtin the vector

int indexOf( vector<string> vertList, string vert );
//pre-conditions: vertList has been filled with the vertices of the graph
//post-conditions: if vert exists in vertList, the index of vert within vertList is returned. If vert does not exist in vertList, -1 is returned

int smallNonMarkDistInd( vector<VertNode> nodes );
//pre-conditions: nodes is filled with the vertices of the graph. At least VertNode's mark within nodes is false
//post-conditions: the index of the VertNode that is unmarked and has the smallest dist is returned

void sortVertexes( vector<VertNode> & nodes );
//pre-conditions: nodes has been run through either a dijkstra or prim algorithm
//post-conditions: nodes is sorted according to the dist in each VertNode

void printResults( vector<VertNode> nodes );
//pre-conditions: nodes has been run through either a dijkstra or prim algoritm
//post-conditions: all VertNodes within nodes are printed in an organized manner

set< vector<string> > getCycles( Graph<string> graph, vector<string> vertList );
//pre-conditions: graph is filled with all the edges and vertices of the graph and vertList is filled with all the vertices of the graph
//post-conditions: a set containing every cycle in the graph is returned. Elements of the set are formatted so that if the cycle goes A to B to C to A, vector will be {A, B, B, C, C, A}. This is done to allow for easy printing

void dfs( int index, bool marked[], Graph<string> graph,  vector<string> vertList, stack<string> & callStack, set< vector<string> > & allCycles );
//pre-conditions: 0 <= index < vertList.size(). graph is filled with all vertices and edges of the graph. vertList is filled with all the vertices of the graph. If it is a non-recursive call, marked must be all false and callStack must be empty.
//post-conditions: all cycles in the graph that can be found with vertList[index] as the start of a depth-first-search are added to allCycles

void cycleFound( stack<string> callStack, string startEnd, set< vector<string> > & allCycles );
//pre-conditions: callStack is filled with a cycle who's start and End is startEnd
//post-conditions: A cycle from callStack is added to allCycles. It is formatted so that the if stack is {A, B, C, D, E} and startEnd is C, { C, D, D, E, E, C }

void printCycles( set< vector<string> > cycles );
//pre-conditions: cycles has been filled with every cycle that exists in the graph
//post-condition: if cycles.size() == 0 a message is prtined stating that the graph has no cycles. Otherwise is prints every cycle within cycles in a neat/formatted manner

void Algorithm( Graph<string> graph, vector<string> vertList, int startInd, vector<VertNode> nodes, AlgorithmType alg );
//pre-conditions: graph is filled with all the edges and vertices of the graph. vertList is filled with all the vertices of the graph, 0 <= startInd < vertList.size(), nodes is filled with a VertNode for every vertex in the graph and the mark are false, dists are 0, and prevs are "", and alg must be either equal to dijkstra or prim (enum values 0 and 1 respectively)
//post-conditions: if alg == dijkstra (enum value) then nodes is processed through a dijkstra algorithm with the starting vertex being the vertex at nodes[startInd]. Else if alg == prim (enum value), then nodes is process through a prim algorithm with the starting vertex being the vertex at nodes[startInd]. After this, nodes is sorted according to the dist of every VertNode within. Then, if alg == prim, a header from Prim's Algorithm is printed. Finally, a summary table of either Dijkstra's algorithm or Prim's algorithm is printed

int main( int argc, char* argv[] ){
	Graph<string> graph(50);
	vector<string> vertList = buildGraph( graph, argc, argv );
	printVerts( vertList );
	vector<VertNode> nodes = getNodes( vertList );
	int startInd = getStartVert( vertList );//used because this is found in dijkstra algorithm call and I want it to be used in prim algorithm while keeping Algorithm a void return method
	Algorithm( graph, vertList, startInd, nodes, dijkstra );
	Algorithm( graph, vertList, startInd, nodes, prim );
	printCycles( getCycles( graph, vertList ) );
}

void getFileName( int argc, char* argv[] ){
	if( argc != 2 ){
		cout << invCommandLine << endl;
		exit(0);
	}
	ifstream testFile( argv[1] );
	string ret;
	char c;
	testFile.get(c);
	if( c == '\0' ){//non-existent and empty file handled
		cout << invFileName << endl;
		exit(0);
	}
	return;
}

vector<string> buildGraph( Graph<string> & graph, int argc, char* argv[] ){
	getFileName( argc, argv );
	ifstream fileIn( argv[1] );
	char c;
	string vert1;
	string vert2;
	string weightS;
	int weight;
	set<string> vertSet;
	
	//This block filles the graphs vertices
	while( ! fileIn.eof() ){
		getline( fileIn, vert1, ';' );
		if( vert1.length() == 0 )//fixes bug that gets a duplicate of the final edge
			break;
		getline( fileIn, vert2, ';' );
		getline( fileIn, weightS, '\n' );
		weight = atoi( weightS.c_str() );
		vertSet.insert( vert1 );
		vertSet.insert( vert2 );
 	}
	set<string>::iterator iter;
	vector<string> vertList;
	for( iter = vertSet.begin(); iter != vertSet.end(); ++iter ){
		graph.AddVertex( *iter );
		vertList.push_back( *iter );
	}
	
	fileIn.clear();
	fileIn.seekg(0);//sets ifstream back to top of file

	//This block fills the graph's edges
	while( ! fileIn.eof() ){
                getline( fileIn, vert1, ';' );
                if( vert1.length() == 0 )//fixes bug that gets a duplicate of the final edge
                        break;
                getline( fileIn, vert2, ';' );
                getline( fileIn, weightS, '\n' );
                weight = atoi( weightS.c_str() );
                graph.AddEdge( vert1, vert2, weight );
        }	
	
	return vertList;
}

void printVerts( vector<string> vertList ){
	cout << clearScreen;
	printf("\t\t^^^^^^^^^^^^^^^^    DIJKSTRA'S ALGORITHM    ^^^^^^^^^^^^^^^^\n\n\t\tA Weighted Graph Has Been Built For These %d Cities : \n", vertList.size() );
	for( int x = 0; x < vertList.size(); x++ ){
		if( x % 3 == 0 )
			cout << "\n\t\t";
		printf("%18s", vertList[x].c_str() );
	}
	cout << "\n\n";	
}

vector<VertNode> getNodes( vector<string> vertList ){
	vector<VertNode> nodes;
	for( int x = 0; x < vertList.size(); x++ ){
		VertNode newNode = { vertList[x], false, INT_MAX, "" };
		nodes.push_back( newNode );
	}
	return nodes;
}

void Algorithm( Graph<string> graph, vector<string> vertList, int startInd, vector<VertNode> nodes, AlgorithmType alg ){
	 nodes[startInd].dist = 0;
	 nodes[startInd].prev = "N/A";
	  //we dont mark the vertex at startInd because it causes smallNonMarkDistInd to have a bug on the first iteration
	 for( int x = 0; x < vertList.size(); x++ ){
	 	Queue<string> adjVerts(50);
	 	int markInd = smallNonMarkDistInd( nodes );//svi==startInd on the first iteration
		if( markInd == -1 ){
			cout << endl << "Critical Error Found in Algorithm. The small index has been found to be -1 in an algorithm iteration." << endl;
			exit(0);
		}
	 	nodes[markInd].mark = true;
	 	graph.GetToVertices( nodes[markInd].name, adjVerts );
	 	while( ! adjVerts.isEmpty() ){
			string vert2name = adjVerts.dequeue();
	        	int adjInd = indexOf( vertList, vert2name );
	               	if( nodes[adjInd].mark )
	 	               continue;
	 		int newWeight = graph.WeightIs( nodes[markInd].name, nodes[adjInd].name );
	 	    	if( alg == dijkstra )
				newWeight += nodes[markInd].dist;
			if( nodes[adjInd].dist > newWeight ){
	 	               nodes[adjInd].dist = newWeight;
	                       nodes[adjInd].prev = nodes[markInd].name;
	                }
	        }
	 }
	sortVertexes( nodes );
	if( alg == prim )
        	cout << "\n\t\t^^^^^^^^^^^^^^^^    PRIM'S ALGORITHM    ^^^^^^^^^^^^^^^^\t\t";
        printResults( nodes );
}

int smallNonMarkDistInd( vector<VertNode> nodes ){
	int minIndex = -1;
	int minDist = INT_MAX;
	for( int x = 0; x < nodes.size(); x++ ){
		if( nodes[x].mark )//ensures no already marked vertex's index is returned
			continue;
		if( nodes[x].dist < minDist ){
			minIndex = x;
			minDist = nodes[x].dist;
		}
	}
	return minIndex;
}
			
int getStartVert( vector<string> vertList ){
	string input;
	while(true){		
		cout << "\t\tPlease input your starting vertex : ";
		getline( cin, input );
		//cin >> input;
		int index = indexOf( vertList, input );
		if( index != -1 )//returns index once a vertex name is entered by user
			return index;
		cout << "\t\tStarting location does not exist..." << endl;
	}
}

int indexOf( vector<string> vertList, string vert ){
	for( int x = 0; x < vertList.size(); x++ )
		if( vertList[x] == vert )
			return x;
	return -1;
}

void sortVertexes( vector<VertNode> & nodes ){
//Selection sort is used
	for( int x = 0; x < nodes.size()-1; x++ ){//the -1 prevents the code from running on the final item
		int minIndex = x;
		for( int y = x + 1; y < nodes.size(); y++ )
			if( nodes[y].dist < nodes[minIndex].dist )
				minIndex = y;
		if( minIndex != x ){
			VertNode temp = nodes[minIndex];
			nodes[minIndex] = nodes[x];
			nodes[x] = temp;
		}
	}
}

void printResults( vector<VertNode> nodes ){
	char NA[] = "N/A";
	char noPath[] = "Not on Path";
	cout << "\n\t\t";
	for( int x = 0 ; x < 64 ; x++ )
		cout << "-";
	printf("\n%28s%24s%24s\n\n", "Vertex", "Distance", "Previous" );
	for( int x = 0 ; x < nodes.size(); x++ ){
		if( nodes[x].dist == INT_MAX )//only true for islands with no path from the start
			printf("%28s%24s%24s\n", nodes[x].name.c_str(), noPath, NA );
		else
			printf("%28s%24d%24s\n", nodes[x].name.c_str(), nodes[x].dist, nodes[x].prev.c_str());
	}
	cout << "\n\t\t";
	for( int x = 0 ; x < 64; x++ )
		cout << "-";
	cout << endl;
}

set< vector<string> > getCycles( Graph<string> graph, vector<string> vertList ){
	set< vector<string> > allCycles;
	stack<string> callStack;
	bool marked[ vertList.size() ];
	fill( marked, marked+vertList.size(), false );
	//note that callStack is empty and marked is all false after each loop iteration due to the design of the dfs function
	for( int x = 0; x < vertList.size(); x++ )
		dfs( x, marked, graph, vertList, callStack, allCycles );
	return allCycles;
}

void dfs( int index, bool marked[], Graph<string> graph,  vector<string> vertList, stack<string> & callStack, set< vector<string> > & allCycles ){
	marked[index] = true;
	callStack.push( vertList[index] );
	for( int x = 0 ; x < vertList.size(); x++ ){
		if( x == index )
			continue;
		if( graph.WeightIs( vertList[index], vertList[x] ) != NO_EDGE ){
			if( marked[x] )
				cycleFound( callStack, vertList[x], allCycles );
			else	
				dfs( x, marked, graph, vertList, callStack, allCycles );
		}
	}
	marked[index] = false;
	callStack.pop();
}

void cycleFound( stack<string> callStack, string startEnd, set< vector<string> > & allCycles ){
	//startEnd is the vertex that is at the start and end of the cycle
	vector<string> tempList;
        while( callStack.top() != startEnd ){
                tempList.push_back( callStack.top() );
                callStack.pop();
        }
	//if callStack = { A, B, C } and startEnd = A, tempList = { C, B }	
        vector<string> cycle;
        cycle.push_back( startEnd );
	for( int x = tempList.size()-1; x >= 0 ; x--)
		for( int y = 0; y < 2; y++ )
			cycle.push_back( tempList[x] );
        cycle.push_back( startEnd );
        allCycles.insert( cycle );
}

void printCycles( set< vector<string> > cycles ){
	char noCycles[] = "The graph contains no cycles\n";
	if( cycles.size() == 0 ){
		printf("%61s", noCycles );
		return;
	}
	set< vector<string> >::iterator i;
	int counter = 0;
	char s1[] = "The graph contains ";
        char s2[] = " cycles";
        char s3[] = "Cycle #";
        char s4[] = " is :";
        char s5[] = "Vertex";
        char s6[] = "To";
        char s7[] = "->";
        for( i = cycles.begin(); i != cycles.end(); ++i ){
		vector<string> cycle = *i;
                printf("%53s%d%s\n\n%27s%d%s\n%34s%36s\n", s1 , cycles.size(), s2, s3, (counter+1), s4, s5, s6 );
		//Note that every cycle in cycles will have an even size due to the design of cycleFound
		for( int x = 0 ; x < cycle.size(); x += 2 )
			printf("%33s%18s%22s\n", cycle[x].c_str(), s7, cycle[x+1].c_str() );
		cout << "\n\t\t";
        	for( int x = 0 ; x < 64; x++ )
                	cout << "-";
        	cout << endl;
		counter++;
	}
}
