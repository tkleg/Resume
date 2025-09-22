
enum TransactionType {Add, Delete, ChangeOnhand, ChangePrice};
struct TransactionRec
{
TransactionType ToDo;
BookRec B;
};

map<unsigned int, long> fillMapFromBinary();
/*
pre-conditions: copy.out is created as a copy of the original master file
post-conditions: a map is returned whos keys are the book isbn's and, 
    whos values are the byte addresses of the books in the binary file*/

void addRecord( TransactionRec transact, map<unsigned int, long> & isbnLocations,  fstream & masterOut, fstream & errorOut, int transactionNumber );
/*
pre-conditions: transact.ToDo = Add, isbnLocations is filled, both fstream parameters point to an open file,
 and transactionNumber is an integer greater than or equal to 1
post-conditions: if the isbn of the book being added is already in isbnLocations, then an error message prints out,
    otherwise the book's isbn number is added as a key to the map so that the books location can be found from its isbn number.*/

void deleteRecord( long isbnToDelete, map<unsigned int, long> & isbnLocations, fstream & errorOut, int transactionNumber );
/*
pre-conditions: errorOut points to a file named ERRORS, isbnLocations has some data, and isbnToDelete is assdigned from a transaction.
post-conditions: is isbnToDelete exists as a key in isbnLocations it is removed from the map. Otherwise an error message is printed.*/

void changeOnHand( BookRec transactBook, map<unsigned int, long> isbnLocations, fstream & errorOut, fstream & masterOut, int transactionNumber );
/*
pre-conditions: transactBook is not-null, isbnLocations has some data, errorOut points to the ERRORS file. masterOut points to copy.out,
    and transactionNumber is an integer greater than or equal to 1.
post-conditions: If the isbn value of the book in transactBook is in the map as a key, the onhand value is added to the associated onhand value saved in copy.out.
    If the new onhand value is negative, the transaction is ignored and an error message is printed. 
    If the isbn number is not present in the map then an error message is printed and the transaction is ignored.
*/

void changePrice( BookRec transactBook, map<unsigned int, long> isbnLocations, fstream & errorOut, fstream & masterOut, int transactionNumber );
/*
pre-conditions: transactBook is not-null, isbnLocations has some data, errorOut points to the ERRORS file. masterOut points to copy.out,
    and transactionNumber is an integer greater than or equal to 1.
post-conditions: If the isbn value of the book in transactBook is in the map as a key, the onhand value is changed accordingly in copy.out.
    If the isbn is not in the map an error message is printed to the console and saved to the ERRORS file.*/

void processTransactions( map<unsigned int, long> & isbnLocations, string transactionFileName );
/*
pre-conditions: isbnLocations has the isbn of every book in copy.out and transactionFileName is the name of the file with transaction records in binary.
post-conditions: The map is updated to include added books and to not have removed books. copy.out is changed to have the records of added books,
    as well as having the prices and onhand values changed according to the transactions.*/

void writeFinalMasterBinary( map<unsigned int, long> isbnLocations, string masterOutName );
/*
pre-conditions: isbnLocations and copy.out have been altered according to the transactions. 
    masterOutName must be the name of the new master file
post-conditions: a file with the name masterOutName is filled with all the books from copy.out who's 
    isbn numebrs are in the map*/

void readAndPrintBinaryBooks(string fileName);
/*
pre-conditions: fileName is the name of a file holding just binary book records.
post-conditions: a string representation of every book in the fileis printed to the console.*/