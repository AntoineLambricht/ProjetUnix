/*
	File name: 	sharedMemory.h
	Author: 	BERGE Benjamin, LAMBRICHT Antoine
	Serie:		1
*/

#if ! defined(_SHARED_MEMORY_H_)
#define _SHARED_MEMORY_H_

#include "util.h"
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>


typedef struct memStruct {
  unsigned char nbPLayers;
  player players[MAX_PLAYERS];
  card plis[MAX_PLAYERS];
}memStruct;

#endif
