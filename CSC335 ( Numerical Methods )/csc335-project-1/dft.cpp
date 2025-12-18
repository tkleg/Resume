#include "dft.h"
#include <chrono>
#ifdef DFT
int main(){
    /*double start = 0;
    double end = 100;
    double current = start;
    cout << "Enter number of data points to generate (suggested: 500): ";
    int n;
    cin >> n;
    double step = ( end - start ) / n;
    vector<double> v;
    vector<double> x;
    random_device rd;
    mt19937 gen( rd() );
    uniform_real_distribution<double> distribution( 1, 1 );
    while( current <= end ){
        x.push_back( current );
        v.push_back( 20 * sin( current ) * distribution( gen ) );
        current += step;
    }
    for( double val : v )
        cout << val << " ";
    cout << endl;*/
    cout << "Enter filename: ";
    string filename;
    cin >> filename;
    vector<pair<double, double>> dataPoints = readDataFromFile( filename );
    vector<double> v;
    vector<double> x;
    sort( dataPoints.begin(), dataPoints.end() );
    for( pair<double, double> p : dataPoints ){
        x.push_back( p.first );
        v.push_back( p.second );
    }
    int n = v.size();

    cx_mat Z = zMatrix(n);
    cx_vec c = cVector( v, Z );

    //get start time
    auto start = chrono::high_resolution_clock::now();
    vector<double> filtered_v_inverse = recoverInverse( c, Z );
    //get end time
    auto end1 = chrono::high_resolution_clock::now();
    vector<double> filtered_v_solve = recoverDirect( c, Z );
    //get end time
    auto end2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration_inverse = end1 - start;
    chrono::duration<double, milli> duration_solve = end2 - end1;
    cout << "Time taken for conjugate method: " << duration_inverse.count() << " ms" << endl;
    cout << "Time taken for solve method: " << duration_solve.count() << " ms" << endl;

    //make sure length of all 4 vectors are the same
    if( x.size() != v.size() || x.size() != filtered_v_inverse.size() || x.size() != filtered_v_solve.size() ){
        cerr << "Error: vector sizes do not match!" << endl;
        return -1;
    }

    ofstream dftData("dft_data.dat");
    for( int i = 0; i < n; i++ )
        dftData << x[i] << " " << v[i] << " " << filtered_v_inverse[i] << " " << filtered_v_solve[i] << endl;
    dftData.close();

    return 0;
}
#endif

cx_vec cVector( vector< double > data, cx_mat Z ){
    int n = data.size();
    cx_vec y = yVector( data );
    cx_vec c = Z * y;
    cx_mat G = gMatrix(n);
    return G * c;
}

vector<double> recoverInverse(cx_vec c, cx_mat Z){
    cx_vec v = conj( Z ) * c;
    int n = v.size();
    vector<double> recovered_v(n);
    for( int i = 0; i < n; i++ )
        recovered_v[i] = v(i).real();
    return recovered_v;
}

vector<double> recoverDirect(cx_vec c, cx_mat Z){
    cx_vec v = solve( Z, c );
    int n = v.size();
    vector<double> recovered_v(n);
    for( int i = 0; i < n; i++ )
        recovered_v[i] = v(i).real();
    return recovered_v;
}

cx_mat zMatrix(int n){
    cx_mat Z(n, n);

    for(int j = 0; j < n; j++)
        for(int k = 0; k < n; k++)
            Z(j, k) = complex<double>(
                cos( 2 * M_PI * j * k / n ) / sqrt(n),
                -sin( 2 * M_PI * j * k / n ) / sqrt(n)
            );

    return Z;
}

cx_mat gMatrix(int n){
    cx_mat G(n, n);

    for(int j = 0; j < n; j++)
        for(int k = 0; k < n; k++){
            if( j != k )//Kronecker delta
                G(j, k) = complex<double>( 0, 0 );
            else
                G(j, k) = complex<double>( exp( - 4 * log(2) * j * k / pow(n, 1.5) ), 0 );
        }

    return G;
}

cx_vec yVector( vector<double> v ){
    int n = v.size();
    cx_vec x(n);
    for(int i = 0; i < n; i++)
        x(i) = complex<double>(v[i], 0);
    return x;
}