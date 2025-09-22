#include "objects.cpp"
#include "mp3.h"

int main(int argc, char* argv[]){
    if( argc == 1 ){
        cerr << "mp3: missing filename 'mp3'" << endl;
        exit(1);
    }
    vector<Song> songs;
    vector<SongHelp> songHelpers;
    getSongs( argv[1], songs, songHelpers );
    ArtistSet artists = getArtists( songs, songHelpers );
    for( auto artist : artists )
        artist->printArtist();
    return 0;
}

ArtistSet getArtists( vector<Song> songs, vector<SongHelp> songHelpers ){
    ArtistSet artists;
    set<string> artistNames;
    for( int x = 0; x < songHelpers.size(); x++ ){
        shared_ptr<Artist> songArtist = assignArtist( songHelpers[x].artist, artists, artistNames );
        songArtist->time += songs[x].time;
        songArtist->nsongs++;
        assignAlbum( songArtist->albums, songs[x], songHelpers[x] );
    }    
    return artists;
}

void assignAlbum( set<Album> & albums, Song song, SongHelp songHelper ){
    Album songAlbum;
    set<Album>::iterator it;
    map<int, Song> songs;
    bool insertAlbum = true;
    for( it = albums.begin(); it != albums.end(); it++ ){
        if( it->name == songHelper.album ){//true if the song's album is already present
            (it->songs)[song.track] = song;
            it->time += song.time;
            it->nsongs++;
            insertAlbum = false;
        }
    }
    songs[song.track] = song;
    if( insertAlbum )//true if the song is associated with an album that does not yet exist
        albums.insert( Album( songs, songHelper.album, songHelper.artist, songHelper.genre, song.time, 1 ) );
}

ArtistPtr assignArtist( string artistName, ArtistSet & artists, set<string> & artistNames ){
    if( artistNames.count( artistName ) == 0 ){//true if the artist already exists
        ArtistPtr songArtist = make_shared<Artist>();
        songArtist->name = artistName;
        songArtist->albums = set<Album>();
        songArtist->time = 0;
        songArtist->nsongs = 0;
        artists.insert( songArtist );
        artistNames.insert( artistName );
        return songArtist;
    }
    //reachable only for already existing artists
    for (auto& artist : artists) 
        if (artist->name == artistName) 
            return artist;
    return nullptr;//never runs, necessary for compiler however
}

void getSongs( char* fileName, vector<Song> & songs, vector<SongHelp> & songHelpers ){
    fstream in(fileName, ios::in);
    string line;

    string title;
    int mins;
    string minsS;
    int secs;
    int time;
    string artist;
    string album;
    string genre;
    int track; 
    while( true ){
        in >> title;
        getline(in, minsS, ':');
        mins = atoi( minsS.c_str() );
        in >> secs >> artist >> album >> genre >> track;
        if( !in )
            break;
        time = 60*mins + secs;
        noUnderscores(title);
        noUnderscores(artist);
        noUnderscores(album);
        Song song{ title, time, track };
        SongHelp songHelper{ artist, album, genre };
        songs.push_back(song);
        songHelpers.push_back(songHelper);
    }
}

void noUnderscores( string & s ){
    for( int x = 0; x < s.size(); x++)
            if( s[x] == '_' )
                s[x] = ' ';
}