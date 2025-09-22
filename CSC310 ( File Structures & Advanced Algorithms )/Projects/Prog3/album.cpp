#include "album.h"

Album::Album (const Album& otherAlbum){
    strcpy( UPC, otherAlbum.UPC );
    strcpy( Artist, otherAlbum.Artist );
    strcpy( Title, otherAlbum.Title );
}

Album::Album (String upc, String artist, String title){
    strcpy( UPC, upc );
    strcpy( Artist, artist );
    strcpy( Title, title );
}

Album::Album(){
    strcpy( UPC, "\0" );
    strcpy( Artist, "\0" );
    strcpy( Title, "\0" );
}

Album & Album::operator = (const Album& otherAlbum){
    strcpy( UPC, otherAlbum.UPC );
    strcpy( Artist, otherAlbum.Artist );
    strcpy( Title, otherAlbum.Title );
    return *this;
}

bool operator < (const Album& a, const Album& b){
    return strcmp( a.UPC, b.UPC ) < 0;
}

string Album::getUPC(){
    return string(UPC);
}

int Album::recordSize(){
    return strlen(UPC)+strlen(Artist)+strlen(Title); 
}

ostream & operator << (ostream & stream, Album & C){
    cout << C.UPC << "|" << C.Artist << "|" << C.Title << "|" << endl;
    return stream;
}

istream & operator >> (istream & stream, Album & C){
    string upc, artist, title;
    getline( stream, upc );
    getline( stream, artist );
    getline( stream, title );
    C = Album( strdup(upc.c_str()), strdup(artist.c_str()), strdup(title.c_str()) );
    return stream;
}