#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFF 25 /* definiuję wielkość bufora potoku, w którym zapisywane są porcje danych */

int main(void)
{
	int descriptor, data_size, finfout;
	char pipe_buff[BUFF]; /* tablica znakowa przechowująca porcje danych */
	char * fifo = "/tmp/fifo";
	srand(time(NULL));
	
   	descriptor = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); /* tworzę deskryptor dla pliku wyjściowego out.txt */
   	
   	if (descriptor == -1)
   	{
   		perror("open() error");
      	exit(2);
   	}
   	
   	finfout = open(fifo, O_RDONLY); /* tworzę deskryptor dla potoku nazwanego */
   	
   	if (finfout == -1)
   	{
   		perror("open() error");
      	exit(3);
   	}

   	while ((data_size = read(finfout, pipe_buff, BUFF))) /* dopóki istnieją dane do odczytania, wykonuj instrukcje... */
   	{
   		if (write(descriptor, pipe_buff, data_size) == -1) /* zapisujemy porcję danych z bufora potoku do pliku określonego deskryptorem */
   		{
   			perror("write() error");
      		exit(4);
   		}
   				
   		if (data_size < BUFF)
   			pipe_buff[data_size] = '\0'; /* aby uniknąć wypisywania poprzez printf poniżej resztek danych z bufora, 
   			gdy w ostatnim przejściu pętli porcja danych jest mniejsza niż ta w nim zapisana, dodajemy w takiej sytuacji 
   			znak \0 określający koniec sekwencji */
   					
   		printf("{Konsument} zapisał ciąg tekstowy: '%s'\n", pipe_buff);
   		sleep((rand() % 2) + 1);
   	}
   			
   	close(descriptor); /* zwalniam używany przez plik out.txt deskryptor */
   	close(finfout); /* zwalniam używany przez potok deskryptor */
   	
   	printf("{Konsument}: Zakończyłem pracę!\n");

	return 0;

}
