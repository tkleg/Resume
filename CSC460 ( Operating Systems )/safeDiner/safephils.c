//Troy Kleger
// CSC 460
// March 28, 2025
// Safe Diner

#include <stdbool.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <time.h>


#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define DEAD 3

#define CLOCK shmem[5]
#define myStatus shmem[procIndex]

#define initialProcIndex -1

void loop( int procIndex, int sem_id, int* shmem, int endTime );

bool someAlive( int* shmem );

void randSleep( int min, int max );

int main(int argc, char* argv[])
{
int	i, sem_id;

int shmid = shmget(IPC_PRIVATE, sizeof(int)*6, 0770); 
int *shmem = (int *) shmat(shmid, NULL, 0);
for( i = 0; i <= 4; i++ )
	shmem[i] = THINKING;

//  Ask OS for semaphores.
sem_id = semget (IPC_PRIVATE, 5, 0777);

//  See if you got the request.
if (sem_id == -1)
   {
    printf("%s","SemGet Failed.\n");
    return (-1);
   }

//  Initialize your sems.
for( i = 0; i < 5; i++ )
	semctl(sem_id, i, SETVAL, 1);

int procIndex;
for( procIndex = 0; procIndex < 5; procIndex++ ){
	if( fork() )
		break;
}
procIndex--;

int startTime = time(NULL);
if( procIndex != initialProcIndex )
	loop( procIndex, sem_id, shmem, startTime+60 );
else{
	char* stateStrings[] = {"thinking", "hungry", "eating", "dead"};
	while( someAlive( shmem ) ){
		CLOCK = time(NULL);
		printf("%2d. ", CLOCK-startTime+1 );
		for( i = 0; i < 5; i++ )
			printf("%-10s", stateStrings[ shmem[i] ]); 
		printf("\n");
		sleep(1);
	}
	//code below lets the processes all print with dead state
	 printf("%2d. ", CLOCK-startTime+1 );
         for( i = 0; i < 5; i++ )
         	printf("%-10s", stateStrings[ shmem[i] ]);
         printf("\n");

	if ((shmctl(shmid, IPC_RMID, NULL)) == -1)
		printf("ERROR removing shmem.\n");
	if ((semctl(sem_id, 0, IPC_RMID, 0)) == -1)
		printf("%s", "Parent: ERROR in removing sem\n");

}

return 0;

}

bool someAlive( int* shmem ){
	int x;
	for( x = 0; x < 5; x++ )
		if( shmem[x] != DEAD )
			return true;
	return false;	
}

void loop( int procIndex, int sem_id, int* shmem, int endTime ){
	int rightIndex = (procIndex+1)%5;
	int leftIndex = procIndex;
	srand( getpid() );
	while( CLOCK < endTime ){
		myStatus = THINKING;
		randSleep( 1, 5 );
		myStatus = HUNGRY;
                p( leftIndex, sem_id );
		p( rightIndex, sem_id );
		myStatus = EATING;
		randSleep( 1, 3 );
		v( leftIndex, sem_id );
		v( rightIndex, sem_id );
	}
	myStatus = DEAD;
}

void randSleep( int min, int max ){
	sleep( (rand() % (max-min+1)) + min );
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

