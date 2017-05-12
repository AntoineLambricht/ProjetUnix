/*
	File name: 	sharedMemory.c
	Author: 	BERGE Benjamin, LAMBRICHT Antoine
	Serie:		1
*/
#include "sharedMemory.h"

int initSharedMemory(int is_server){
  key_t key;
  int shmid,shmflg;
  shmflg = (is_server) ? IPC_CREAT|0644 : 0644;
  key = KEY;
  SYS(shmid = shmget(key,sizeof(memStruct),shmflg));

  return shmid;
}

memStruct *attach(int shmid){
  key_t key;

  memStruct* data;

  key = KEY;
  SYS(shmid = shmget(key,sizeof(memStruct),IPC_EXCL | 0644));

  if ((data = shmat(shmid,NULL,0)) == (memStruct * ) -1) {
  		perror("Pas de mémoire partagée\n");
  		exit(1);
  }

  return data;
}
