#include "roundingCalc.h"

#ifdef ROUNDINGCALC_CPP

int main() {
    cout << "We are computing a+b, a-b, a*b, a/b." << endl;
    cout << "Enter a: ";
    double a;
    cin >> a;
    cout << "Enter b: ";
    double b;
    cin >> b;
    cout << "Enter max precision to calculate: ";
    int maxPrecision;
    cin >> maxPrecision;
    cout << fixed << setprecision(10);
    cout << "Safe Basic Ops Test" << endl;
    vector< vector<double> > results;
    for( int precision = 0; precision <= maxPrecision; precision++ )
        results.push_back( {
            precision,
            safeBasicOps(a, b, ROUND, ADD, precision),
            safeBasicOps(a, b, CHOP, ADD, precision),
            safeBasicOps(a, b, ROUND, SUBTRACT, precision),
            safeBasicOps(a, b, CHOP, SUBTRACT, precision),
            safeBasicOps(a, b, ROUND, MULTIPLY, precision),
            safeBasicOps(a, b, CHOP, MULTIPLY, precision),
            safeBasicOps(a, b, ROUND, DIVIDE, precision),
            safeBasicOps(a, b, CHOP, DIVIDE, precision)
        } );

    vector<int> opWidths = {10, 13, 13, 13, 13, 13, 13, 13, 13};
    cout << setw(opWidths[0]) << "Precision" << " |"
        << setw(opWidths[1]) << "R_Add" << " |"
        << setw(opWidths[5]) << "C_Add" << " |"
        << setw(opWidths[2]) << "R_Subtract" << " |"
        << setw(opWidths[6]) << "C_Subtract" << " |"
        << setw(opWidths[3]) << "R_Multiply" << " |"
        << setw(opWidths[7]) << "C_Multiply" << " |"
        << setw(opWidths[4]) << "R_Divide" << " |"
        << setw(opWidths[8]) << "C_Divide" << " |" << endl;
    int totalWidth = 9;//accounting for the spaces and pipes
    for( int w : opWidths )
        totalWidth += w + 1;
    string separator(totalWidth, '-');
    cout << separator << endl;
    for( vector<double> row : results ){
        cout << setw(opWidths[0]) << (int) row[0] << " |";
        for( int i = 1; i < row.size(); i++ )
            cout << setw(opWidths[i]) << row[i] << " |";
        cout << endl;
    }
    return 0;
}
#endif // ROUNDINGCALC_CPP

double safeBasicOps(double a, double b, RoundingMode mode, Operation op, int precision){
    double result;
    switch(op){
        case ADD:
            result = a + b;
            break;
        case SUBTRACT:
            result = a - b;
            break;
        case MULTIPLY:
            result = a * b;
            break;
        case DIVIDE:
            if(b == 0)
                throw invalid_argument("Division by zero in safeBasicOps with args: " + to_string(a) + ", " + to_string(b) + ", RoundingMode " + to_string(mode) + ", precision " + to_string(precision));
            result = a / b;
            break;
        default:
            cout << "Invalid operation: " << op << ". Exiting." << endl;
            exit(1);
    }
    return applyRounding(result, mode, precision);
}

float safeBasicOps(float a, float b, RoundingMode mode, Operation op, int precision){
    float result;
    switch(op){
        case ADD:
            result = a + b;
            break;
        case SUBTRACT:
            result = a - b;
            break;
        case MULTIPLY:
            result = a * b;
            break;
        case DIVIDE:
            if(b == 0)
                throw invalid_argument("Division by zero in safeBasicOps with args: " + to_string(a) + ", " + to_string(b) + ", RoundingMode " + to_string(mode) + ", precision " + to_string(precision));
            result = a / b;
            break;
        default:
            cout << "Invalid operation: " << op << ". Exiting." << endl;
            exit(1);
    }
    return applyRounding(result, mode, precision);
}


double applyRounding(double value, RoundingMode mode, int precision){
    if(precision <= 0)
        return value;

    //Shifting value so the sig figs we want to keep are before the decimal
    //w is just a temporary variable to assist in this calculation. no meaning to the name
    //w is the number of places to shift the decimal to the right to get 1 significant figure before the decimal
    double w = value == 0 ? 0 : ceil( -log10( fabs(value) ) );
    int shift = w + precision - 1;
    double factor = pow(10, shift);

    switch(mode){
        case NONE:
            return value;
        case CHOP:
            return trunc(value * factor) / factor;
        case ROUND:
            return round(value * factor) / factor;
        default:
            cout << "Invalid RoundingMode" << endl;
            return value;
    }
}

float applyRounding(float value, RoundingMode mode, int precision){
    if(precision <= 0)
        return value;

    //Shifting value so the sig figs we want to keep are before the decimal
    //w is just a temporary variable to assist in this calculation. no meaning to the name
    //w is the number of places to shift the decimal to the right to get 1 significant figure before the decimal
    float w = value == 0 ? 0 : ceil( -log10( fabs(value) ) );
    int shift = w + precision - 1;
    float factor = pow(10, shift);

    switch(mode){
        case NONE:
            return value;
        case CHOP:
            return trunc(value * factor) / factor;
        case ROUND:
            return round(value * factor) / factor;
        default:
            cout << "Invalid RoundingMode" << endl;
            return value;
    }
}