// Troy Kleger
// CSC 460
// February 12, 2025
// Slow Synchronization

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

int n = atoi(argv[1]), x, a = 0;
FILE *out = fopen("syncfile", "w"), *in;

if( n < 1 || n > 26 ){
        printf("User input number was %d.\nYou must enter a number no less than 1 and no greater than 26\n.", n );
        return 0;
}

//this writes the originalPid to the file and sets it to a variable to allows for the originalProcess to be found again
int originalPid = getpid();
fprintf(out, "%d", originalPid);
fclose(out);

char ch = 'A';

for( x = 1; x < n; x++ ){
	a = fork();
	if( a == 0 )
		ch++;
	else break;
}

x = 0;
int myPID = getpid(), filePid;

while ( true ){
	in = fopen("syncfile", "r");
	fscanf(in, "%d", &filePid);
	fclose(in);
	if( filePid == myPID ){ 
		out = fopen("syncfile", "w");
		printf("%c:%d\n", ch, myPID );
		if ( a == 0 )//only true for final child with no children
			fprintf(out, "%d", originalPid );
		else
			fprintf(out, "%d", a );
		fclose(out);
		if( ++x == n )
			break;
	}
}

usleep(200000);
if ( a == 0 )//this process will always be last process created so it has the last print statement
	system("rm syncfile");

return 0;
}

