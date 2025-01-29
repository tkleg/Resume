#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>
#include <climits>
#include <map>
#include "common.h"
#include "update.h"
using namespace std;


/* transaction plan
1. valid add of 1984
2. (ERROR) duplicate add of 1984
3. valid delete of 1984
4. (ERROR) failed delete 1984, no key
5. valid add of 1984
6. (ERROR) change on hand of 1984, cause overflow to negative
7. (ERROR) attempt to change on hand of invalid isbn
8. on hand is now 0, valid add of 9 to 1984 on hand
9. add 123 to 1984 onhand, now 132
10. (ERROR) attempt to change price of isbn 1, not found
11. change price of 1984 to 9.89
12. (ERROR) attempted duplicate add of tom sawyer
13. valid delete of tom sawyer
14. (ERROR) attempt to delete tom sawyer when it does not exist
15. valid re-ad of tom sawyer
16. (ERROR) change on hand of tom sawyer, cause overflow to negative
17. (ERROR) attempt to change on hand of invalid isbn
18. tom sawyer on hand now 0, add 20 to it
19. add 99 to tom sawyer on hand, now 119
20. add 2 to tom sawyer on hand, now 121
21. (ERROR) attempt to change price of invalid isbn
22. change price of tom sawyer to 15.72

ERROR TRANSACTIONS: 2, 4, 6, 7, 10, 12, 14, 16, 17, 21
*/

void readAndPrintTransactions( string fileName );

void printTransaction( TransactionRec t, string transactTypes[4] );

vector<TransactionRec> makeTransactions();

void writeTransactions( vector<TransactionRec> transactions, string fileName );

int main(int argc, char* argv[]){
    //TransactionRec t = getFirstTransaction();
    //printTransaction(t);
    vector<TransactionRec> transactions = makeTransactions();
    writeTransactions( transactions,  argv[1] );
    readAndPrintTransactions(argv[1]);
}

/*TransactionRec getFirstTransaction(){
    fstream binfile("transact.out", ios::in | ios::binary);
    TransactionRec t;
    binfile.seekg(0);
    binfile.read( (char *) &t, sizeof(TransactionRec) );
    binfile.close();
    return t;
}*/
void writeTransactions( vector<TransactionRec> transactions, string fileName ){
    fstream binfile(fileName, ios::out | ios::binary);
    binfile.seekg(0);
    for( int x = 0; x < transactions.size(); x++ )
        binfile.write( (char *) &transactions[x], sizeof(TransactionRec) );
    binfile.close();
}

vector<TransactionRec> makeTransactions(){
    TransactionRec t;
    vector<TransactionRec> transactions;
    unsigned int newRecIsbn = 123456789, tSawyerIsbn = 123766891;

    //start testing add for new record
    t.ToDo = TransactionType::Add;
    t.B.isbn = newRecIsbn;
    strcpy( t.B.name, "1984" );
    strcpy( t.B.author, "Orwell, George");
    t.B.onhand = 5;
    t.B.price = 15.65;
    strcpy( t.B.type, "fiction");
    transactions.push_back(t);
    
    //start test add for new record
    transactions.push_back(t);
    //end test add for new record
    //start test delete for new record
    t.ToDo = TransactionType::Delete;
    transactions.push_back(t);
    //delete error triggers below
    transactions.push_back(t);

    t.ToDo = TransactionType::Add;
    transactions.push_back(t);

    //start test onhand for new record
    t.ToDo = TransactionType::ChangeOnhand;
    t.B.onhand = INT_MAX;
    transactions.push_back(t);

    t.B.isbn = 1;
    t.B.onhand = 9;
    transactions.push_back(t);

    t.B.isbn = newRecIsbn;
    transactions.push_back(t);

    t.B.onhand = 123;
    transactions.push_back(t);
    //end test one hand for new record
    //onhand should be 123 for the book 1984
    //start test price for new record
    t.ToDo = TransactionType::ChangePrice;
    t.B.isbn = 1;
    transactions.push_back(t);

    t.B.isbn = newRecIsbn;
    t.B.price = 9.89;
    transactions.push_back(t);
    //end test price for new record
    //price should be 9.89 for the book 1984

    BookRec existingRecord{123766891, "Tom Sawyer", "Twain, Mark", 2, 8.5, "fiction"};
    //start test add and delete for existing record
    t.ToDo = TransactionType::Add;
    t.B = existingRecord;
    transactions.push_back(t);

    t.ToDo = TransactionType::Delete;
    transactions.push_back(t);
    transactions.push_back(t);

    t.ToDo = TransactionType::Add;
    transactions.push_back(t);
    //end test add for existing record
    //start test onhand for existing record
    t.ToDo = TransactionType::ChangeOnhand;
    t.B.onhand = INT_MAX;
    transactions.push_back(t);

    t.B.isbn = 2;
    t.B.onhand = 20;
    transactions.push_back(t);

    t.B.isbn = tSawyerIsbn;
    transactions.push_back(t);

    t.B.onhand = 99;
    transactions.push_back(t);
    t.B.onhand = 2;
    transactions.push_back(t);
    //end test onhand for existing record
    //tom sawyer onhand should be 101
    //start testing price for existing record
    t.ToDo = TransactionType::ChangePrice;
    t.B.isbn = 2;
    transactions.push_back(t);

    t.B.isbn = tSawyerIsbn;
    t.B.price = 15.72;
    transactions.push_back(t);
    //end test price for existing record
    //price should be 15.72
    return transactions;

}

void printTransaction( TransactionRec t, string transactTypes[4] ){
    cout << setw(13) << transactTypes[t.ToDo] << ": " << bookToString(t.B); 
}

void readAndPrintTransactions( string fileName ){
    TransactionRec t;
    string transactTypes[4] = {"Add", "Delete", "ChangeOnhand", "ChangePrice"};
    fstream binfile(fileName, ios::in | ios::binary);
    binfile.seekg(0, ios::beg);
    while( binfile.read( (char *) &t, sizeof(TransactionRec) ) )
        printTransaction( t, transactTypes );
    binfile.close();
}