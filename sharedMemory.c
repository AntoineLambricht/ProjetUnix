/*
	File name: 	sharedMemory.c
	Author: 	BERGE Benjamin, LAMBRICHT Antoine
	Serie:		1
*/


int initSharedMemory(){
  key_t key;
  int shmid;


  key = 2105;
  SYS(shmid = shmget(key,sizeof(memStruct),IPC_CREATE | 0644));

  return shmid;
}


int lire(){
  key_t key;
  int shmid;

  memStruct *data;

  key = 2105;
  SYS(shmid = shmget(key,sizeof(memStruct),IPC_EXCL | 0644));

  if ((data = shmat(shmid,NULL,0)) == (memStruct * ) -1) {
  		perror("Pas de mémoire partagée\n");
  		exit(1);
  	}
  
  return shmid;
}
