#define _REENTRANT 
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define K 5 /* ilość wątków */
#define N 10 /* ilość powtórzeń operacji na sekcji krytycznej */

int licznik = 0; /* incjalizuję zmienną globalną "licznik" wartością 0 */
pthread_t tid[K]; /* tablica zawierająca identyfikatory wątków */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* inicjalizuję muteks */

void *GlobalWork(void *arg) /* funkcja wykonywana przez wątki */
{
	int i, j;
	
	for(i=0; i<N; i++) /* realizacja wzajemnego wykluczania */
	{
		printf("Wątek (%lu) oczekuje na wejscie do sekcji krytycznej\n", (unsigned long) pthread_self());

		pthread_mutex_lock(&mutex); /* zamykam mutex */

		printf("Wątek (%lu) wykonuje sekcje krytyczna\n", (unsigned long) pthread_self());
	
			j = licznik;
			++j;
			licznik = j;
			sleep(rand() % 2);
	
		pthread_mutex_unlock(&mutex); /* otwieram mutex */
         	
    	printf("Wątek (%lu) opuscil sekcje krytyczna\n", (unsigned long) pthread_self());	
	}
	
	return 0;
}

int main(void)
{
	int i;
	
	srand(time(NULL));
	
	for(i=0; i<K; i++)
	{
		pthread_create(&tid[i], NULL, GlobalWork, NULL); /* tworzę wątek */
	}
	
	for(i=0; i<K; i++)
	{
		pthread_join(tid[i], NULL); /* czekam na zakończenie wątków */
	}
	
	printf("Licznik = %d\n", licznik);
	
	return 0;
}
