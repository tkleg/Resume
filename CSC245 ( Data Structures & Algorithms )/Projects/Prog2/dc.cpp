#include<iostream>
#include<cstdlib>
#include<cctype>
#include<vector>
#include<string>
#include "stack.h"
#include "dsexceptions.h"
using namespace std;

bool isOperator( char c );
//pre-conditions: char c is initialzed
//post-conditions: returns true if 'c' is an operator which the calculator can be use, otherwise it returns false

bool isCommand( char c );
//pre-conditions: char c is initialized
//post-conditions: returns true if 'c' is a command which the calculator can used, otherwise it returns false;

string getInt( string linePart );
//pre-conditions: the first character in linePart is either an underscore or a digit
//post-conditions: a string representation of the integer at the front of linePart is returned.

void runLine( string line, Stack<int> & stack );
//pre-conditions: line holds a full line from the input and the stack is initialized
//post-conditions: the tokens retrieved from 'line' are processed by the calculator, any numbers from the line get pushed into the stack. Error messages get printed for any invalid characters, stray underscores, and division by zero

string getToken( string & line );
//pre-conditions: line is initialized and holds at least part of the a single line from input
//post:conditions: one token from the front of the line is returned if the front of 'line' has a valid token for the calculator. Otherwise an appropriate string is returned detailing the error so that runLine can print an appropriate error message. The returned also is pulled off the front of 'line'

void processToken( string token, Stack<int> & stack );
//pre-conditions: 'token' hold a valid token to be processed by the calculator, stack must be initialized.
//post-conditins: 'token' takes some action on the 'stack' depending on what 'token''s value is. Unless there is a divide by zero, the stack is full and more items get pushed, or the stack is not full enough to perform the operations prescribed by 'token'

void processInt( string token, Stack<int> & stack );
//pre-conditions: 'x' holds a value from the input and 'stack' is initialized.
//post-conditions: 'x' is pushed onto 'stack' as long as 'stack' is not full. If it is full, then it throws an exception to be caught by another method which tells the user that 'stack' is full

void processCommand( char c , Stack<int> & stack );
//pre-conditions: 'c' holds a valid command for the calculator and 'stack' is initialized
//post-conditions: an action determined by the value of 'c' is taken on 'stack'. If there is an error, an exception is thrown to be caught by another method so that an apparopriate error message prints out

void processOperator( char c, Stack<int> & stack );
//pre-conditions: 'c' hold a valid operator for the calculator and 'stack' is initialized.
//post-conditions: If 'stack' has at least two variable and there is no divison by zero occuring, a math operation occurs ( the operation that occurs depends on 'c' ). Otherwise, an exception is thrown to be caught by another method so that an appropriate erorr message can be printed

Stack<int> flipStack( Stack<int> stack );
//pre-conditions: 'stack' is not null.
//post-conditions: a new Stack<int> object is returned which holds all of the values of 'stack', but in reverse.



class invalidChar{
public:
       invalidChar( char c ) : stray(c){}
       string getMessage(){
		return "Invalid Input: '" + string(1,stray) + "' is not a valid character. This character will be ignored by the calculator.";
	}
	
private:
	char stray;

};

class stray_{//when an underscore is not followed immediately by a digit
public:
	stray_(){}
	string getMessage(){
		return "Underscores must be followed by a digit.";
	}
};


int main(){

string line;
Stack<int> myStack(10);
while( cin ){
	getline( cin, line );
	runLine( line, myStack );
}//the vector is used so that nothing gets printed until ctrl+d is hit and all the lines of input are used

return 0;
}

void runLine( string line, Stack<int> & stack ){
	string token;
	while( line.length() != 0 ){	
		try{
			token = getToken( line );
		}catch( invalidChar e ){
			cout << e.getMessage() << endl;
			continue;
		}catch( stray_ e ){
			cout << e.getMessage() << endl;
			continue;
		}
		if( token != "whitespace1" /*&& token != ""*/ )
			processToken( token, stack );
	}
}

string getToken( string & line ){
	char c = line[0];
	if( isOperator( c ) || isCommand( c ) ){
	       	line = line.substr(1);
		return string( 1, c );
	}
	else if( isdigit( c ) || c == '_' ){
        	string num = getInt( line );
		if( num == "_" ){
			line = line.substr(1);
			throw stray_();
		}
		else
			line = line.substr( num.length() );//chops the integer pulled from the line off of the line
		return num;
	}else if( c == ' ' || c == '\t' ){//handles whitespace
   		line = line.substr(1);
		return "whitespace1";
	}
        else{
		line = line.substr(1);
		throw invalidChar( c );
	}

}

