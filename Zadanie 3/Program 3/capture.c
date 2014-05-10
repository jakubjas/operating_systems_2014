#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h>
#include "capture.h"

void capture(int arg)
{
	printf("Mam cie, niegrzeczny sygnale o numerze: %i!\n", arg);
}