// Troy Kleger
// CSC 460
// February 3, 2025
// Pyramid Scheme

#include <stdio.h>
int main(int argc, char *argv[])
{
int n = atoi(argv[1]), x, y, gen, childPid = 0;
if( n < 0 || n > 5 ){
	printf("User input number was %s.\nYou must enter a number no less than 0 and no greater than 5\n.", argv[1] );
	return 0;
}

printf("Gen\tPID\tPPID\n");

for( x = 0; x <= n; x++ ){
	for( y = 0; y < x; y++ ){
		childPid = fork();
		if( childPid == 0 )
			break;
	}
	if( childPid != 0 )
		break;
	else
		gen = x;
}

printf("%d\t%d\t%d\n",gen,getpid(),getppid());

sleep(1);

return 0;
}

