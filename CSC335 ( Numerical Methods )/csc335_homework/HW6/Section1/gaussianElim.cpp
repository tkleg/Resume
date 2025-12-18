#include "gaussianElim.h"

#ifdef GAUSSIANELIM_CPP
int main(){
    DoubleMatrix augmentedMatrix = {
        {2, 1, -1, 8},
        {-3, -1, 2, -11},
        {-2, 1, 2, -3}
    };
    DoubleMatrix solution = gaussianElim( augmentedMatrix );
    cout << "Solution:" << endl;
    printMatrix(solution);
    

    augmentedMatrix = {
        {2.11, -4.21, 0.921, 2.01},
        {4.01, 10.2, -1.12, -3.09},
        {1.09, 0.987, 0.832, 4.21}
    };
    vector<double> pivotSolution = gaussianElimPartialPivot( augmentedMatrix, true );
    cout << "\nSolution with Scaled Partial Pivoting:" << endl;
    for(double val : pivotSolution)
        cout << val << endl;

    augmentedMatrix = {
        {1, 2, -1, 1, 0, 0},
        {2, 1, 0, 0, 1, 0},
        {-1, 1, 2, 0, 0, 1}
    };
    DoubleMatrix multiSolution = gaussianElim( augmentedMatrix );
    cout << "\nMultiple Solutions:" << endl;
    printMatrix(multiSolution);

    return 0;
}
#endif

DoubleMatrix gaussianElim( DoubleMatrix augmentedMatrix, bool enableSwaps, bool printAfterElim, RoundingMode roundingMode, int precision ){
    int n = augmentedMatrix.size();
    //Size of each vector in solution is number of columns - number of rows
    //This allows for solving multiple systems with the same coefficient matrix
    DoubleMatrix solution(n, vector<double>( augmentedMatrix[0].size() - n ));

    for( int i = 1; i <= n - 1; i++ ){
        if( enableSwaps ){
            bool swapped = false;// Check for zero pivot and swap if necessary
            for( int p = i; p <= n; p++ ){
                if( augmentedMatrix[p-1][i-1] != 0 ){
                    if( p == i ){
                        swapped = true; 
                        break;
                    }
                    vector<double> tempRow = augmentedMatrix[i-1];
                    augmentedMatrix[i-1] = augmentedMatrix[p-1];
                    augmentedMatrix[p-1] = tempRow;
                    swapped = true; 
                    printMatrix(augmentedMatrix);
                    break;
                }
            }
            if( !swapped ){
                cout << "No unique solution exists." << endl;
                exit(1);
            }
        }

        for( int j = i + 1; j <= n; j++ ){
            double m = safeBasicOps( augmentedMatrix[j-1][i-1], augmentedMatrix[i-1][i-1], roundingMode, DIVIDE, precision );
            vector<double> rowToScale = vector<double>(augmentedMatrix[i-1].size());
            transform(augmentedMatrix[i-1].begin(), augmentedMatrix[i-1].end(), rowToScale.begin(), [m, roundingMode, precision](double val) { 
                return safeBasicOps( -val, m, roundingMode, MULTIPLY, precision ); });
            augmentedMatrix[j-1] = vector_sum(augmentedMatrix[j-1], rowToScale, roundingMode, precision);
        }
        if( printAfterElim ){
            cout << "\nAugmented Matrix after eliminating column " << i << ":" << endl;
            printMatrix(augmentedMatrix);
        }
    }

    if( augmentedMatrix[n-1][n-1] == 0 ){
        cout << "No unique solution exists." << endl;
        exit(1);
    }

    //Pulling out the coefficients to solve the solutions
    DoubleMatrix coeffsOnly(n, vector<double>(n));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            coeffsOnly[i][j] = augmentedMatrix[i][j];

    DoubleMatrix constantsOnly(n, vector<double>(augmentedMatrix[0].size() - n));
    for(int i = 0; i < n; i++)
        for(int j = n; j < augmentedMatrix[0].size(); j++)
            constantsOnly[i][j - n] = augmentedMatrix[i][j];
        
    for(int solutionIndex = 0; solutionIndex < constantsOnly[0].size(); solutionIndex++){
        //Creates an augmented matrix for each system to solve
        DoubleMatrix currentMatrix(n, vector<double>(n + 1));
        for(int row = 0; row < n; row++){
            for(int col = 0; col < n; col++)
                currentMatrix[row][col] = coeffsOnly[row][col];
            currentMatrix[row][n] = constantsOnly[row][solutionIndex];
        }
        solution[n-1][solutionIndex] = safeBasicOps( currentMatrix[n-1][n], currentMatrix[n-1][n-1], roundingMode, DIVIDE, precision );
        for( int i = n - 1; i >= 1; i-- ){
            double sum = 0;
            for( int j = i + 1; j <= n; j++ ){
                double temp = safeBasicOps( currentMatrix[i-1][j-1], solution[j-1][solutionIndex], roundingMode, MULTIPLY, precision );
                sum = safeBasicOps( sum, temp, roundingMode, ADD, precision );
            }
            double numerator = safeBasicOps( currentMatrix[i-1][n], sum, roundingMode, SUBTRACT, precision );
            solution[i-1][solutionIndex] = safeBasicOps( numerator, currentMatrix[i-1][i-1], roundingMode, DIVIDE, precision );
        }

    }

    return solution;

}

