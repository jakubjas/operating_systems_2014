#define _XOPEN_SOURCE
#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h> 
#include "semaphorefunc.h"

/* fragment konieczny dla kompilacji pod Linuxem, w przypadku Mac OS X trzeba go usunąć */
union semun {
    int              val;    
    struct semid_ds *buf;   
    unsigned short  *array;  
    struct seminfo  *__buf; 
};

int CreateSem(key_t keyval, int numsems)
{
	int sid;
	
	if (numsems <= 0)
	{
		perror("CreateSem error");
		exit(1);
	}
	
	if( (sid = semget(keyval, numsems, IPC_CREAT | IPC_EXCL | 0660)) == -1 )
	{
		perror("semget error");
		exit(1);
	}
	
	return(sid);
}

int OpenSem(key_t keyval)
{
	int sid;
	
	if( (sid = semget(keyval, 0, 0666)) == -1 )
	{
		perror("semget error");
		exit(1);
	}
	
	return(sid);
}

void InitSem(int sid, int semnum, int initval)
{
	union semun semopts;
	
	semopts.val = initval;
	semctl(sid, semnum, SETVAL, semopts);
}

void V(int sid, int semnum)
{
	struct sembuf semops;
	
	semops.sem_num = semnum;
	semops.sem_op = 1;
	semops.sem_flg = 0 | SEM_UNDO;
	
	if (semop(sid, &semops, 1) == -1)
	{
		perror("V error");
		exit(1);
	}
}

void P(int sid, int semnum)
{
	struct sembuf semops;
	
	semops.sem_num = semnum;
	semops.sem_op = -1;
	semops.sem_flg = 0 | SEM_UNDO;
	
	if (semop(sid, &semops, 1) == -1)
	{
		perror("P error");
		exit(1);
	}
}

int GetSemVal(int sid, int member)
{
        int semval;

        semval = semctl(sid, member, GETVAL, 0);
        return(semval);
}

void RemoveSem(int sid)
{
	semctl(sid, 0, IPC_RMID, 0);
	printf("Semafor usuniety\n");
}

