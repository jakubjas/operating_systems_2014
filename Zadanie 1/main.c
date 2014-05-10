#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "printdata.h" /* dołączam plik nagłówkowy zawierający deklarację funkcji printdata */

int main(void)
{
	int i;

	for(i=0;i<3;++i)
	{		
		switch (fork())
		{
   			case -1:
      			perror("fork error");
      			exit(1);
			break;
   			case 0:
   				printdata(i); /* wypisuje identyfikatory UID, GID, PID, PPID oraz PGID dla danego procesu */
   				/* przekazane "i" odpowiada za wypisanie wartości i, dla której proces został utworzony */
			break;
			default:
			break;
		};
		
		sleep(1); /* proces czeka jedną sekundę */
	}

	return 0;

}
