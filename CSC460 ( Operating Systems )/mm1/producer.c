// Troy Kleger
// CSC 460
// April 30, 2025
// Memory Manager - Producer

#include "includes.h"

int size, time;

void checkForConsumer();

int main( int argc, char* argv[] ){

	if( argc != 3 ){
		printf("Two command line arguments are needed such that 1<=arg_1<=rows*cols and 1<=arg_2<=30.\n");
		return 1;
	}

	size = atoi( argv[1] ), time = atoi( argv[2] );

	if( time < 1 || time > 30 ){
		printf("The time entered must be an integer in the range [1,30].\n");
		return 1;
	}

	int rows, cols, sem_id, requestedId, stopMarkerId;
	FILE * idFile = fopen("ids", "r");
	if( idFile == NULL )
		return 1;

	fscanf(idFile, "%d%d%d%d%d%d%d%d%d%d", &rows, &cols, &sem_id, &requestedId, &stopMarkerId );
	fclose( idFile );

        int * stopMarkerPtr = (int *) shmat( stopMarkerId, NULL, SHM_RND );

	if ( stopMarker == STOP )
		return 0;

        checkForConsumer();

	if ( rows*cols < size ){
		printf("The size entered must be less than or equal to the rows*cols. rows = %d and cols = %d.\n", rows, cols);
		return 1;
	}

	struct job * requestedJob = (struct job *) shmat( requestedId, NULL, SHM_RND );
	
	printf("%d is requesting size %d blocks of RAM for %d seconds.\n", getpid(), size, time);;
	
	int mySemId = semget(IPC_PRIVATE, 1, 0777);
	if( mySemId == -1 ){
		printf("Cannot get sem_id\n");
		return 1;
	}
	semctl(mySemId, 0, SETVAL, 0);

	//write semId to a file so that stop my v the semaphore
	FILE * prodSemIds = fopen("prodSemIds", "a");
	fprintf(prodSemIds, "%d\n", mySemId);
	fclose( prodSemIds );

	struct job myJob;
	myJob.pid = getpid();
	myJob.size = size;
	myJob.sec = time;
	myJob.canOverwrite = false;
	myJob.semId = mySemId;

	p( MUTEX, sem_id );
		requestedJob[0] = myJob;
		v( REQUEST, sem_id );
	v( MUTEX, sem_id );

	p( 0, mySemId );
	
	if ( stopMarker != STOP )
		printf("%d finished my request of %d blocks for %d seconds.\n", getpid(), size, time);


	if ((semctl(mySemId, 0, IPC_RMID, 0)) == -1)
		printf("%s", "Parent: ERROR in removing producer sem\n");

	return 0;
}

void checkForConsumer(){
	FILE *checker = fopen("ids", "r");
	if( checker == NULL ){
		printf("No ids file can be found. Start running the consumer to create one.\n");
		exit(1);
	}
	fclose( checker );
}


p(int s, int sem_id) {
	struct sembuf sops;
	sops.sem_num = s;
	sops.sem_op = -1;
	sops.sem_flg = 0;
	if ((semop(sem_id, &sops, 1)) == -1)
		printf("%s", "'P' error\n");
}

v(int s, int sem_id) {
	struct sembuf sops;
	sops.sem_num = s;
	sops.sem_op = 1;
	sops.sem_flg = 0;
	if ((semop(sem_id, &sops, 1)) == -1)
		printf("%s","'V' error\n");
}
