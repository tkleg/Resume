
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
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
ostream & operator << (ostream& out, Song & l){
    cout << "\t\t" << l.track << ".  " << l.title << ": " << l.time/60 << ":";
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
    friend std::ostream& operator<<(std::ostream& out, const Album& al);
};

class Artist {
   public :
     string name; // Artist's name
     set<Album> albums; // Artist's Albums
     int time;    // Total time of all songs on all albums by this artist
     int nsongs;  // Total number of songs on all albums by this artist

     bool operator < (Artist another) const { return name < another.name;}
     bool operator == (string artistName) const { return name == artistName;}
     friend std::ostream& operator<<(std::ostream& out, const Artist& ar);
};
