// Troy Kleger
// CSC 460
// April 30, 2025
// Memory Manager - Consumer

#include "includes.h"

void checkForConsumer();

void printRAM();

void placeInRAM();

void initializeRAM();

void initializeRequestedJob();

void printJobs();

bool fit();

void initializeJobsInRAM();

void removeFromRAM();

int rows, cols, bufferSize;

char * RAM;
struct job * jobsInRAM;
struct job * requestedJob;
char * idPtr;
int * numInRAMPtr;
int sem_id;
int * timerPtr;

int main(int argc, char* argv[]){

	if (argc != 4){
		printf("Three commmand line arguments are needed such that 1<=arg_1<=20, 1<=arg_2<=50, and 1<=arg_3<=26.\n");
		return 1;
	}

	rows = atoi( argv[1] ), cols = atoi( argv[2] ), bufferSize = atoi( argv[3] );

	if( rows < 1 || rows > 20 ){
		printf("An integer in the range [1,20] must be entered for the first argument, giving the row count of RAM\n");
		return 1;
	}
	if( cols < 1 || cols > 50 ){
		printf("An integer in the range [1,50] must be entered for the second argument, giving the column count of RAM\n");
                return 1;
	}
	if( bufferSize < 1 || bufferSize > 26 ){
		printf("An integer in the range [1,26] must be entered for the second argument, giving the job buffer size\n");
                return 1;
	}
	checkForConsumer();

	int timerId = shmget(IPC_PRIVATE, 1, 0770);
	timerPtr = (int *) shmat( timerId, NULL, SHM_RND );
	timer = 0;

	int ramId = shmget(IPC_PRIVATE, rows*cols+1, 0770);
	RAM = (char *) shmat( ramId, NULL, SHM_RND );
	initializeRAM();

	int bufferId = shmget(IPC_PRIVATE, sizeof(struct job)*bufferSize, 0770);
	struct job * bufferPtr = (struct job *) shmat(bufferId, NULL, SHM_RND);

	int requestedId = shmget(IPC_PRIVATE, sizeof(struct job)*rows*cols, 0770);
	requestedJob = (struct job *) shmat( requestedId, NULL, SHM_RND);
	initializeRequestedJob();

	//holds front and back indexes for the buffer
	int indexShmid = shmget(IPC_PRIVATE, sizeof(int)*2, 0770);
	int * indexPtr = (int *) shmat(indexShmid, NULL, SHM_RND);
	frontIndex = 0;

	//rows*cols is the max amount of jobs in RAM at once since each job requires 1 char minimum
        int jobsInRAMId = shmget(IPC_PRIVATE, sizeof(struct job)*rows*cols, 0770);
        jobsInRAM = (struct job *) shmat(jobsInRAMId, NULL, SHM_RND);
	initializeJobsInRAM();

	int stopMarkerId = shmget(IPC_PRIVATE, sizeof(int), 0770);
	int * stopMarkerPtr = (int *) shmat(stopMarkerId, NULL, SHM_RND);
	stopMarker = GO;	
	
	int numInRAMId = shmget(IPC_PRIVATE, sizeof(int)*2, 0770);
	numInRAMPtr = (int *) shmat(numInRAMId, NULL, SHM_RND);

	sem_id = semget(IPC_PRIVATE, 4, 0777);
	if( sem_id == -1 ){
		backIndex = 0; printf("Cannot get sem_id\n");
		return 1;
	}

	semctl(sem_id, MUTEX, SETVAL, 1);
	semctl(sem_id, EMPTY, SETVAL, bufferSize);
	semctl(sem_id, FULL, SETVAL, 0);
	semctl(sem_id, REQUEST, SETVAL, 0);

	FILE * out = fopen("ids", "w");
	if( out == NULL ){
		printf("error getting file to write\n");
		exit(1);
	}
	fprintf(out, "%d\n%d\n%d\n%d\n%d\n", rows, cols, sem_id, requestedId, stopMarkerId );
	fclose( out );

	int x, pid = -1;
	int originalPid = getpid();
	
	curNumInRAM = 0;
	totalNumInRAM = 0;

	if( fork() == 0 ){//create timer process as child
		pid = getpid();
		while(1){
			if( stopMarker == STOP )
				break;
			sleep(1);
			timer++;
		}
	}else if( fork() ==  0 ){//consumer for the buffer
		pid = getpid();
		while(1){
			if ( stopMarker == STOP )
                                break;
			p(FULL, sem_id);
			if ( stopMarker == STOP )
				break;
			bool vEmpty = false;
			p(MUTEX, sem_id);
			if ( stopMarker == STOP )
                                break;
                                struct job temp = rJob;
				rJob = frontPtr;
				if( fit() ){
					frontPtr.ID = '\0';
					rJob.timeIn = timer;
					placeInRAM();
					curNumInRAM++;
					totalNumInRAM++;
					vEmpty = true;		
				}else
					v(FULL, sem_id);
				frontIndex = frontIndex >= bufferSize - 1 ? 0 : frontIndex + 1;
				rJob = temp;	
			v(MUTEX, sem_id);
			if ( vEmpty )//if a job is not placed into memory then we do not v the empty semaphore
				v(EMPTY, sem_id);
		}
	}else if( fork() == 0 ){//removeFromRAM and print
		pid = getpid();
		while(1){
			sleep(1);
			if( stopMarker == STOP )
				break;
			p(MUTEX, sem_id);
				removeFromRAM();
				printRAM();
				printJobs();
			v(MUTEX, sem_id);
		}
	}else if( fork() != 0 ){//processing requests from prods
				//either puts into RAM or the buffer
		pid = getpid();
		while(1){
			sleep(1);
			if( stopMarker == STOP )
				break;
			p( REQUEST, sem_id );
			if( stopMarker == STOP )
                                break;
			if ( fit() ){
				p( MUTEX, sem_id );
					rJob.timeIn = timer;
					placeInRAM();
					curNumInRAM++;
					totalNumInRAM++;
				v( MUTEX, sem_id );
			}else{
				if( fork() == 0 ){//necessary since the p on EMPTY may block the process
					if ( stopMarker == STOP )
						break;
					p( EMPTY, sem_id );
					p( MUTEX, sem_id );
						backPtr = rJob;
						rJob.ID = '\0';
						backIndex = backIndex >= bufferSize - 1 ? 0 : backIndex + 1;
					v( MUTEX, sem_id );
					v( FULL, sem_id );
				}
			}
		}		
	}

	if ( pid != originalPid )
		return 0;

	if ((semctl(sem_id, 0, IPC_RMID, 0)) == -1)
		printf("%s", "Parent: ERROR in removing sem\n");

	if ((shmctl(bufferId, IPC_RMID, NULL)) == -1)
		printf("ERROR removing buffer shmem.\n");

	if ((shmctl(indexShmid, IPC_RMID, NULL)) == -1)
		printf("ERROR removing index shmem.\n");
	
	if ((shmctl(requestedId, IPC_RMID, NULL)) == -1)
		printf("ERROR removing index shmem.\n");

	if ((shmctl(ramId, IPC_RMID, NULL)) == -1)
                printf("ERROR removing RAM shmem.\n");

	if ((shmctl(jobsInRAMId, IPC_RMID, NULL)) == -1)
                printf("ERROR removing jobInRAM shmem.\n");

	if ((shmctl(stopMarkerId, IPC_RMID, NULL)) == -1)
                printf("ERROR removing stopMarker shmem.\n");

	if ((shmctl(timerId, IPC_RMID, NULL)) == -1)
		printf("ERROR removing timer shmem.\n");

	system("rm ids");
	return 0;

}

