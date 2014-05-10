#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "printdata.h"

void printdata(void)
{
	printf("UID: %i | GID: %i | PID: %i | PPID: %i | PGID: %i\n", getuid(), getgid(), getpid(), getppid(), getpgrp());
}