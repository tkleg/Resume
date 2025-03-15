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

int main(int argc, char *argv[])
{

int i, shmid;
struct glistStruct *ptr;

int x;

//gets the pid of the shared memory
FILE *idIn = fopen("/pub/csc460/glist/GLISTID.txt", "r");
fscanf(idIn, "%d", &shmid);
fclose(idIn);

ptr = (struct glistStruct *) shmat(shmid, NULL, 0);
/*ptr++;
char newname[20] = "hello";
strcpy(ptr->name, newname);
ptr--;*/
printf("HERE IS OUR SHARED GROCERY LIST:\n\n");

for( x = 0; x < 24; x++ ){
	printf("%2d:%20s|%9d|%30s|\n", 
		ptr->id, ptr->name, ptr->favNum, ptr->favFood );
	ptr++;
}


return 0;
}

