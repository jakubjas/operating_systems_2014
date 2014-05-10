#ifndef _SEMAPHOREFUNC_H
#define _SEMAPHOREFUNC_H

int CreateSem(key_t keyval, int numsems); /* funkcja służąca do tworzenia semafora */
int OpenSem(key_t keyval); /* funkcja służąca do otwierania semafora */
void InitSem(int sid, int semnum, int initval); /* funkcja służąca do inicjalizacji semafora */
void V(int sid, int semnum); /* podniesienie semafora */
void P(int sid, int semnum); /* opuszczenie semafora */
int GetSemVal(int sid, int member); /* funkcja zwracająca wartość semafora */
void RemoveSem(int sid); /* funkcja służąca do usuwania semafora */

#endif