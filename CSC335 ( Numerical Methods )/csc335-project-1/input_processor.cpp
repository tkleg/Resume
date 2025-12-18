#include"input_processor.h"

#ifdef INPUT_PROCESSOR_TEST
int main(){
    DualStream out("input_processor.txt", true, true);
    printParams(getInputParams(), out);
    // printParams(manualInputParams());

    return 0;
}
#endif

void printParams( InputParams params, DualStream& out ){
    out << "File Name: " << params.input_file_name << endl << endl;
    out << "Baseline: " << params.baseline << endl << endl;
    out << "Tolerance: " << params.tolerance << endl << endl;
    out << "Filter Type: ";
    switch(params.filter_type){
        case NONE:
            out << "None" << endl << endl;
            break;
        case BOXCAR:
            out << "Boxcar" << endl << endl;
            break;
        case SAVITZKY_GOLAY:
            out << "Savitzky-Golay" << endl << endl;
            break;
        case DFT:
            out << "Discrete Fourier Transform" << endl << endl;
            break;
    }
    out << "Filter Window Size: " << params.filter_window_size << endl << endl;
    out << "Number of Passes: " << params.num_passes << endl << endl;
    out << "Integration Type: ";
    switch(params.integration_type){
        case NEWTONS_COTES:
            out << "Newton's Cotes" << endl << endl;
            break;
        case ROMBERG:
            out << "Romberg" << endl << endl;
            break;
        case ADAPTIVE:
            out << "Adaptive" << endl << endl;
            break;
        case QUADRATURE:
            out << "Quadrature" << endl << endl;
            break;
    }
    out << "Recovery method: ";
    switch(params.recovery_method){
        case INVERSE:
            out << "Inverse" << endl << endl;
            break;
        case DIRECT:
            out << "Direct" << endl << endl;
            break;
    }
    out << "Output File Name: " << params.output_file_name << endl << endl;
}

InputParams getInputParams(){
    ifstream infile("nmr.in");

    InputParams params;
    int filter_int, integration_int, recovery_int;

    stringstream ss;
    string line;

    for( int x = 0; x <= 8; x++ ){
        switch( x ){
            case 0:
                infile >> params.input_file_name;
                break;
            case 1:
                infile >> params.baseline;
                break;
            case 2:
                infile >> params.tolerance;
                break;
            case 3:
                infile >> filter_int;
                params.filter_type = static_cast<FilterType>(filter_int);
                break;
            case 4:
                infile >> params.filter_window_size;
                break;
            case 5:
                infile >> params.num_passes;
                break;
            case 6:
                infile >> integration_int;
                params.integration_type = static_cast<IntegrationType>(integration_int);
                break;
            case 7:
                infile >> recovery_int;
                params.recovery_method = static_cast<RecoveryMethod>(recovery_int);
                break;
            case 8:
                infile >> params.output_file_name;
                break;
        }
        getline(infile, line);
    }
    infile.close();
    return params;

}

InputParams manualInputParams(){

    string line;
    InputParams params = getInputParams();

    cout << "Enter the name of the input data file: ";
    getline(cin, line);
    if( line != "" )
        params.input_file_name = line;

    cout << "Enter the baseline adjustment value: ";
    getline(cin, line);
    if( line != "" )
        params.baseline = stoi(line);

    cout << "Enter the tolerance for numerical algorithms: ";
    getline(cin, line);
    if( line != "" )
        params.tolerance = stod(line);

    cout << "Enter the type of filter (0=none, 1=boxcar, 2=SG, 3=DFT): ";
    getline(cin, line);
    if( line != "" )
        params.filter_type = static_cast<FilterType>(stoi(line));

    cout << "Enter the size of the boxcar or SG filter (should be odd, see below): ";
    getline(cin, line);
    if( line != "" )
        params.filter_window_size = stoi(line);

    cout << "Enter the number of passes of the filter: ";
    getline(cin, line);
    if( line != "" )
        params.num_passes = stoi(line);

    cout << "Enter the type of integration (0=Newton's Cotes, 1=Romberg, 2=Adaptive, 3=Quadrature): ";
    getline(cin, line);
    if( line != "" )
        params.integration_type = static_cast<IntegrationType>(stoi(line));

    cout << "Enter the name of the output data file: ";
    getline(cin, line);
    if( line != "" )
        params.output_file_name = line;

    cout << "Enter the recovery method (0=Inverse, 1=Direct): ";
    getline(cin, line);
    if( line != "" )
        params.recovery_method = static_cast<RecoveryMethod>(stoi(line));

    return params;
}
