#include"common.h"
#include"filters.h"
#include<set>

#ifdef TEST_SAVITZKY_GOLAY_READER
int main(){
    for( const int windowSize : {5, 11, 17} ){
        SavitzkyGolayData savData = getSavitzkyGolayData(windowSize);
        cout << "Window Size: " << savData.windowSize << endl;
        cout << "Normalization Factor: " << savData.norm << endl;
        cout << "Coefficients: ";
        for(int coeff : savData.coefficients)
            cout << coeff << " ";
        cout << endl << endl;
    }
    
    return 0;
}
#endif

SavitzkyGolayData getSavitzkyGolayData(int windowSize) {
    //Hardcoded coefficients for Savitzky-Golay filters of window sizes 5, 11, and 17
    switch(windowSize) {
        case 5:
            return {5, 35, {-3, 12, 17, 12, -3}};
        case 11:
            return {11, 429, {-36, 9, 44, 69, 84, 89, 84, 69, 44, 9, -36}};
        case 17:
            return {17, 323, {-21, -6, 7, 18, 27, 34, 39, 42, 43, 42, 39, 34, 27, 18, 7, -6, -21}};
    };
    return {0, 0, {}};
}

vector< pair<double, double> > savGolFilter( vector< pair<double, double> > data, int windowSize, int numPasses ){
    if ( windowSize == 0 )
        return data; //no filtering if window size is 0
    SavitzkyGolayData sgData = getSavitzkyGolayData(windowSize);
    int loopCountHelp = (int) (( windowSize - 1 ) / 2); //helps center the window around the current point
    int index = 0;
    vector< pair<double, double> > filteredData = data;
    for( int x = 0; x < numPasses; x++ ){//Passes
        for( int i = 0; i < data.size(); i++ ){//Point to filter
            double filteredY = 0;
            int countForCoeffs = 0;
            for( int j = i - loopCountHelp; j <= i + loopCountHelp; j++){//Point in window
                if ( j >= data.size() )
                    index = j % data.size();
                else if ( j < 0 )
                    index = data.size() + j;
                else
                    index = j;
                filteredY += data[index].second * sgData.coefficients[countForCoeffs++];
            }
            filteredData[i].second = filteredY / sgData.norm;
        }
        data = filteredData; //update data for next pass
    }
    return data;
}

vector< pair<double, double> > boxCarFilter( vector< pair<double, double> > data, int windowSize, int numPasses ){
    if ( windowSize == 0 )
        return data; //no filtering if window size is 0
    int loopCountHelp = (int) (( windowSize - 1 ) / 2);
    int index = 0;
    vector< pair<double, double> > filteredData = data;
    for( int x = 0; x < numPasses; x++ ){//Passes
        for( int i = 0; i < data.size(); i++ ){//Point to filter
            double filteredY = 0;
            for( int j = i - loopCountHelp; j <= i + loopCountHelp; j++){//Point in window
                if ( j >= data.size() )
                    index = j % data.size();
                else if ( j < 0 )
                    index = data.size() + j;
                else
                    index = j;
                filteredY += data[index].second;
            }
            filteredData[i].second = filteredY / windowSize;
        }
        data = filteredData; //update data for next pass
    }
    return data;
}
