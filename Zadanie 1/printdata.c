#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h>
#include "printdata.h"

void printdata(int i)
{
	printf("UID: %i | GID: %i | PID: %i | PPID: %i | PGID: %i | Utworzony przy i= %d\n", getuid(), getgid(), getpid(), getppid(), getpgrp(),i);
}