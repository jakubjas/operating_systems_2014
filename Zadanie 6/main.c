#define _XOPEN_SOURCE
#include <stdio.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h> 
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "semaphorefunc.h"

int main(void)
{
	key_t key; 
	int semid, i; 
	
	srand(time(NULL));

 	key = ftok(".", 'A'); /* tworzę unikalny klucz */
	
	if (key == -1)
   	{
   		perror("ftok() error");
      	exit(1);
   	}

  	semid = CreateSem(key, 1); /* tworzę jeden semafor */
  	
  	if (semid == -1)
   	{
      perror("CreateSem() error");
      exit(1);
    }
    
    InitSem(semid, 0, 1); /* inicjalizuję semafor wartością 1 */

  	printf("Utworzono semafor o identyfikatorze: %d i wartości %d\n", semid, GetSemVal(semid,0));
	
	for(i=0;i<3;++i) 
	{	
		switch (fork())
		{
   			case -1:
   				perror("fork error");
      			exit(1);
			break;
   			case 0:
      			execl("./1.exe", "1.exe", NULL); 	
			break;
			default:  			
			break;
		};
	}
	
	printf("Proces rodzica (%d) oczekuje na wejscie do sekcji krytycznej\n",getpid());

	P(semid,0); /* opuszczam semafor */

	printf("Proces rodzica (%d) wykonuje sekcje krytyczna\n",getpid());
	sleep(rand() % 3);
			
	V(semid,0); /* podnoszę semafor */
         	
    printf("Proces rodzica (%d) opuscil sekcje krytyczna\n",getpid());	
    
    for(i=0;i<3;++i)
    {
    	wait(NULL);
    }
    
	RemoveSem(semid);
	
	return 0;
}