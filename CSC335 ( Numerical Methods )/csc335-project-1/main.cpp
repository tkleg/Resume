#include "main.h"

#ifdef MAIN
//Note: 1329 data points in original testdata.dat
int main(){

    InputParams params = getInputParams();
    
    DualStream out(params.output_file_name, true, true);
    
    vector< pair<double, double> > data = readDataFromFile(params.input_file_name);

    // Start timing
    auto start = chrono::high_resolution_clock::now();

    //Sorts data by x values ascending
    sort(data.begin(), data.end(), []( pair<double, double> a, pair<double, double> b ){
        return a.first < b.first;
    });
    
    //nullopt if no peak found. Means no data above baseline.
    optional< pair<double, double> > shift_peak = getPeak(data, params.baseline);
    if( ! shift_peak.has_value() ){
        out << "No data can be found above the baseline. No analysis necessary." << endl;
        return 0;
    }

    //Shift data horizontally by shifting peak
    vector< pair<double, double> > shiftedData = shiftDataHorizontal(data, shift_peak->first);

    //Filter data based on input parameters
    vector< pair<double, double> > filteredData = filterData(shiftedData, params, out.getFileStream() );

    //Shift data vertically by baseline
    vector<pair<double, double> > baselineAdjustedData = shiftDataVertical(filteredData, params.baseline);

    //Get natural spline coefficients
    vector<NaturalSplineCoefficients> splineCoeffs = naturalSplineCoeffs(baselineAdjustedData);

    //Get x values for spline function
    vector<double> xVals;
    for( pair<double, double> point : baselineAdjustedData )
        xVals.push_back(point.first);

    //Create spline function
    function<double(double)> splineFunc = splineFunction(splineCoeffs, xVals);

    //Get integral bounds based on tolerance
    vector< pair< double, double > > integralBounds = getIntegralBounds( splineFunc, params.tolerance, make_pair(shiftedData.front().first, shiftedData.back().first) );
    if( integralBounds.size() == 0 ){
        out << "No peaks found to integrate over. Exiting." << endl;
        return 0;
    }

    vector<PeakData> peaks = getPeaks(splineFunc, integralBounds, params );

    printResults(peaks, out, params, shift_peak->first);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    out << fixed << setprecision(4) << "Total elapsed time: " << elapsed.count() << " seconds" << endl;

    //ifdef to allow executables to run with or without writing all data files
    #ifdef WRITE_ALL
        vector< pair<double, double> > splineData;
        for( double x = baselineAdjustedData.front().first; x <= baselineAdjustedData.back().first; x += .01 )
                splineData.push_back( make_pair( x, splineFunc(x) ) );
        writeAll( params.filter_type, params.filter_window_size, shiftedData, filteredData, splineData, out.getFileStream() );
    #endif
    
    out.getFileStream().close();

    return 0;
}
#endif

vector< pair<double, double> > filterData( vector< pair<double, double> > data, InputParams params, ofstream& outfile ){
    switch( params.filter_type ){
        case BOXCAR:
            return boxCarFilter(data, params.filter_window_size, params.num_passes);
        case SAVITZKY_GOLAY:
            return savGolFilter(data, params.filter_window_size, params.num_passes);
        case DFT:{
            int n = data.size();
            vector<double> v(n);
            for( int i = 0; i < n; i++ )
                v[i] = data[i].second;
            cx_mat Z = zMatrix(n);
            cx_vec c = cVector( v, Z );
            if( params.recovery_method == INVERSE )
                v = recoverInverse( c, Z );
            else if( params.recovery_method == DIRECT )
                v = recoverDirect( c, Z );
            else
                throw invalid_argument( "Unknown recovery method" );
            vector< pair<double, double> > filteredData;
            for( int i = 0; i < n; i++ )
                filteredData.push_back( make_pair( data[i].first, real(v[i]) ) );
            return filteredData;
        }
        case NONE:
            return data;
        default:
            outfile << "Error: Unknown filter type" << endl;
            exit(1);
    }
    return data;
}

vector<PeakData> getPeaks( function<double(double)> splineFunc, vector< pair<double, double> > integralBounds, InputParams params ){
    vector<PeakData> peaks;
    optional<int> index_min_area = nullopt;
    double min_area = -1.0;
    for( int x = 0; x < integralBounds.size(); x++ ){
        if( integralBounds[x].first * integralBounds[x].second <= 0 )
            continue; //Skip any bounds that touch or cross x=0
        PeakData peak;
        peak.index = x + 1;
        peak.begin = integralBounds[x].first;
        peak.end = integralBounds[x].second;
        peak.loc = (peak.end + peak.begin) / 2.0;
        peak.top = splineFunc(peak.loc);
        //Hardcoded tolerance for Newton's Cotes and Romberg to 1e-3 to avoid excessive computation time
        switch( params.integration_type ){
            case NEWTONS_COTES:
                peak.area = tolerant_composite_simpsons_rule(splineFunc, peak.begin, peak.end, 1e-3, 100000);
                break;
            case ROMBERG:
                peak.area = tolerant_romberg_extrapolation(splineFunc, peak.begin, peak.end, 1e-3);
                break;
            case ADAPTIVE:
                peak.area = adaptive_quadrature(splineFunc, peak.begin, peak.end, 6*params.tolerance);
                break;
            case QUADRATURE:
                peak.area = gauss_legendre_64pt(splineFunc, peak.begin, peak.end);
                break;
        }
        peaks.push_back(peak);
        if ( ! index_min_area.has_value() || peak.area < min_area ){
            min_area = peak.area;
            index_min_area = x;
        }
    }

    peaks[index_min_area.value()].hydrogenCount = 1;

    for( int x = 0; x < peaks.size(); x++ )
        if( x != index_min_area )
            peaks[x].hydrogenCount = round(peaks[x].area / min_area);

    return peaks;
}

