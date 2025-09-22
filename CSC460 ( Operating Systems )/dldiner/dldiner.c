//Troy Kleger
// CSC 460
// March 20, 2025
// DL Diner

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

void loop( int procIndex, int sem_id );

void randWait( unsigned int seed, float divisor );

int main(int argc, char* argv[])
{
int	i, sem_id;
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

int x;
for( x = 0; x < 4; x++ ){
	if( fork() )
		break;
}

loop( x, sem_id );

return 0;
}

void loop( int procIndex, int sem_id ){
	int x, i = 0;
	int rightIndex = (procIndex+1)%5;
	int leftIndex = procIndex;
	unsigned int seed = 0;
	float eatingFactor = 5;
	float thinkingFactor = 3;
	float betweenPickupFactor, betweenPutdownFactor = 1.2;
	srand( getpid() );
	
	while(1){

		for( i = 0; i < procIndex; i++ ) printf("\t");
                printf("%d %s\n", procIndex, "THINKING");
		randWait(seed, thinkingFactor);

		for( i = 0; i < procIndex; i++ ) printf("\t");
		printf("%d %s\n", procIndex, "HUNGRY");
                p( leftIndex, sem_id );
		randWait(seed, betweenPickupFactor);
                p( rightIndex, sem_id );

		for( i = 0; i < procIndex; i++ ) printf("\t");
		printf("%d %s\n", procIndex, "EATING");
		randWait(seed, eatingFactor);
		v( leftIndex, sem_id );
		randWait(seed, betweenPutdownFactor );
		v( rightIndex, sem_id );
		
	}
}

void randWait( unsigned int seed, float factor ){
	int x, r = (rand() % 500000) * factor;
	for( x = 0; x < r; x++ );
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

