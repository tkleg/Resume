// Troy Kleger
// CSC 460
// February 17, 2025
// Faster Synchronization

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define TURN shmem[0]

int main(int argc, char *argv[])
{

int i, shmid, *shmem;

int n = atoi(argv[1]), x, a = 0;

if( n < 1 || n > 26 ){
        printf("User input number was %d.\nYou must enter a number no less than 1 and no greater than 26\n.", n );
        return 0;
}

//this writes the originalPid to the file and sets it to a variable to allows for the originalProcess to be found again
int originalPid = getpid();

shmid  =  shmget(IPC_PRIVATE, sizeof(int), 0770);
shmem = (int *) shmat(shmid, NULL, SHM_RND);
TURN = originalPid;

char ch = 'A';

for( x = 1; x < n; x++ ){
	a = fork();
	if( a == 0 )
		ch++;
	else break;
}

x=0;
int myPID = getpid();

while (1){
	if( TURN == myPID ){ 
		printf("%c:%d\n", ch, myPID );
		if ( a == 0 )//only true for final child with no children
			TURN = originalPid;
		else
			TURN = a;
		if( ++x == n )
			break;
	}
}

if (originalPid == getpid())         // ONLY need one process to do this
if ((shmctl(shmid, IPC_RMID, NULL)) == -1)
    printf("ERROR removing shmem.\n");

return 0;
}

