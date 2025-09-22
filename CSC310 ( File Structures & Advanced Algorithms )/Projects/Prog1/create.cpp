#include <fstream>
#include <iostream>
#include <vector>
#include "common.h"
#include "create.h"
using namespace std;

int main(int argc, char* argv[]){
    fstream infile ("library.dat", ios::in);
    fstream outfile ("library.out", ios::out | ios::binary );
    vector<string> printingBooks;
    infile.seekg( ios::beg );
    BookRec book; 
    long prevIsbn = 0, isbnHelp = 1;
    int lineCount = 1;
    while( infile >> isbnHelp ){
        book.isbn = isbnHelp;
        readSingleTextBook( book, infile );
        handleBook( printingBooks, book, prevIsbn, lineCount, outfile, isbnHelp );
        lineCount++;
    }
    infile.close();
    outfile.close();
    cout << endl;
    for( int x = 0; x < printingBooks.size(); x++ )
       cout << printingBooks[x];
}

void readSingleTextBook( BookRec & book, fstream & infile ){
    char ch;
    infile.get(ch); //handles pipe after isbn
    infile.getline ( book.name, 25, '|' );
    infile.getline ( book.author, 25, '|' );
    infile >> book.onhand;
    infile.get(ch); //handles pipe after onhand
    infile >> book.price;
    infile.get(ch); //handles pipe after price
    infile.getline ( book.type, 25, '\n' );
}

void handleBook( vector<string> & printingBooks, BookRec book, long & prevIsbn, int lineCount, fstream & outfile, long isbnHelp ){
    EntryErrors errors = computeErrors(book,prevIsbn, lineCount, isbnHelp );
    if( ! ( errors.negIsbn || errors.negOH || errors.negP ) ){//shoutout demorgans principle
        printingBooks.push_back( bookToString( book ) );
        outfile.write( (char *) &book, sizeof(BookRec) );
    }
}

EntryErrors computeErrors( BookRec book, long & prevIsbn, int lineCount, long isbnHelp ){
    EntryErrors errors{ false, false, false };
    bool isbnOOS = false;
    string errorString;
    if( isbnHelp < 1 ){
        cerr << "> Illegal isbn number encountered on line " 
        << lineCount << " of data file - record ignored." << endl;
        errors.negIsbn = true;
    }
    if( book.isbn <= prevIsbn && book.isbn >= 1 ){
        cerr << "> Isbn number out of sequence on line " << lineCount
        << " of data file." << endl;
        cout << bookToString( book );
        isbnOOS = true;
    }
    if( book.onhand < 0 ){
        cerr << "> Negative amount onhand on line " << lineCount
        << " of data file - record ignored." << endl;
        cout << bookToString( book );
        errors.negOH = true;
    }
    if( book.price < 0 ){
        cerr <<  "> Negative price on line " << lineCount
        << " of data file - record ignored." << endl;
        cout << bookToString( book );
        errors.negP = true;
    }
    if( ! ( errors.negIsbn || errors.negOH || errors.negP || isbnOOS ) )
        prevIsbn = book.isbn;
    return errors;

}