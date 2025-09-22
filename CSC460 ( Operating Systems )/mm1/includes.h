#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdbool.h> 
#include "common.h"


#define FULL 0
#define EMPTY 1

#define MUTEX 2
#define REQUEST 3

#define GO 0
#define STOP 1
#define stopMarker stopMarkerPtr[0]

#define FRONT 0
#define BACK 1

#define ZERO 0

#define frontIndex indexPtr[FRONT]
#define backIndex indexPtr[BACK]
#define frontPtr bufferPtr[frontIndex]
#define backPtr bufferPtr[backIndex]
#define curNumInRAM numInRAMPtr[0]
#define totalNumInRAM numInRAMPtr[1]
#define timer timerPtr[0]
#define rJob requestedJob[0]