vector<float> gaussianElim( FloatMatrix augmentedMatrix, bool enableSwaps, bool printAfterElim, RoundingMode roundingMode, int precision ){
    int n = augmentedMatrix.size();
    vector<float> solution(n);

    for( int i = 1; i <= n - 1; i++ ){
        if( enableSwaps ){
            bool swapped = false;// Check for zero pivot and swap if necessary
            for( int p = i; p <= n; p++ ){
                if( augmentedMatrix[p-1][i-1] != 0 ){
                    if( p == i ){
                        swapped = true; 
                        break;
                    }
                    vector<float> tempRow = augmentedMatrix[i-1];
                    augmentedMatrix[i-1] = augmentedMatrix[p-1];
                    augmentedMatrix[p-1] = tempRow;
                    swapped = true; 
                    printMatrix(augmentedMatrix);
                    break;
                }
            }
            if( !swapped ){
                cout << "No unique solution exists." << endl;
                exit(1);
            }
        }

        for( int j = i + 1; j <= n; j++ ){
            float m = safeBasicOps( augmentedMatrix[j-1][i-1], augmentedMatrix[i-1][i-1], roundingMode, DIVIDE, precision );
            vector<float> rowToScale = vector<float>(augmentedMatrix[i-1].size());
            transform(augmentedMatrix[i-1].begin(), augmentedMatrix[i-1].end(), rowToScale.begin(), [m, roundingMode, precision](float val) { 
                return safeBasicOps( -val, m, roundingMode, MULTIPLY, precision ); });
            augmentedMatrix[j-1] = vector_sum(augmentedMatrix[j-1], rowToScale, roundingMode, precision);
        }
        if( printAfterElim ){
            cout << "\nAugmented Matrix after eliminating column " << i << ":" << endl;
            printMatrix(augmentedMatrix);
        }
    }

    if( augmentedMatrix[n-1][n-1] == 0 ){
        cout << "No unique solution exists." << endl;
        exit(1);
    }

    solution[n-1] = safeBasicOps( augmentedMatrix[n-1][n], augmentedMatrix[n-1][n-1], roundingMode, DIVIDE, precision );

    for( int i = n - 1; i >= 1; i-- ){
        float sum = 0;
        for( int j = i + 1; j <= n; j++ ){
            float temp = safeBasicOps( augmentedMatrix[i-1][j-1], solution[j-1], roundingMode, MULTIPLY, precision );
            sum = safeBasicOps( sum, temp, roundingMode, ADD, precision );
        }
        float numerator = safeBasicOps( augmentedMatrix[i-1][n], sum, roundingMode, SUBTRACT, precision );
        solution[i-1] = safeBasicOps( numerator, augmentedMatrix[i-1][i-1], roundingMode, DIVIDE, precision );
    }

    return solution;

}

vector<double> vector_sum(vector<double> v1, vector<double> v2, RoundingMode roundingMode, int precision){
    if(v1.size() != v2.size()) {
        cout << "Error: Vectors must be of the same size to add." << endl;
        exit(1);
    }

    vector<double> result(v1.size());
    for(int i = 0; i < v1.size(); i++) {
        result[i] = safeBasicOps(v1[i], v2[i], roundingMode, ADD, precision);
    }
    return result;
}

