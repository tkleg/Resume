#include "huffman.h"
#include <iostream>
using namespace std;

HuffmanTree:: HuffmanTree()
	: numChars(0), built(false) {}

void HuffmanTree:: insert(char ch, int weight) {
    HNode newNode = {ch, weight, -1, -1}; 
    built = false;
    nodes.push_back(newNode);
    numChars++;

}

bool HuffmanTree:: inTree(char ch) {
	for( int x = 0; x < nodes.size(); x++ )
		if( nodes[x].ch == ch )
			return true;
	return false;

}

int HuffmanTree:: GetFrequency(char ch) {
	return GetFrequency( lookUp(ch) );
}

int HuffmanTree:: GetFrequency(int i) {
	return nodes[i].weight;
}

int HuffmanTree:: lookUp(char ch) {
	for( int x =0; x < nodes.size(); x++ )
		if( nodes[x] == ch )
			return x;
	return -1;
}

string HuffmanTree:: GetCode(char ch) {
	return GetCode( lookUp( ch ) );
}


string HuffmanTree:: GetCode(int i) {
	if( nodes.size() == 1 )
		return "0";
	if( nodes[i].parent == 0 )
		return "";
	return GetCode((nodes[i].parent)+(char)(nodes[i].chlidType+'0'));
}

void HuffmanTree:: PrintTable() {

}

int HuffmanTree:: numNodes() {
	return nodes.size();
}

void HuffmanTree:: build() {
	for( int x =1; x<numChars; x++ ){
		int small1 = minIndex(-1);
		int small2 = minIndex(-2);
	
		nodes[small1].parent = nodes.size();
		nodes[small2].parent = nodes.size();
		nodes[small1].childType = 0;
		nodes[small2].childType = 1;
		
		int newWeight = nodes[small1].weight + nodes[small2].weight;
		
		HNode newNode = {'\0', newWeight, -1, -1};
		nodes.push_back( newNode );

	}
}

int HuffmanTree:: minIndex( int ignoreIndex ){
	HNode minNode;
	int minIndex;
	int minWeight = -1;
	for( int x = 0; x < nodes.size(); x++ ){
		if( x == ignoreIndex )
			continue;
		if( nodes[x].parent == -1 && 
