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
	
	if ((mkfifo(fifo, 0666)) == -1) /* tworzę potok nazwany */
	{	
		perror("mkfifo() error");
		exit(1);
	}
	
	descriptor = open("in.txt", O_RDONLY, 0644); /* tworzę deskryptor dla pliku wejściowego in.txt */
	
	if (descriptor == -1)
   	{
   		perror("open() error");
      	exit(2);
   	}
   	
	finfout = open(fifo, O_WRONLY); /* tworzę deskryptor dla potoku nazwanego */
	
	if (finfout == -1)
   	{
   		perror("open() error");
      	exit(3);
   	}
   			
	while ((data_size = read(descriptor, pipe_buff, BUFF))) /* dopóki istnieją dane do odczytania, wykonuj instrukcje... */
	{
		if (write(finfout, pipe_buff, data_size) == -1) /* zapisujemy porcję danych z pliku do bufora potoku */
   		{
   			perror("write() error");
      		exit(4);
   		}
				
		if (data_size < BUFF)
   			pipe_buff[data_size] = '\0'; /* aby uniknąć wypisywania poprzez printf poniżej resztek danych z bufora, 
   			gdy w ostatnim przejściu pętli porcja danych jest mniejsza niż ta w nim zapisana, dodajemy w takiej sytuacji 
   			znak \0 określający koniec sekwencji */
   					
   		printf("{Producent} pobrał ciąg tekstowy: '%s'\n", pipe_buff);
   				
   		sleep(rand() % 2); /* usypiam proces, symulując różny czas zapisu/odczytu programu */
	}	
			
	close(descriptor); /* zwalniam używany przez plik in.txt deskryptor */
	unlink(fifo); /* usuwam potok nazwany, stanie się to dopiero, gdy przestanie go używać konsument */
	
	printf("{Producent}: Zakończyłem pracę!\n");
	
	return 0;
}
