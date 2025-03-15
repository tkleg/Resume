// Troy Kleger
// CSC 460
// February 8, 2025
// Alpha Squared

#include <stdio.h>
int main(int argc, char *argv[])
{
int n = atoi(argv[1]), x, a, childPid = 0;
if( n < 1 || n > 26 ){
	printf("User input number was %s.\nYou must enter a number no less than 1 and no greater than 26\n.", argv[1] );
	return 0;
}

char ch = 'A';

for( x = 1; x < n; x++ ){
	a = fork();
	if( a == 0 )
		ch += 1;
	else break;
}

for( x = 0 ; x < n ; x++ )
	printf("%c:%d\n", ch, getpid() );

sleep(1);
return 0;
}

