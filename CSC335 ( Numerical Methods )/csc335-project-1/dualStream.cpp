#include "dualStream.h"


#ifdef dualStream
int main(){
    DualStream ds("dual.txt", true, true);
    ds << setprecision(10) << right << setw(30) << "file and cout test" << endl;
    ds.setCoutEnabledStatus(false);
    ds << "file only test" << endl;
    ds.setFileEnabledStatus(false);
    ds.setCoutEnabledStatus(true);
    ds << "cout only test" << endl;
    ds.setCoutEnabledStatus(false);
    ds << "no output test" << endl;

    return 0;

}
#endif

ofstream& DualStream::getFileStream(){
    return fileStream;
}

DualStream::DualStream(string filename, bool toFile, bool toCout){
    this->printToFile = toFile;
    this->printToCout = toCout;
    fileStream.open(filename);
}

bool DualStream::isFileOpen(){
    return printToFile;
}

bool DualStream::isCoutEnabled(){
    return printToCout;
}

void DualStream::setCoutEnabledStatus(bool enabled){
    printToCout = enabled;
}

void DualStream::setFileEnabledStatus(bool enabled){
    printToFile = enabled;
}

DualStream& DualStream::operator<<(ostream& (*manip)(ostream&)){
            if(printToFile)
                fileStream << manip;
            if(printToCout)
                cout << manip;
            return *this;
}