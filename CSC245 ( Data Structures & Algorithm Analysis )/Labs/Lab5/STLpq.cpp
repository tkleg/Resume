#include<iostream>
#include<queue>
using namespace std;

void insertNames( priority_queue<string> & pq );
void printNames( priority_queue<string> pq );

int main(){

	priority_queue<string> pq;
	insertNames( pq );
	printNames( pq );
}

void insertNames( priority_queue<string> & pq ){

	pq.push("Jeremy");
	pq.push("Tim");
	pq.push("Albert");
	pq.push("Bill");
	pq.push("Zane");
	pq.push("Charlie");
	pq.push("Xander");
	pq.push("Yvette");
	pq.push("Quinn");
	pq.push("Ally");
}

void printNames( priority_queue<string> pq ){

	while( ! pq.empty() ){
		cout << pq.top() << ", ";
		pq.pop();
	}
}
