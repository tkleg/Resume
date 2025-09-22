struct EntryErrors{
    bool negIsbn; // negative isbn
    bool negOH; // negative price
    bool negP; // negative price
};//out of sequence isbn is not included because it is handled with a single if statement
// and nothing changes besides printing a message if the error is present in the data

void handleBook( vector<string> & printingBooks, BookRec book, long & prevIsbn, int lineCount, fstream & outfile, long isbnHelp );
/*
pre-conditions: book is filled with data and all other parameters are initialized.
post-conditions: prevIsbn is set to the isbn of book if there are no errors with the book.
    printingBooks gets the string version of book added to it if any error other than ISBN out of sequence is present.
    book is written out as binary to the file outfile is writing to if there is any error other than ISBN out of sequence.
*/

EntryErrors computeErrors( BookRec book, long & prevIsbn, int lineCount, long isbnHelp );
/*
pre-conditions: book has data
post-conditions: an EntryErrors struct is returned which holds booleans determining if the isbn is negative, the on hand is negative, and the price is negative.
*/

void readSingleTextBook( BookRec & book, fstream & infile );
/*
pre-conditions: book has been initialized, the isbn has been assigned, and infile is looking at right after the isbn in the library.day file
post-conditions: book is filled with data that is read in from library.dat by infile
*/