void writeAll( FilterType filter_type, int filter_window_size, vector< pair<double, double> > shiftedData,
    vector< pair<double, double> > filteredData, vector< pair<double, double> > splineData, ofstream& outfile){
    writeDataToFile(shiftedData, "shiftedData.dat");
    switch( filter_type ){
        case BOXCAR:
            writeDataToFile(filteredData, "BoxCarfilteredData" + to_string(filter_window_size) + ".dat");
            break;
        case SAVITZKY_GOLAY:
            writeDataToFile(filteredData, "SavGolfilteredData" + to_string(filter_window_size) + ".dat");
            break;
        case NONE:
            writeDataToFile(filteredData, "unfilteredData.dat");
            break;
        case DFT:
            writeDataToFile(filteredData, "DFTfilteredData.dat");
            break;
        default:
            cout << "Error: Unknown filter type" << endl;
            outfile << "Error: Unknown filter type" << endl;
            exit(1);
    }
    writeDataToFile(filteredData, "filteredData.dat");
    writeDataToFile(splineData, "splineData.dat");
}

void printResults( vector<PeakData> peaks, DualStream& out, InputParams params, double shift_amount ){

    out << right << setw(30) << "-=> NMR ANALYSIS <=-" << endl << endl << endl;
    out << "Program Options" << endl << setfill('=') << setw(20) << "" << setfill(' ') << endl;
    out << left << setw(20) << "Baseline Adjustment" << ":\t" << params.baseline << endl;
    out << left << setw(20) << "Tolerance" << ":\t" << params.tolerance << endl;
    out << left << setw(20) << "Filter Type" << ":\t";
    switch( params.filter_type ){
        case BOXCAR:
            out << "Boxcar";
            break;
        case SAVITZKY_GOLAY:
            out << "Savitzky-Golay";
            break;
        case DFT:
            out << "Discrete Fourier Transform";
            break;
        case NONE:
            out << "No";
            break;
        default:
            out << "Unknown Filter Type in printResults filter_type switch";
    }
    out << " Filter" << endl;

    if( params.filter_type == BOXCAR ){
        out << left << setw(20) << "Boxcar Size (Cyclic)" << ":\t" << params.filter_window_size << endl;
        out << left << setw(20) << "Boxcar Passes" << ":\t" << params.num_passes << endl;
    }else if( params.filter_type == SAVITZKY_GOLAY ){
        out << left << setw(20) << "Savitzky-Golay Size" << ":\t" << params.filter_window_size << endl;
        out << left << setw(20) << "Savitzky-Golay Passes" << ":\t" << params.num_passes << endl;
    }

    out << endl << "Techniques" << endl << setfill('=') << setw(20) << "" << setfill(' ') << endl;
    out << left << setw(20) << "Integration Method" << ":\t";
    switch( params.integration_type ){
        case NEWTONS_COTES:
            out << "Newton's-Cotes";
            break;
        case ROMBERG:
            out << "Romberg Extrapolation";
            break;
        case ADAPTIVE:
            out << "Adaptive Quadrature";
            break;
        case QUADRATURE:
            out << "Gauss-Legendre Quadrature";
            break;
        default:
            out << "Unknown Integration Type in printResults integration_type switch";
    }
    out << " Integration" << endl;
    if( params.filter_type == DFT ){
        out << left << setw(20) << "DFT Recovery Method" << ":\t";
        switch( params.recovery_method ){
            case INVERSE:
                out << "Inverse";
                break;
            case DIRECT:
                out << "Direct Matrix Factorization";
                break;
            default:
                out << "Unknown DFT Recovery Method in printResults recovery_method switch";
        }
    }
    out << endl << endl;
    out << "Plot File Data" << endl << setfill('=') << setw(20) << "" << setfill(' ') << endl;
    out << left << setw(20) << "Input File" << ":\t" << params.input_file_name << endl;
    out << "Plot shifted by " << setprecision(5) << shift_amount << " ppm for TMS calibration" << endl << endl;
    
    //Print headers for table
    out << left << setw(9) << "Peak" << setw(18) << "Begin" << setw(17) << "End"
    << setw(17) << "Location" << setw(17) << "Top" << setw(17) << "Area" <<
    "Hydrogens" << endl;

    //Print separator line
    out << setfill('=') << setw(7) << "" << "  " << setw(16) << "" << "  " << setw(16) << "" 
        << " " << setw(16) << "" << " " << setw(16) << "" << " " <<
        setw(16) << "" << " " << setw(9) << "" << endl;

    //Set formatting for numbers in table
    out << setfill(' ') << fixed << setprecision(12) << uppercase;
 
    //Print peak data
    for( PeakData peak : peaks ){
        out << fixed << setprecision(10) << "   " << left 
            << setw(6) << peak.index << right
            << setw(16) << peak.begin 
            << setw(18) << peak.end 
            << setw(17) << peak.loc << setprecision(8)
            << setw(17) << peak.top
            << scientific
            << setw(16) << peak.area <<
            setw(10) << peak.hydrogenCount
            << endl;
    }
    double sum_area = 0;
    for( PeakData peak : peaks )
        sum_area += peak.area;
    out << "\nTotal integrated area: " << sum_area << endl << endl;
}
