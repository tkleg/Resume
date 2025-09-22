// Troy Kleger
// CSC 460
// March 12, 2025
// System Print Daemon - Daemon

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MUTEX 0
#define EMPTY 1
#define FULL 2

#define MAX_QUOTE_SIZE 150

#define FRONT 0
#define BACK 1

#define GO 0
#define STOP 1

#define frontIndex indexPtr[FRONT]
#define backIndex indexPtr[BACK]
#define stopMarker stopMarkerPtr[0]
#define frontPtr ptr[frontIndex]

struct quoteOTD{
	int pid;
        char fileName[20];
};


int main(int argc, char* argv[])
{

if( argc != 2 ){
	printf("Error: Exactly one parameter should be entered. It must be a number 1-10.\n");
	return 0;
}

int     i, sem_id;
int bufferSize = atoi(argv[1]), a;
if( bufferSize < 1 || bufferSize > 10 ){
	printf("Error: Daemon requires a number 1-10.\n." );
	return 0;
}

FILE *checker = fopen("idFile", "r");
if( checker != NULL ){
	printf("An instance of daemon is already running and has create the idFile.\nStop it before running a new daemon process.\n");
	return 1;
}
//  Ask OS for semaphores.
sem_id = semget (IPC_PRIVATE, 3, 0777);

//  See if you got the request.
if (sem_id == -1)
   {
    printf("%s","SemGet Failed.\n");
    return (-1);
   }

//  Initialize your sems.
semctl(sem_id, MUTEX, SETVAL, 1); 
semctl(sem_id, EMPTY, SETVAL, bufferSize);
semctl(sem_id, FULL, SETVAL, 0);

struct quoteOTD * ptr;

//initialize our shared memory for the buffer
int bufShmid = shmget(IPC_PRIVATE, sizeof(struct quoteOTD)*bufferSize, 0770); 
ptr = (struct quoteOTD *) shmat(bufShmid, NULL, SHM_RND);

//create and set the index shared memory
int indexShmid = shmget(IPC_PRIVATE, sizeof(int)*2, 0770);
int * indexPtr = (int *) shmat(indexShmid, NULL, SHM_RND);
frontIndex = 0;
backIndex = 0;

//create and initialize the bufferSize shared memory
int bufSizeShmid = shmget(IPC_PRIVATE, sizeof(int), 0770);
int * bufSizePtr = (int *) shmat(bufSizeShmid, NULL, SHM_RND);
bufSizePtr[0] = bufferSize;

//create and initialize the stopMarker shared memory
int stopMarkerId = shmget(IPC_PRIVATE, sizeof(int), 0770);
int * stopMarkerPtr = (int *) shmat(stopMarkerId, NULL, SHM_RND);
stopMarker = GO;

//write the semaphore and shared memory ids out to idFile
FILE *out = fopen("idFile", "w");
if( out == NULL )
	printf("failed file\n");
fprintf( out,"%d\n%d\n%d\n%d\n%d\n%d\n", sem_id, bufShmid, indexShmid, bufSizeShmid, stopMarkerId, getpid() );
fclose( out );

char command[20];

while(1){
	p( FULL, sem_id );

	if( stopMarker == STOP )//only true after stop runs 
                break;

	p( MUTEX, sem_id );

	strcpy( command, "cat " );
	strcat( command, frontPtr.fileName );

	frontIndex = frontIndex >= bufferSize - 1 ? 0 : frontIndex + 1;

	printf("User %d's file is printing.\n", frontPtr.pid);
	system(command);

	v( MUTEX, sem_id );
	v( EMPTY, sem_id );
}

if ((semctl(sem_id, 0, IPC_RMID, 0)) == -1)
	printf("%s", "Parent: ERROR in removing sem\n");

if ((shmctl(bufShmid, IPC_RMID, NULL)) == -1) 
	printf("ERROR removing bufffer shmem.\n");

if ((shmctl(indexShmid, IPC_RMID, NULL)) == -1)
	printf("ERROR removing index shmem.\n");

if ((shmctl(bufSizeShmid, IPC_RMID, NULL)) == -1)
	printf("ERROR removing buffer size shmem.\n");

if ((shmctl(stopMarkerId, IPC_RMID, NULL)) == -1)
        printf("ERROR removing stop marker shmem.\n");

//deletes the files used by the users to hold their files
char rmCommand[30];
char digit[2];
for( i = 1; i < 10; i++ ){
	strcpy( rmCommand, "rm userFile" );
	sprintf(digit, "%d", i );
	strcat( rmCommand, digit);
	strcat( rmCommand, "* &> /dev/null" );
	system( rmCommand );
}

system( "rm idFile" );

return 0;

}

p(int s, int sem_id)
{
struct sembuf sops;

sops.sem_num = s;
sops.sem_op = -1;
sops.sem_flg = 0;
if((semop(sem_id, &sops, 1)) == -1) printf("%s", "'P' error\n");
}

v(int s, int sem_id)
{
struct sembuf sops;

sops.sem_num = s;
sops.sem_op = 1;
sops.sem_flg = 0;
if((semop(sem_id, &sops, 1)) == -1) printf("%s","'V' error\n");
}


