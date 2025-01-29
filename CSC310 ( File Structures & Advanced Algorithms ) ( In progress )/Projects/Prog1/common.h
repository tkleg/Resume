#include <iomanip>
#include <string>
using namespace std;

typedef char String[25];
struct BookRec
{
  unsigned int isbn;
  String name;
  String author;
  int onhand;
  float price;
  String type;
};

string isbnToString( unsigned int isbn ){
  string stringIsbn = to_string(isbn);
  int spacesNeeded = 10 - stringIsbn.length();
  for( int x = 0; x < spacesNeeded; x++ )
    stringIsbn = "0" + stringIsbn;
  return stringIsbn;
}

string bookToString( BookRec book ){

    stringstream ss;
    
    //if( book.isbn < 1000000000 )
     //   ss << "0";
    
    ss << setfill('0') << setw(10) << book.isbn << setfill(' ') << setw(21) << right << book.name
     << setw(24) << right << book.author
     << setw(4) << right << book.onhand
     << fixed << setprecision(2) << setw(7) << right << book.price
     << setw(10) << right << book.type << endl;

    return ss.str();
}