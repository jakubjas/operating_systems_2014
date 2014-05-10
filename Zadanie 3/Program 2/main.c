#define _POSIX_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(void)
{
	int k;
	
	k=fork();
	
	switch (k)
	{
   		case -1:
   			perror("fork error");
      		exit(1);
		break;
   		case 0:
      		execl("./1.exe", "1.exe", "3", "15", NULL); /* uruchamiam program 1.exe przy użyciu funkcji execl, wybierając obsługę przechwytywania sygnału SIGTERM (15) */
		break;
		default:
			sleep(1);
			kill(k,SIGTERM); /* wysyłam sygnał SIGTERM do uruchomionego wcześniej programu 1.exe */
		break;
	};

	return 0;
}
