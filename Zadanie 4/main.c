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
	int descriptor, data_size, pipedes[2];
	char pipe_buff[BUFF]; /* tablica znakowa przechowująca porcje danych */
	srand(time(NULL));
	
	if ((pipe(pipedes)) == -1)
	{
		perror("pipe() error");
		exit(1);
	}

	switch (fork())
	{
   		case -1:
      		perror("fork() error");
      		exit(2);
		break;
   		case 0:
   			close(pipedes[1]); /* zamykam nieużywany koniec potoku */
   			descriptor = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); /* tworzę deskryptor dla pliku wyjściowego out.txt */
   			
   			if (descriptor == -1)
   			{
   				perror("open() error");
      			exit(5);
   			}

   			while ((data_size = read(pipedes[0], pipe_buff, BUFF))) /* dopóki istnieją dane do odczytania, wykonuj instrukcje... */
   			{
   				if (write(descriptor, pipe_buff, data_size) == -1) /* zapisujemy porcję danych z bufora potoku do pliku określonego deskryptorem */
   				{
   					perror("write() error");
      				exit(6);
   				}
   				
   				if (data_size < BUFF)
   					pipe_buff[data_size] = '\0'; /* aby uniknąć wypisywania poprzez printf poniżej resztek danych z bufora, 
   					gdy w ostatnim przejściu pętli porcja danych jest mniejsza niż ta w nim zapisana, dodajemy w takiej sytuacji 
   					znak \0 określający koniec sekwencji */
   					
   				printf("{Konsument} zapisał ciąg tekstowy: '%s'\n", pipe_buff);
   				sleep((rand() % 2) + 1); /* usypiam proces, symulując różny czas zapisu/odczytu programu */
   			}
   			
   			close(descriptor); /* zwalniam używany przez plik out.txt deskryptor */
   			close(pipedes[0]); /* zwalniam używany przez potok deskryptor */
   			
   			printf("{Konsument}: Zakończyłem pracę!\n");
		break;
		default:
			close(pipedes[0]); /* zamykam nieużywany koniec potoku */
			descriptor = open("in.txt", O_RDONLY, 0644); /* tworzę deskryptor dla pliku wejściowego in.txt */
	
			if (descriptor == -1)
   			{
   				perror("open() error");
      			exit(3);
   			}
   			
			while ((data_size = read(descriptor, pipe_buff, BUFF))) /* dopóki istnieją dane do odczytania, wykonuj instrukcje... */
			{
				if (write(pipedes[1], pipe_buff, data_size) == -1) /* zapisujemy porcję danych z pliku do bufora potoku */
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
			close(pipedes[1]); /* zwalniam używany przez potok deskryptor */
			
			printf("{Producent}: Zakończyłem pracę!\n");
	};
	
	wait(NULL); /* proces macierzysty czeka na zakończenie procesu potomnego */
	
	return 0;

}