vector<float> vector_sum(vector<float> v1, vector<float> v2, RoundingMode roundingMode, int precision){
    if(v1.size() != v2.size()) {
        cout << "Error: Vectors must be of the same size to add." << endl;
        exit(1);
    }

    vector<float> result(v1.size());
    for(int i = 0; i < v1.size(); i++) {
        result[i] = safeBasicOps(v1[i], v2[i], roundingMode, ADD, precision);
    }
    return result;
}

void printMatrix( DoubleMatrix matrix ){
    int rows = matrix.size();
    int cols = matrix[0].size();

    for( vector<double> row : matrix ){
        cout << "| ";
        for( double val : row ){
            cout << setw(10) << val << " ";
        }
        cout << '|' << endl;
    }

}

void printMatrix( FloatMatrix matrix ){
    int rows = matrix.size();
    int cols = matrix[0].size();

    for( vector<float> row : matrix ){
        cout << "| ";
        for( float val : row ){
            cout << setw(10) << val << " ";
        }
        cout << '|' << endl;
    }

}

vector<double> gaussianElimPartialPivot( DoubleMatrix augmentedMatrix, bool scaled, bool printAfterElim, RoundingMode roundingMode, int precision ){
    int n = augmentedMatrix.size();
    vector<double> solution(n);

    for( int i = 1; i <= n - 1; i++ ){

        //Start pivoting
        int valueToPass = abs( augmentedMatrix[i-1][i-1] );
        if( scaled ){
            double maxInRow = abs( augmentedMatrix[i-1][0] );
            for( int col = 1; col <= n; col++ ){
                if( abs( augmentedMatrix[i-1][col-1] ) > maxInRow )
                    maxInRow = abs( augmentedMatrix[i-1][col-1] );
            }
            valueToPass = valueToPass / maxInRow;
        }
        for( int p = i+1; p <= n; p++ ){//Starting at i+1 instead of i since row i is put into the max position initially
            double valueToCompare = abs( augmentedMatrix[p-1][i-1] );
            if( scaled ){
                double maxInRow = abs( augmentedMatrix[p-1][0] );
                for( int col = 1; col <= n; col++ ){
                    if( abs( augmentedMatrix[p-1][col-1] ) > maxInRow )
                        maxInRow = abs( augmentedMatrix[p-1][col-1] );
                }
                valueToCompare = valueToCompare / maxInRow;
            }
            if( valueToCompare > valueToPass ){
                cout << "Pivoting: Swapping row " << i << " with row " << p << endl;
                vector<double> tempRow = augmentedMatrix[i-1];
                augmentedMatrix[i-1] = augmentedMatrix[p-1];
                augmentedMatrix[p-1] = tempRow;
            }
        }
        //End pivoting

        for( int j = i + 1; j <= n; j++ ){
            double m = safeBasicOps( augmentedMatrix[j-1][i-1], augmentedMatrix[i-1][i-1], roundingMode, DIVIDE, precision );
            vector<double> rowToScale = vector<double>(augmentedMatrix[i-1].size());
            transform(augmentedMatrix[i-1].begin(), augmentedMatrix[i-1].end(), rowToScale.begin(), [m, roundingMode, precision](double val) { 
                return safeBasicOps( -val, m, roundingMode, MULTIPLY, precision ); });
            augmentedMatrix[j-1] = vector_sum(augmentedMatrix[j-1], rowToScale, roundingMode, precision);
        }
        if( printAfterElim ){
            cout << "\nAugmented Matrix after eliminating column " << i << ":" << endl;
            printMatrix(augmentedMatrix);
        }
    }

    if( augmentedMatrix[n-1][n-1] == 0 ){
        cout << "No unique solution exists." << endl;
        exit(1);
    }

    solution[n-1] = safeBasicOps( augmentedMatrix[n-1][n], augmentedMatrix[n-1][n-1], roundingMode, DIVIDE, precision );

    for( int i = n - 1; i >= 1; i-- ){
        double sum = 0;
        for( int j = i + 1; j <= n; j++ ){
            double temp = safeBasicOps( augmentedMatrix[i-1][j-1], solution[j-1], roundingMode, MULTIPLY, precision );
            sum = safeBasicOps( sum, temp, roundingMode, ADD, precision );
        }
        double numerator = safeBasicOps( augmentedMatrix[i-1][n], sum, roundingMode, SUBTRACT, precision );
        solution[i-1] = safeBasicOps( numerator, augmentedMatrix[i-1][i-1], roundingMode, DIVIDE, precision );
    }

    return solution;

}