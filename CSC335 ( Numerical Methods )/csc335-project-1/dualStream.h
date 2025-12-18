#ifndef DUALSTREAM_H
#define DUALSTREAM_H

#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

class DualStream {
    private:
        ofstream fileStream;
        bool printToFile;
        bool printToCout;
    public:
        DualStream(string filename, bool toFile, bool toCout);
        bool isFileOpen();
        void write(string message);
        bool isCoutEnabled();
        void setCoutEnabledStatus(bool enabled);
        void setFileEnabledStatus(bool enabled);
        ofstream& getFileStream();

        template <class T>
        DualStream& operator<<(T message){
            if(printToFile)
                fileStream << message;
            if(printToCout)
                cout << message;
            return *this;
        }
        
        DualStream& operator<<(ostream& (*manip)(ostream&));
};

#endif