/*
	File name: 	ipc.h
	Author: 	BERGE Benjamin, LAMBRICHT Antoine
	Serie:		1
*/

#if ! defined(_IPC_H_)
#define _IPC_H_

#define KEY 2105
#define KEY_SEM 1066
#define KEY_SPACE_SEM 1082

#define MUTEX 0
#define BD 1
#define SINGLE_OPERATION 1

#include "util.h"
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>



typedef struct memStruct {
  unsigned char nbPlayers;
  player players[MAX_PLAYERS];
  Card plis[MAX_PLAYERS];
}memStruct;

typedef int semaphore;

void deleteSharedMemory(int shmid);
int initSharedMemory(int is_server);

void ecrirePlayers(player newPlayers[MAX_PLAYERS],int newNbPlayers);
void ecrirePlis(Card newPlis[MAX_PLAYERS]);
void lirePoints();
Pli lirePlis();

void init_semaphore(int is_server);
int semaphore_up(int semaphore);
int semaphore_down(int semaphore);
int initRcMemory(int is_server);
void ecrireRc(int rc);
int lireRc();
void readDown();
void readUp();

#endif
