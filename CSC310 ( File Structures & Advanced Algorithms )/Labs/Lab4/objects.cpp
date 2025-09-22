#include <fstream>
#include <iostream>
#include <map>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <memory>
using namespace std;

class Song {
public:
  string title;
  int time;
  int track;      // Primary key
  bool operator < (Song another) const { return title < another.title;}
  friend ostream & operator<<(ostream& out, const Song& l);
};

//this operator writes out the song in the correct format
ostream & operator << (ostream& out, const Song & l){
    cout << setw(16) << "" << l.track << ".  " << l.title << ": " << l.time/60 << ":";
    if ((l.time % 60) < 10) cout << "0";
    cout << l.time % 60 << endl;
    return out;
}

class Album {
  public :
    mutable map<int, Song> songs;
    string name;  // Album's name
    string artist;
    string genre;
    mutable int time;     // Total time of all songs on album
    mutable int nsongs;   // Total number of songs on album

    bool operator < (Album another) const { return name < another.name;}
    bool operator == (string albumName) const { return name == albumName;}

    void printAlbum();

    Album(){}

    Album(map<int, Song> songs, string name, string artist, string genre, int time, int nsongs)
        : songs(std::move(songs)), name(std::move(name)), artist(std::move(artist)), 
          genre(std::move(genre)), time(time), nsongs(nsongs) {}
    friend std::ostream& operator<<(std::ostream& out, const Album& al);
};

void Album::printAlbum(){
  cout << setw(8) << "" << name << ": " << nsongs << ", " << time/60 << ":";
  if ((time % 60) < 10) cout << "0";
    cout << time % 60 << endl;
  //map< int, Song >::iterator it;
  //for( it = songs.begin(); it != songs.end(); it++ )
  for( const auto& song : songs )
    cout << song.second;
}

class Artist {
   public :
     string name; // Artist's name
     set<Album> albums; // Artist's Albums
     int time;    // Total time of all songs on all albums by this artist
     int nsongs;  // Total number of songs on all albums by this artist

     void printArtist();

     bool operator < (Artist another) const { return name < another.name;}
     bool operator == (string artistName) const { return name == artistName;}
     friend std::ostream& operator<<(std::ostream& out, const Artist& ar);
};

void Artist::printArtist(){
  cout << name << ": " << nsongs << ", " << time/60 << ":";
  if ((time % 60) < 10) cout << "0";
  cout << time % 60 << endl;  
  set<Album>::iterator it;
  for( it = albums.begin(); it != albums.end(); it++ ){
    Album album = *it;
    album.printAlbum();
  }
}

struct SongHelp{
    string artist;
    string album;
    string genre;
};