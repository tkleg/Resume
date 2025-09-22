//Troy Kleger
// CSC 460
// March 12, 2025
// System Print Daemon - Stop

#include <sys/shm.h>
#include <stdio.h>
#include <sys/sem.h>

#define FULL 2

#define STOP 1

#define stopMarker stopMarkerPtr[0]

int main(){
	FILE * in = fopen( "idFile", "r" );
	if( in == NULL ){
		printf( "Stop cannot run as there is no Daemon running.\n");
		return 1;
	}
	int stopMarkerId, sem_id, i;
	fscanf(in, "%d%d%d%d%d", &sem_id, &i, &i, &i, &stopMarkerId );
	fclose( in );
	
	int * stopMarkerPtr = (int *) shmat(stopMarkerId, NULL, SHM_RND );
	stopMarker = STOP;

	v( FULL, sem_id );	
}

v(int s, int sem_id){

struct sembuf sops;

sops.sem_num = s;
sops.sem_op = 1;
sops.sem_flg = 0;

if((semop(sem_id, &sops, 1)) == -1)
	printf("%s","'V' error\n");

}
