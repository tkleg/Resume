#ifndef INPUT_PROCESSOR_H
#define INPUT_PROCESSOR_H

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include"dualStream.h"
using namespace std;

enum FilterType { NONE, BOXCAR, SAVITZKY_GOLAY, DFT };
enum IntegrationType { ADAPTIVE, ROMBERG, NEWTONS_COTES, QUADRATURE };
enum RecoveryMethod { INVERSE, DIRECT };

struct InputParams{
    string input_file_name;
    double baseline;
    double tolerance;
    FilterType filter_type;
    int filter_window_size;
    int num_passes;
    IntegrationType integration_type;
    string output_file_name;
    RecoveryMethod recovery_method;
};

InputParams getInputParams();
/*
    @return: struct containing all input parameters
    Gets all input parameters from nmr.in.
*/

void printParams( InputParams params, DualStream& out );
/*
    @param params: struct containing all input parameters
    Prints the input parameters to console.
*/

InputParams manualInputParams();
/*
    @return: struct containing manually inputted parameters. With defaults where nothing is entered.
*/

#endif