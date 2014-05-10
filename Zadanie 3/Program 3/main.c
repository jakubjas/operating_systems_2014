#define _POSIX_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(void)
{
	int i;
	
	for(i=0;i<5;++i)
	{	
		switch (fork())
		{
   			case -1:
   				perror("fork error");
    	  		exit(1);
			break;
   			case 0:
      			execl("./1.exe", "1.exe", "1", "15", NULL); /* uruchamiam program 1.exe przy użyciu funkcji execl, wybierając obsługę domyślną sygnału SIGTERM (15) */
			break;
		};
		
		sleep(1);
	}

	signal(15,SIG_IGN); /* zabezpieczam proces główny przed zabiciem sygnałem kill */
	kill(-getpgrp(),SIGTERM); /* wykonuję SIGTERM dla grupy procesów powstałych w pętli, wykorzystując funkcję getpgrp zabezpieczam się przed problemem w przypadku getpgid, które może zwrócić -1 */
	/* getpgrp zawsze zwraca identyfikator grupy procesów, nie ma zadeklarowanej wartości zwracanej w przypadku błędu, co rozwiązuje problem obecny przy użyciu getpgid */

	printf("SIGTERM wyslany do 5 uruchomionych procesow. \nKoncze prace procesu macierzystego...\n");
	
	return 0;
}