void removeFromRAM(){
        int x = 0;
        for( x = 0; x < rows*cols; x++ ){
                if( jobsInRAM[x].ID == '\0' )
                        continue;
                if( jobsInRAM[x].sec + jobsInRAM[x].timeIn <= timer ){
                        jobsInRAM[x].ID = '\0';
                        int y, addr = jobsInRAM[x].addr;
			int size = jobsInRAM[x].size;
                        for( y = addr; y < addr + size; y++ )
                                RAM[y] = '.';
			curNumInRAM--;
                        v( 0, jobsInRAM[x].semId );//allow the producer to finish
                }
        }
}

void initializeJobsInRAM(){
	struct job dummy;
	dummy.canOverwrite = true;
	dummy.ID = '\0';
	int x = 0;
	for( x = 0; x < rows*cols; x++ )
		jobsInRAM[x] = dummy;
}

void placeInRAM(){
	int x = 0;
	for( x = 0; x < rows*cols; x++ )
		if( jobsInRAM[x].canOverwrite ){
			rJob.ID = 'A' + totalNumInRAM;
			rJob.canOverwrite = false;
			jobsInRAM[x] = rJob;
			int size = rJob.size;
			int addr = rJob.addr;
			for( x = addr; x < addr+size; x++ )
				RAM[x] = rJob.ID;
			return;
		}	
}

