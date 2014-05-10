#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "printdata.h" /* dołączam plik nagłówkowy zawierający deklarację funkcji printdata */

int main(void)
{
    printdata(); /* wypisuje identyfikatory UID, GID, PID, PPID oraz PGID dla danego procesu */

	return 0;
}