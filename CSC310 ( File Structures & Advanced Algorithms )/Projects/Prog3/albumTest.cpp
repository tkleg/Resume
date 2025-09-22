#include "includes.h"
#include "album.cpp"

int main(int argc, char* argv[]){

    Album a = Album();
    string upc = "52344565";
    string artist = "Bon Jovi";
    string title = "It's My Life";
    Album b = Album( strdup(upc.c_str()), strdup(artist.c_str()), strdup(title.c_str()) );

    upc = "29804723";
    artist = "Billy Joel";
    title = "Piano Man";
    Album c = Album( strdup(upc.c_str()), strdup(artist.c_str()), strdup(title.c_str()) );

    upc = "89023423";
    artist = "Eminem";
    title = "Lose Yourself";
    Album d = Album( strdup(upc.c_str()), strdup(artist.c_str()), strdup(title.c_str()) );

    Album dc = Album(d);

    Album cc = c;

    set<Album> albums;
    albums.insert(a);
    albums.insert(b);
    albums.insert(c);
    albums.insert(d);
    albums.insert(dc);
    albums.insert(cc);

    for( auto album : albums ){
        cout << album;
    }
    albums.clear();
    cout << endl << endl;

    Album aIn;
    fstream albumsIn( argv[1], ios::in );
    while( albumsIn ){
        albumsIn >> aIn;
        if( aIn.getUPC() == "" )
            break;
        if( albums.find( aIn ) != albums.end() )
            cout << "duplicate" << endl;
        albums.insert( aIn );
    }

    for( auto album : albums ){
        cout << album << album.recordSize() << endl;
    }
    cout << albums.size() << " albums read" << endl;
    return 0;
}