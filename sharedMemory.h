/*
	File name: 	sharedMemory.h
	Author: 	BERGE Benjamin, LAMBRICHT Antoine
	Serie:		1
*/

#if ! defined(_SHARED_MEMORY_H_)
#define _SHARED_MEMORY_H_

#define KEY 2105

#include "util.h"
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>



typedef struct memStruct {
  unsigned char nbPlayers;
  player players[MAX_PLAYERS];
  Card plis[MAX_PLAYERS];
}memStruct;

memStruct *attach(int shmid);

int initSharedMemory(int is_server);

#endif
