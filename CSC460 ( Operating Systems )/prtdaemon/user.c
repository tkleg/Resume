// Troy Kleger
// CSC 460
// March 12, 2025
// System Print Daemon - User

#include <sys/types.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/sem.h>
#include <string.h>

#define MUTEX 0
#define EMPTY 1
#define FULL 2
#define MAX_QUOTE_SIZE 150

#define FRONT 0
#define BACK 1
#define backIndex indexPtr[BACK]
#define bufferSize bufSizePtr[0]
#define backQuote quotePtr[backIndex]

struct quoteOTD{
	int pid;
	char fileName[20];
};

int main(int argc, char *argv[])
{

int i;


//this writes the originalPid to the file and sets it to a variable to allows for the originalProcess to be found again
int originalPid = getpid();

struct quoteOTD* quotePtr;
int * indexPtr, * bufSizePtr;

int myPID = getpid();
srand( myPID );

//create the file name. \a is used because this character should not be in a filename
//So the rm in daemon should onyl delete files created by users.
char myFileName[40] = "userFile";
char fileNameHelp[20];
sprintf( fileNameHelp, "%d", myPID );
strcat( myFileName, fileNameHelp );

//check if a daemon is currently running
FILE * in = fopen("idFile", "r");
if( in == NULL ){
	printf("daemon must be runnning before starting a user process.\n");
	return 1;
}

//read in semaphore and shared memory ids
int sem_id, bufShmid, indexShmid, bufSizeId;
fscanf(in, "%d%d%d%d", &sem_id, &bufShmid, &indexShmid, &bufSizeId );
fclose( in );

//attach shared memory pointers
quotePtr = (struct quoteOTD *) shmat(bufShmid, NULL, SHM_RND);
indexPtr = (int *) shmat( indexShmid, NULL, SHM_RND);
bufSizePtr = (int *) shmat( bufSizeId, NULL, SHM_RND);

//create the command to write the random quote to a file
char command[150] = "curl -s http://api.quotable.io/random | cut -d\":\" -f3 | cut -d\"\\\"\" -f2 > ";
strcat(command, myFileName);
strcat( command, "\0" );
system(command);

//create the quote struct for this user
struct quoteOTD myInfo;
myInfo.pid = getpid();
strcpy( myInfo.fileName, myFileName );

for( i = 0; i < 5; i++ ){
	p( EMPTY, sem_id );
	p( MUTEX, sem_id );

	int sleepTime = ( rand() % ( 5 - 2 + 1 ) ) + 2;
	printf("User %d is working for %d seconds.\n", myPID, sleepTime);
	sleep( sleepTime ); 

	printf("User %d is printing %s.\n", myPID, myFileName);
	backQuote = myInfo;

	backIndex = backIndex >=  bufferSize - 1 ? 0 : backIndex + 1; 

	v( MUTEX, sem_id );
	v( FULL, sem_id );
}

printf("User %d is logging off.\n", myPID );


return 0;

}



p(int s, int sem_id) { 

struct sembuf sops;

sops.sem_num = s;
sops.sem_op = -1;
sops.sem_flg = 0;

if((semop(sem_id, &sops, 1)) == -1) 
	printf("%s", "'P' error\n");

}

v(int s, int sem_id) {

struct sembuf sops;

sops.sem_num = s;
sops.sem_op = 1;
sops.sem_flg = 0;

if((semop(sem_id, &sops, 1)) == -1) 
	printf("%s","'V' error\n");

}