void processToken( string token, Stack<int> & stack ){
	char c = token[0];	
	try{
		/*if( ( c == '-' && token.length() != 1 ) || isdigit( c ) )
			processInt( atoi( token.c_str() ), stack );	
		*/if( isCommand( c ) )
			processCommand( c, stack );
		else if( isOperator( c ) )
			processOperator( c , stack );
		else	
			processInt( token , stack );
	}catch( Overflow e ){
		cout << "\nThe stack is already full. Ignoring token (" << token << ").\n";
	}catch( Underflow e ){
		cout << "\nThe stack is not full enough to perform the necessary operation. Ignoring token (" << token << ").\n";
	}catch( DivisionByZero e ){
		cout << "\nCannot divide by zero. Multiplying other operator by 1 instead.\n";
	}
}

void processInt( string token, Stack<int> & stack ){
	if( stack.isFull() )
		throw Overflow();
	if( token[0] == '_' )
		token = "-" + token.substr(1);
	stack.push( atoi( token.c_str() ) );
}

void processCommand( char c, Stack<int> & stack ){
	int x, y;
	Stack<int> temp;
	switch( c ){
		case 'p':
			if( stack.isEmpty() )
				throw Underflow();
			cout << stack.top() << endl;
		break;
		case 'n':
			if( stack.isEmpty() )
				throw Underflow();
			cout << stack.topAndPop() << " ";
		break;
		case 'f':
			if( stack.isEmpty() )
				return;
			temp = flipStack( stack );
			while( ! stack.isEmpty() )
				cout << stack.topAndPop() << endl;
			stack = flipStack( temp );
		break;
		case 'c':
			stack.makeEmpty();
		break;
		case 'd':
			if( stack.isEmpty() )
				throw Underflow();
			if( stack.isFull() )
				throw Overflow();
			stack.push( stack.top() );
		break;
		case 'r':
			if( stack.isEmpty() )
				return;
			x = stack.topAndPop();
			if( stack.isEmpty() ){
				stack.push( x );
				return;
			}
			y = stack.topAndPop();
			stack.push( x );
			stack.push( y );
		break;	
	}					
}

void processOperator( char c, Stack<int> & stack ){
	int x, y, z;
	if( stack.isEmpty() )
		throw Underflow();
	switch( c ){
		case '+':
			x = stack.topAndPop();
			if( stack.isEmpty() ){
				stack.push( x );
				throw Underflow();
			}	
			y = stack.topAndPop();
			z = x+y;
		break;
		case '-':
                        x = stack.topAndPop();
                        if( stack.isEmpty() ){
                                stack.push( x );
                                throw Underflow();
                        }
                        y = stack.topAndPop();
			z = y-x;
                break;
		case '*':
                        x = stack.topAndPop();
                        if( stack.isEmpty() ){
                                stack.push( x );
                                throw Underflow();
                        }
                        y = stack.topAndPop();
                        z = x*y;
                break;
		case '/':
                        x = stack.topAndPop();
			if( x == 0 )
				throw DivisionByZero();
                        if( stack.isEmpty() ){
                                stack.push( x );
                                throw Underflow();
                        }
                        y = stack.topAndPop();
                        z = y/x;
                break;
		case '%':
                        x = stack.topAndPop();
			if( x == 0 )
                                throw DivisionByZero();
                        if( stack.isEmpty() ){
                                stack.push( x );
                                throw Underflow();
                        }
                        y = stack.topAndPop();
                        z = y%x;
                break;
	}
	stack.push( z );

}

Stack<int> flipStack( Stack<int> stack ){
	Stack<int> newStack;
	while( ! stack.isEmpty() )
		newStack.push( stack.topAndPop() );
	return newStack;
}

bool isOperator( char c ){
	return (c == '+' || c == '-' || c == '/' || c == '%' || c == '*');
}

bool isCommand( char c ){
	return (c == 'p' || c == 'n' || c == 'f' || c == 'd' || c == 'r' || c == 'c');
}

string getInt( string linePart ){
	string num = "";
	//bool neg = false;
	if( linePart[0] == '_' ){
		//neg = true;
		num += '_';
		linePart = linePart.substr(1);
	}
	while( linePart.length() != 0  && isdigit( linePart[0] ) ){
		num += linePart[0];
		linePart = linePart.substr(1);
	} 
	//if( neg )
	//	num = "_"+num;
	return num;
	
}

