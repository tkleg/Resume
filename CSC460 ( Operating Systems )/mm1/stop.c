// Troy Kleger
// CSC 460
// April 30, 2025
// Memory Manager - Stop

#include "includes.h"

int main(){

	int sem_id, stopMarkerId, dump;
	FILE * idFile = fopen("ids", "r");
	if( idFile == NULL ){
		printf("id file not found by stop program.\n");
		return 1;
	}
	fscanf(idFile, "%d%d%d%d%d", &dump, &dump, &sem_id, &dump, &stopMarkerId);
	fclose(idFile);


	int * stopMarkerPtr = (int *) shmat(stopMarkerId, NULL, SHM_RND);
	stopMarker = STOP;
	v( FULL, sem_id );
	FILE * prodSems = fopen("prodSemIds", "r");
	if ( prodSems == NULL ){
		printf("producer sem_ids file not found by stop program.\n");
		return 1;
	}
	fclose( prodSems );
	
	int prodSemId;
	while( fscanf(prodSems, "%d", prodSemId) == 1 )
		v( 0, prodSemId );

	system("rm prodSemIds");

	return 0;
}


v(int s, int sem_id){

	struct sembuf sops;
	sops.sem_num = s;
	sops.sem_op = 1;
	sops.sem_flg = 0;

	if((semop(sem_id, &sops, 1)) == -1)
		printf("%s","'V' error\n");

}
