#include<iostream>
#include<vector>
#include<utility>
#include<functional>
#include<fstream>
#include"lagrange.h"
using namespace std;

long double curveSample1(long double x);
long double curveSample2(long double x);
void writeDataToFile(string filename, function<long double(long double)> func, long double start, long double end);

int main(){
    vector<int> xValues;
    for(int i = 0; i <= 28; i++)
        xValues.push_back(i);

    long double maxSample1 = curveSample1(0);
    int maxDay1 = 0;

    long double maxSample2 = curveSample2(0);
    int maxDay2 = 0;
    for(long double x : xValues){
        long double y1 = curveSample1(x);
        if(y1 > maxSample1){
            maxSample1 = y1;
            maxDay1 = x;
        }
        long double y2 = curveSample2(x);
        if(y2 > maxSample2){
            maxSample2 = y2;
            maxDay2 = x;
        }
    }

    cout << "Max of Sample 1: " << maxSample1 << " on day " << maxDay1 << endl;
    cout << "Max of Sample 2: " << maxSample2 << " on day " << maxDay2 << endl;
    writeDataToFile("sample1.dat", curveSample1, 0, 28);
    writeDataToFile("sample2.dat", curveSample2, 0, 28);
    return 0;
}

void writeDataToFile(string filename, function<long double(long double)> func, long double start, long double end){
    ofstream outFile(filename);
    for(long double x = start; x <= end; x++)
        outFile << x << " " << func(x) << endl;
    outFile.close();
}

long double curveSample1(long double x){
    vector<pair<long double,long double>> sample1 =
        {{0,6.67}, {6,17.33},
        {10,42.67}, {13,37.33},
        {17,30.10}, {20, 29.31},
        {28, 28.74}};
    return lagrange(sample1, x);
}

long double curveSample2(long double x){
    vector<pair<long double,long double>> sample2 =
        {{0,7.67}, {6,16.61},
        {10,18.89}, {13,15.00},
        {17,10.56}, {20,9.44},
        {28,8.89}};
    return lagrange(sample2, x);
}