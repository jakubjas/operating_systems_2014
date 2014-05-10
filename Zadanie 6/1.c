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
	int semid; 
	
	srand(time(NULL));
	
	key = ftok(".", 'A'); /* umieszczam wartość klucza powiązanego z utworzonym wcześniej w programie głównym semaforze w zmiennej key */
	
	if (key == -1)
   	{
   		perror("ftok() error");
      	exit(1);
   	}
   	
   	semid = OpenSem(key); /* otwieram semafor utworzony w programie głównym */
    
    if (semid == -1)
    {
      perror("OpenSem() error");
      exit(1);
    }

	printf("Proces potomny (%d) oczekuje na wejscie do sekcji krytycznej\n", getpid());

	P(semid,0); /* opuszczam semafor */

	printf("Proces potomny (%d) wykonuje sekcje krytyczna\n",getpid());
	sleep(rand() % 3);
			
	V(semid,0); /* podnoszę semafor */
         	
	printf("Proces potomny (%d) opuscil sekcje krytyczna\n",getpid());

	return 0;
}