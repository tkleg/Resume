// Troy Kleger
// CSC 460
// February 17, 2025
// SharedGrocery List

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>

struct glistStruct
{
        int id;
        char name[20];
        int favNum;
        char favFood[30];
};

void trim( char* s ){
        int frontIndex = 0, backIndex = strlen(s)-1;
        while( s[frontIndex] == ' ' ){
                s++;
                frontIndex++;
        }
        while( s[backIndex] == ' ' ){
                s[backIndex] = '\0';
                backIndex--;
        }
}

int main(int argc, char *argv[])
{

int x, shmid;
struct glistStruct *ptr;

argv[1][20] = '\0';
trim( argv[1] );

FILE *idIn = fopen("/pub/csc460/glist/GLISTID.txt", "r");
fscanf(idIn, "%d", &shmid);
fclose(idIn);

ptr = (struct glistStruct *) shmat(shmid, NULL, 0);

for( x = 0; x < 24; x++ ){
	if( ptr->id == 17 ){
		strcpy( ptr->name, argv[1] );
		return 0;
	}
	ptr++;
}


return 0;
}
