#include"integrals.h"
//Index of a double is the coefficient for x^index
int newton_cotes_n = 100000;
int romberg_n = 6;

#ifdef NEWTON_COTES_TEST
int main(int argc, char* argv[]){

    int default_cout_precision = cout.precision();

    cout << fixed << setprecision(10);

    if( argc == 3 ){
        newton_cotes_n = stoi( argv[1] );
        romberg_n = stoi( argv[2] );
    }
    
    vector< vector<double> > R1 = romberg_extrapolation( f1_integrals, -50, 50, 5, true );
    cout << "Adaptive quadrature f1_integrals: " << adaptive_quadrature( f1_integrals, -50, 50, epsilon_multiplier * epsilon ) << endl;
    cout << "Gauss-Legendre 64pt f1_integrals: " << gauss_legendre_64pt( f1_integrals, -50, 50 ) << endl << endl;

    double end = 10;
    double start = 0;

    vector< vector<double> > R2 = romberg_extrapolation( f2_integrals, start, end, romberg_n, true );
    cout << "Adaptive quadrature f2_integrals: " << adaptive_quadrature( f2_integrals, start, end, epsilon_multiplier * epsilon ) << endl;
    cout << "Gauss-Legendre 64pt f2_integrals: " << gauss_legendre_64pt( f2_integrals, start, end ) << endl << endl;

    vector< vector<double> > R3 = romberg_extrapolation( f3_integrals, -start, end, romberg_n, true );
    cout << "Adaptive quadrature f3_integrals: " << adaptive_quadrature( f3_integrals, start, end, epsilon_multiplier * epsilon ) << endl;
    cout << "Gauss-Legendre 64pt f3_integrals: " << gauss_legendre_64pt( f3_integrals, start, end ) << endl << endl;

    cout << "sqrt(x) from 0 to 1: " << adaptive_quadrature( [](double x){ return sqrt(x); }, 0, 1, epsilon_multiplier * epsilon ) << endl;

    cout << resetiosflags( ios::fixed | ios::scientific ) << setprecision( default_cout_precision);

    return 0;
}
#endif

double composite_simpsons_rule( function<double(double)> f, double a, double b, int n ){
    double h = ( b - a ) / n;
    double sum = f(a) + f(b);
    vector<double> xVals = { a, b };
    for( int j = 1; j <= n/2 - 1; j++ ){
       sum += 2 * f( a + (2 * j) * h );
    }
    for( int j = 1; j <= n/2; j++ ){
        sum += 4 * f( a + (2 * j - 1) * h );
    }
    
    return h / 3 * sum;
}

double tolerant_composite_simpsons_rule( function<double(double)> f, double a, double b, double tol, int maxIterations ){
    int n = 100;//Start with 100 intervals to hopefully converge faster

    double integral_old = composite_simpsons_rule( f, a, b, n );
    n += 2;
    double integral_new = composite_simpsons_rule( f, a, b, n );
    n += 2;
    while( abs( integral_new - integral_old ) > tol && n < maxIterations ){
        integral_old = integral_new;
        integral_new = composite_simpsons_rule( f, a, b, n );
        n += 2;
    }
    return integral_new;
}

double tolerant_romberg_extrapolation( function<double(double)> f, double a, double b, double tolerance ){
    int n_limit = 14;//Initial guess, expands as needed
    //I do nlimit+1 to account for 1-based indexing in the algorithm from the textbook
    //The algorithm is from the textbook, so I kept the 1-based indexing for easier translation
    vector< vector<double> > R( n_limit + 1, vector<double>(n_limit + 1, 0.0) );
    
    double h = b - a;
    R[1][1] = h / 2.0 * ( f(a) + f(b) );
    
    int i;
    for( i = 2; i <= n_limit; i++ ){
        if( i > n_limit )
            R.push_back( vector<double>(n_limit + 1, 0.0) );

        double sum = 0.0;
        for( int k = 1; k <= (int) pow(2, i-2); k++)
            sum += f( a + (k - 0.5) * h );
        
        R[i][1] = ( R[i-1][1] + h * sum ) / 2.0;

        for( int j = 2; j <= i; j++ )
            R[i][j] = R[i][j-1] + ( R[i][j-1] - R[i-1][j-1] ) / ( pow(4, j-1) - 1 );

        h = h / 2.0;
        if( abs( R[i][i] - R[i-1][i-1] ) < tolerance )
            return R[i][i];
    }

    return R[i-1][i-1];
}

vector< vector<double> > romberg_extrapolation( function<double(double)> f, double a, double b, int n, bool printTable ){
    //Algorithm taken from textbook
    //The algorithm is from the textbook, so I kept the 1-based indexing for easier translation
    vector< vector<double> > R( n + 1, vector<double>(n + 1, 0.0) );
    
    double h = b - a;
    R[1][1] = h / 2.0 * ( f(a) + f(b) );
    
    for( int i = 2; i <= n; i++ ){
        double sum = 0.0;
        for( int k = 1; k <= (int) pow(2, i-2); k++)
            sum += f( a + (k - 0.5) * h );
        
        R[i][1] = ( R[i-1][1] + h * sum ) / 2.0;

        for( int j = 2; j <= i; j++ )
            R[i][j] = R[i][j-1] + ( R[i][j-1] - R[i-1][j-1] ) / ( pow(4, j-1) - 1 );

        h = h / 2.0;
    }

    // Remove the 0th row and 0th column to convert back to 0-based indexing
    vector< vector<double> > result( n, vector<double>(n, 0.0) );
    for( int i = 1; i <= n; i++ ){
        for( int j = 1; j <= i; j++ ){
            result[i-1][j-1] = R[i][j];
        }
    }

    if( printTable ){
        cout << "Romberg Extrapolation Table:" << endl;
        for( vector<double> row : result ){
            for( double val : row )
                if( val != 0.0 )
                    cout << val << " ";
            cout << endl;
        }
    }
    
    return result;
}

double simpson_rule_third( function<double(double)> f, double a, double b ){
    return ( b - a ) / 6.0 * ( f(a) + 4 * f( (a+b)/2 ) + f(b) );
}

double adaptive_quadrature( function<double(double)> f, double a, double b, double tol  ){
    //Apply Adaptive Quadrature using Simpson's 1/3 Rule

    if( a == b )
        return 0.0;
    double parent = simpson_rule_third(f, a, b);
    double middle = ( a + b ) / 2;
    double left_child = simpson_rule_third(f, a, middle);
    double right_child = simpson_rule_third(f, middle, b);
    if( abs( parent - left_child - right_child ) < tol)
        return left_child + right_child;
    else
        return adaptive_quadrature(f, a, middle, tol / 2) + adaptive_quadrature(f, middle, b, tol / 2);
}

double gauss_legendre_64pt( function<double(double)> f, double a, double b ){
    double sum = 0, abscissas, weight;
    ifstream legendreIn("legendre_064.dat");
    //Algorithm taken from slides
    for( int x = 0; x < 64; x++ ){
        legendreIn >> abscissas >> weight;
        sum += weight * f( ((b-a) * abscissas + (a+b))/2 ) * (b-a)/2;
    }
    return sum;
}

double f1_integrals(double x){
    return 17.5 * pow(x,3) + 3 * x + 5;
}

double f2_integrals(double x){
    return cos(x) * x * x * tanh(x) / 9;
}

double f3_integrals(double x){
    return cos( 0.1 * x ) * pow( x, 3 );
}