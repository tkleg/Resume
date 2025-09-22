#include <fstream>
#include <iostream>
#include <map>
#include "common.h"
#include "update.h"
using namespace std;

int main(int argc, char* argv[]){
    string copyCommand ="cp " + string(argv[1]) + " copy.out";
    system(copyCommand.c_str());
    map<unsigned int, long> isbnLocations = fillMapFromBinary();
    processTransactions( isbnLocations, argv[2] );
    writeFinalMasterBinary( isbnLocations, argv[3] );
    readAndPrintBinaryBooks(argv[3]);
    system("rm copy.out");
}

void writeFinalMasterBinary( map<unsigned int, long> isbnLocations, string masterOutName ){
    fstream binfile("copy.out", ios::in | ios::binary);
    fstream finalOut(masterOutName, ios::out | ios::binary);
    BookRec book;
    map<unsigned int, long>:: iterator it = isbnLocations.begin();
    while( it != isbnLocations.end() ){
        binfile.seekg(it -> second);
        binfile.read( (char *) &book, sizeof(book) );
        finalOut.write( (char *) &book, sizeof(book) );
        ++it;
    }
    binfile.close();
    finalOut.close();
}


map<unsigned int, long> fillMapFromBinary(){
    BookRec book;
    map<unsigned int, long> isbnLocations;
    fstream binfile("copy.out", ios::in | ios::binary);
    binfile.seekg(0);
    long bookSize = sizeof(BookRec);
    while( binfile.read( (char *) &book, sizeof(BookRec) ) ){
        //-sizeof(BookRec) necessary since the first book was not read, the last was read twice, and the isbns were all off
        isbnLocations[book.isbn] = binfile.tellg()-bookSize;
    }
    binfile.close();
    return isbnLocations;
}

void processTransactions( map<unsigned int, long> & isbnLocations, string transactionFileName ){
    TransactionRec transact;
    fstream binfile(transactionFileName, ios::in | ios::binary);
    system("cp ERRORS oldERRORS");
    fstream errorOut("ERRORS", ios::out );
    fstream masterOut("copy.out", ios::in | ios::out );
    masterOut.seekg(0);
    errorOut.seekg(0);
    binfile.seekg(0);
    int transactionNumber = 1;
    while( binfile.read( (char *) &transact, sizeof(transact) ) ){
        switch( transact.ToDo ){
            case TransactionType::Add:
                addRecord( transact, isbnLocations, masterOut, errorOut, transactionNumber );
                break;
            case TransactionType::Delete:
                deleteRecord( transact.B.isbn, isbnLocations, errorOut, transactionNumber);
                break;
            case TransactionType::ChangeOnhand:
                changeOnHand( transact.B, isbnLocations, errorOut, masterOut, transactionNumber );
                break;
            case TransactionType::ChangePrice:
                changePrice( transact.B, isbnLocations, errorOut, masterOut, transactionNumber );
                break;
        }
        transactionNumber++;
    }
}

void changePrice( BookRec transactBook, map<unsigned int, long> isbnLocations, fstream & errorOut, fstream & masterOut, int transactionNumber ){
    BookRec b;
    string errorMessage;
    if( isbnLocations.find(transactBook.isbn) == isbnLocations.end() ){
        errorMessage =  "Error in transaction number " + to_string(transactionNumber) + ": cannot change price---no such key ";
        errorMessage += isbnToString(transactBook.isbn) + "\n";
        cout << errorMessage;
        errorOut << errorMessage;
    }else{
        masterOut.seekg( isbnLocations[transactBook.isbn] );
        masterOut.read( (char *) &b, sizeof(b) );
        b.price = transactBook.price;
        masterOut.seekg( isbnLocations[b.isbn] );
        masterOut.write( (char *) &b, sizeof(b) );
    }
}


void changeOnHand( BookRec transactBook, map<unsigned int, long> isbnLocations, fstream & errorOut, fstream & masterOut, int transactionNumber ){
    BookRec b;
    string errorMessage;
    if( isbnLocations.find(transactBook.isbn) == isbnLocations.end() ){
        errorMessage = "Error in transaction number " + to_string(transactionNumber) + ": cannot change count---no such key ";
        errorMessage += isbnToString(transactBook.isbn) + "\n";
        cout << errorMessage;
        errorOut << errorMessage;
    }else{
        masterOut.seekg( isbnLocations[transactBook.isbn] );
        masterOut.read( (char *) &b, sizeof(b) );
        int newOnHand = b.onhand + transactBook.onhand;
        if( newOnHand < 0 ){
            errorMessage = "Error in transaction number " + to_string(transactionNumber) + ": count = " + to_string(newOnHand) + " for key "; 
            errorMessage += isbnToString(b.isbn) + "\n";
            cout << errorMessage;
            errorOut << errorMessage;
            newOnHand = 0;
        }
        b.onhand = newOnHand;
        masterOut.seekg( isbnLocations[b.isbn] );
        masterOut.write( (char *) &b, sizeof(b) );
    }

}

void deleteRecord( long isbnToDelete, map<unsigned int, long> & isbnLocations, fstream & errorOut, int transactionNumber ){
    string errorMessage;
    if( isbnLocations.find(isbnToDelete) == isbnLocations.end() ){
        errorMessage = "Error in transaction number " + to_string(transactionNumber) + ": cannot delete---no such key ";
        errorMessage += isbnToString(isbnToDelete) + "\n";
        errorOut << errorMessage;
        cout << errorMessage;
    }else
        isbnLocations.erase(isbnToDelete);
}

void addRecord( TransactionRec transact, map<unsigned int, long> & isbnLocations, fstream & masterOut, fstream & errorOut, int transactionNumber ){
    string errorMessage;
    if( isbnLocations.find(transact.B.isbn) == isbnLocations.end() ){
        long recordLocation = 0;
        masterOut.seekg(0, ios::end);
        isbnLocations[transact.B.isbn] = masterOut.tellg();
        masterOut.write( (char *) &transact.B, sizeof(transact.B) );
    }else{
        errorMessage = "Error in transaction number " + to_string(transactionNumber) + ": cannot add---duplicate key ";
        errorMessage += isbnToString(transact.B.isbn) + "\n";
        errorOut << errorMessage;
        cout << errorMessage;
    }
}

void readAndPrintBinaryBooks(string fileName){
    BookRec book;
    fstream binfile(fileName, ios::in | ios::binary);
    binfile.seekg(0, ios::beg);
    while( binfile.read( (char *) &book, sizeof(BookRec) ) )
    	cout << bookToString(book);
}
