#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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
      			execl("./1.exe", "1.exe", NULL); /* uruchamiam program 1.exe przy użyciu funkcji execl */
			break;
			default:
			break;
		};
		
		sleep(1); /* proces czeka jedną sekundę */
	}

	return 0;

}
