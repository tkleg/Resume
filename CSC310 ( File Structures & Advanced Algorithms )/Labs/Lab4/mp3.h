typedef shared_ptr<Artist> ArtistPtr;
struct ArtistShrPtrComp{
    bool operator()( ArtistPtr a, ArtistPtr b ) const {
      return *a < *b;
    }
};
typedef set<ArtistPtr, ArtistShrPtrComp> ArtistSet;

void getSongs( char* fileName, vector<Song> & songs, vector<SongHelp> & songHelpers );
//pre-conditions: fileName points to a file filled of properly formatted songs
//post-conditions: songs and songHelpers are filled, each with one entry per entry in the file

void noUnderscores( string & s );
//pre-conditions: none
//post-conditions: all underscores in s are changed to spaces

ArtistSet getArtists( vector<Song> songs, vector<SongHelp> songHelpers );
//pre-conditions: 
//  1. songs and songHelpers have the same size
//  2. For all n in [0, size of songs and songHelpers], songs[x] and songHelpers[x] refer to the same song
//post-conditions: A set of <ArtistPtr, ArtistShrPtrComp> is returned

ArtistPtr assignArtist( string artistName, ArtistSet & artists, set<string> & artistNames );
//pre-conditions: all of the parameters are non-null and artistName is either the name of an artist in artists or it exists in artistNames
//post-conditions: the ArtistPtr referring to the artistName is returned

void assignAlbum( set<Album> & albums, Song song, SongHelp songHelper );
//pre-conditions: song and songHelper are referring to the same entry
//post-conditions: a song entry is entered into a new album if the right album is not in albums. If it is already in albums, then the song's infomartion is added to the appropriate album