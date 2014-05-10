#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "capture.h" /* dołączam plik nagłówkowy zawierający deklarację funkcji capture */

int main(int argc, char *argv[])
{
	
	switch (atoi(argv[1])) /* obsługa sygnału */
		{
   			case 1:
   				printf("Wykonuje operacje domyslna\n");
   				signal(atoi(argv[2]),SIG_DFL);
   				pause();
			break;
   			case 2:
   				printf("Ignoruje sygnal\n");
   				signal(atoi(argv[2]),SIG_IGN);
   				pause();
			break;
			case 3:
				printf("Przechwytuje sygnal...\n");
				signal(atoi(argv[2]),capture);
				pause();
			break;
		};
		
	return 0;
}