bool fit(){
	int x = 0, curCount = 0, curPlace = 0;	
	for( x = 0; x < rows*cols; x++ ){
		if ( RAM[x] == '.' ){
			curCount++;
			if ( curCount == rJob.size ){
				rJob.addr = curPlace;
				return true;
			}
		}else{
			curCount = 0;
			curPlace = x + 1;
		}
	}
	return false;
}

void initializeRequestedJob(){
	rJob.pid = -999;
        rJob.size = -1;
        rJob.sec = -1;
        rJob.addr = -1;
        rJob.timeIn = -1;
        rJob.canOverwrite = true;
        rJob.ID = '\0';
	rJob.semId = -1;
}

void printJobs(){
	int x;
	if( curNumInRAM >= 1 )
                printf("ID thePID Size Sec\n");		
	for( x = 0; x < rows*cols; x++ ){
		if( jobsInRAM[x].ID == '\0' )
			continue;
		printf("%c. %-6d %-4d %-3d\n", jobsInRAM[x].ID, jobsInRAM[x].pid, jobsInRAM[x].size, jobsInRAM[x].sec);
	}
	printf("\n");
}

void checkForConsumer(){
	FILE *checker = fopen("ids", "r");
	if( checker != NULL ){
		printf("An instance of consumer is already running and has create the ids file.\nStop it before running a new consumer process.\n");
		exit(1);
	}
}


void initializeRAM(){
	int sizeOfRAM = rows*cols;
	int x;
	for( x = 0; x < sizeOfRAM; x++ )
		RAM[x] = '.';
}

void printRAM(){
	//+2 for the asterisks in surrounding columns, -6 for "Memory"
	int gap = (cols + 2 - 6) >> 1;
	gap = gap < 1 ? 1 : gap;
	char header[100];
	sprintf(header, "\nTroy's%*s%*s\n", gap+6, "Memory", gap+7, "Manager");
	printf("%s", header);
	
	int x, y, z;
	for( x = 0; x < strlen(header) - 1; x++ )
		printf("-");
	printf("\n");

	for( x = 0; x < 6; x++ )
		printf(" ");

	for( x = 0; x < cols + 2; x++ )
		printf("*");
	printf("\n");
	

	for( x = 0; x < rows; x++ ){
		for( z = 0; z < 6; z++ )
                	printf(" ");
		printf("*");
		for( y = x*cols; y < x*cols + cols; y++ )
			printf("%c", RAM[y]);
		printf("*\n");
	}

	for( x = 0; x < 6; x++ )
                printf(" ");

        for( x = 0; x < cols + 2; x++ )
                printf("*");
        printf("\n");

	return;
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
