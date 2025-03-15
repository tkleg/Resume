//Troy Kleger
// CSC 460
// February 26, 2025
// Fastest Synchronization

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
int     i, sem_id, HowManySems = 2;
int     loopCount = 100;
int n = atoi(argv[1]), a;
if( n < 1 || n > 26 ){
	printf("User input number was %d.\nYou must enter a number no less than 1 and no greater than 26\n.", n );
	return 0;
}
//  Ask OS for semaphores.
sem_id = semget (IPC_PRIVATE, n, 0777);

//  See if you got the request.
if (sem_id == -1)
   {
    printf("%s","SemGet Failed.\n");
    return (-1);
   }

//  Initialize your sems.
semctl(sem_id, 0, SETVAL, 1);
for( i = 1; i < n; i++ )
	semctl(sem_id, i, SETVAL, 0);

char ch = 'A';
int semIndex = 0, originalPid = getpid();
for( i = 1; i < n; i++ ){
	a = fork();
	if( a == 0 ){
		ch++;
		semIndex++;
	}
	else break;
}
int myPid = getpid();
for( i = 0; i < n; i++ ){
	p( semIndex, sem_id );
	printf("%c:%d\n", ch, myPid );
	if( semIndex + 1 == n )
		v( 0, sem_id );
	else
		v( semIndex+1, sem_id );
}


if( myPid == originalPid ){
	usleep(100000);
	if ((semctl(sem_id, 0, IPC_RMID, 0)) == -1)
		printf("%s", "Parent: ERROR in removing sem\n");
}

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


