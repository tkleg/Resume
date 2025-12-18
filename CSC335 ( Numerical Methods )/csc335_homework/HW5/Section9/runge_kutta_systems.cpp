#include "runge_kutta_systems.h"

#ifdef RUNGE_KUTTA_SYSTEMS_TEST
int main(){
    cout << "No main test for runge_kutta_systems.cpp" << endl;
    return 0;
}
#endif

double runge_system_solver( double a, double b, vector< function<double( double, vector<double> )> > funcs, optional< vector< function<double(double)> > > actual_funcs, vector<double> y0, optional<int> N, optional<double> h, optional<string> data_filename, bool print_all ){
    int m = funcs.size();
    if( !h )
        h = (b - a) / N.value();
    if( !N )
        N = (int) ( (b - a) / h.value() );
    double t = a;

    if( print_all )
        cout << setprecision(8);

    vector<double> w;
    for( double initial_val : y0 )
        w.push_back( initial_val );


    vector< vector<double> > k_all( 4, vector<double>(m));
    ofstream outfile;
    if( data_filename )
        outfile.open( data_filename.value() );
    if( print_all ){
        //print header
        cout << setw(3) << "t";
        if( data_filename)
            outfile << setw(3) << "t";
        for( int x = 0; x < m; x++ ){
            if( data_filename )
                outfile << setw(13) << "w[" + to_string(x) + "]";
            cout << setw(13) << "w[" + to_string(x) + "]";
            if( actual_funcs ){
                cout << setw(13) << "actual[" + to_string(x) + "]";
                if( data_filename )
                    outfile << setw(13) << "actual[" + to_string(x) + "]";
            }
        }
        cout << endl;
        if( data_filename )
            outfile << endl;
    }

    for( int i = 0; i < N.value(); i++ ){

        for( int j = 0; j < m; j++ )
            k_all[0][j] = h.value() * funcs[j](t, w);

        vector<double> k_row_copy(m);

        transform(k_all[0].begin(), k_all[0].end(), k_row_copy.begin(), [](double val) { return val * 0.5; });
        for(int j = 0; j < m; j++ )
            k_all[1][j] = h.value() * funcs[j]( t + h.value() / 2, vector_sum( w, k_row_copy ) );

        transform(k_all[1].begin(), k_all[1].end(), k_row_copy.begin(), [](double val) { return val * 0.5; });
        for(int j = 0; j < m; j++ )
            k_all[2][j] = h.value() * funcs[j]( t + h.value() / 2, vector_sum( w, k_row_copy ) );

        for(int j = 0; j < m; j++ )
            k_all[3][j] = h.value() * funcs[j]( t + h.value(), vector_sum( w, k_all[2] ) );

        for( int j = 0; j < m; j++ )
            w[j] += ( k_all[0][j] + 2 * k_all[1][j] + 2 * k_all[2][j] + k_all[3][j] ) / 6;
        t += h.value();

        if( print_all ){
            cout << setw(3) << t;
            if( data_filename)
                outfile << setw(3) << t;
            for( int x = 0; x < m; x++ ){
                if( data_filename )
                    outfile << setw(13) << w[x];
                cout << setw(13) << w[x];
                if( actual_funcs ){
                    cout << setw(13) << actual_funcs.value()[x](t);
                    outfile << setw(13) << actual_funcs.value()[x](t);
                }
            }
            outfile << endl;
            cout << endl;
        }

    }
    if( data_filename )
        outfile.close();
    return w[0];
}

vector<double> vector_sum(vector<double> v1, vector<double> v2){
    if(v1.size() != v2.size()) {
        cout << "Error: Vectors must be of the same size to add." << endl;
        exit(1);
    }

    vector<double> result(v1.size());
    for(int i = 0; i < v1.size(); i++) {
        result[i] = v1[i] + v2[i];
    }
    return result;
}