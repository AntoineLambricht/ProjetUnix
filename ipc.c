/*
	File name: 	ipc.c
	Author: 	BERGE Benjamin, LAMBRICHT Antoine
	Serie:		1
*/
#include "ipc.h"
int semaphore_descriptor = -1;
int rc=0;
int rc_shmid=-1;

void deleteSharedMemory(int shmid){
	SYS(shmctl(shmid,IPC_RMID,0));
	SYS(semctl(semaphore_descriptor, IPC_RMID, 0));
	SYS(shmctl(rc_shmid,IPC_RMID,0));
}

/*create or connect to the shared memory*/
int initSharedMemory(int is_server){
  key_t key;
  int shmid,shmflg;
  shmflg = (is_server) ? IPC_CREAT|IPC_EXCL|0644 : 0644;
  key = KEY;
  SYS(shmid = shmget(key,sizeof(memStruct),shmflg));
  return shmid;
}

/*writes players in shared memory*/
void ecrirePlayers(player newPlayers[MAX_PLAYERS],int newNbPlayers){
	semaphore_down(BD);
	int shmid,i;
	key_t key;
	memStruct* data;

	key = KEY;
	SYS(shmid = shmget(key,sizeof(memStruct),IPC_EXCL | 0644));

	if ((data = shmat(shmid,NULL,0)) == (memStruct * ) -1) {
  		perror("Pas de mémoire partagée\n");
  		exit(1);
	}
	
	for(i = 0;i<MAX_PLAYERS;i++){
		stpcpy(data->players[i].name,newPlayers[i].name);
		data->players[i].points = newPlayers[i].points;
		data->players[i].socket = newPlayers[i].socket;
	}
	data->nbPlayers = newNbPlayers;
	semaphore_up(BD);
}

/*writes the plis in shared memory*/
void ecrirePlis(Card newPlis[MAX_PLAYERS]){
	
	int shmid,i;
	key_t key;
	memStruct* data;

	semaphore_down(BD);
	key = KEY;
	SYS(shmid = shmget(key,sizeof(memStruct),IPC_EXCL | 0644));

	if ((data = shmat(shmid,NULL,0)) == (memStruct * ) -1) {
  		perror("Pas de mémoire partagée\n");
  		exit(1);
	}
	
	for(i = 0;i<MAX_PLAYERS;i++){
		data->plis[i].num = newPlis[i].num;
		data->plis[i].couleur = newPlis[i].couleur;
	}
	semaphore_up(BD);
	
}


/*read points in shared memory*/
player* lirePoints(){
	int shmid;
	key_t key;
	memStruct* data;
	readDown();
	key = KEY;
	SYS(shmid = shmget(key,sizeof(memStruct),IPC_EXCL | 0644));

	if ((data = shmat(shmid,NULL,0)) == (memStruct * ) -1) {
  		perror("Pas de mémoire partagée\n");
  		exit(1);
	}
	
	/*for(i = 0;i<data->nbPlayers;i++){
		printf("%s a %d points\n",data->players[i].name,data->players[i].points);
	}*/
	readUp();
        return data->players;
}

/*read plis in shared memory*/
Pli lirePlis(){
	
	int shmid;
	key_t key;
	memStruct* data;
	readDown();
	key = KEY;
	SYS(shmid = shmget(key,sizeof(memStruct),IPC_EXCL | 0644));

	if ((data = shmat(shmid,NULL,0)) == (memStruct * ) -1) {
  		perror("Pas de mémoire partagée\n");
  		exit(1);
	}
	
	readUp();
	Pli pli;
	pli.nbr = data->nbPlayers;
	memcpy(pli.pli,data->plis,sizeof(Card)*MAX_PLAYERS);
    return pli;
}

/* algorithme du banquier pour la lecture*/
void readDown(){
	semaphore_down(MUTEX);
	ecrireRc(lireRc()+1);
	if(lireRc()==1)semaphore_down(BD);
	semaphore_up(MUTEX);
}

/* algorithme du banquier pour la lecture*/
void readUp(){
	semaphore_down(MUTEX);
	ecrireRc(lireRc()-1);
	if(lireRc()==0)semaphore_up(BD);
	semaphore_up(MUTEX);
}


/*________SEMAPHORES_____*/

/* Initialise la sémaphore */
void init_semaphore(int is_server) {
    rc_shmid = initRcMemory(is_server);
    key_t semaphore_key = KEY_SEM;
    int semaphore_flag = (is_server) ? IPC_CREAT|0666 : 0666;
    if((semaphore_descriptor = semget(semaphore_key, 2, semaphore_flag)) == -1) {
        /* TODO Error management */
        fprintf(stderr,"Semget fail\n");
        exit(EXIT_FAILURE);
    }

    if( (semctl(semaphore_descriptor, MUTEX, SETVAL, 1)) == -1
        || (semctl(semaphore_descriptor, BD, SETVAL, 1)) == -1 ) {
        /* TODO Error management */
        fprintf(stderr,"Semctl fail\n");
		exit(EXIT_FAILURE);
    }
}


/* Sortie de zone protégée */
int semaphore_up(int semaphore) {
    struct sembuf operations_buffer[1], semaphore_operation;
    if( semaphore_descriptor == -1 ) {
        /* TODO Error management */
        fprintf(stderr,"Sem_desc not init\n");
        return -1;
    }
    
    semaphore_operation.sem_num = semaphore;
    semaphore_operation.sem_op = 1;
    semaphore_operation.sem_flg = 0;
    operations_buffer[0] = semaphore_operation;

    if( semop(semaphore_descriptor, operations_buffer, SINGLE_OPERATION) == -1 ) {
        /* TODO Error management */
        fprintf(stderr,"Semop down ko\n");
        return -1;
    }
    return 0;
}

/* Entrée dans zone protégée*/
int semaphore_down(int semaphore) {
    struct sembuf operations_buffer[1], semaphore_operation;
    
    if( semaphore_descriptor == -1 ) {
        /* TODO Error management */
        fprintf(stderr,"Sem_desc not init\n");
        exit(EXIT_FAILURE);
    }
    semaphore_operation.sem_num = semaphore;
    semaphore_operation.sem_op = -1;
    semaphore_operation.sem_flg = 0;
    operations_buffer[0] = semaphore_operation;

    if( semop(semaphore_descriptor, operations_buffer, SINGLE_OPERATION) == -1 ) {
        /* TODO Error management */
        fprintf(stderr,"Semop up ko\n");
        return -1;
    }
    return 0;
}


/*________GESTION D'UNE ZONE MEMOIRE PARTAGEE PROPRE A RC_____*/

/*Création ou connection à une zone de mémoire partagée où on stocke le nombre de processus en lecture*/
int initRcMemory(int is_server){
  key_t key;
  int shmid,shmflg;
  shmflg = (is_server) ? IPC_CREAT|0644 : 0644;
  key = KEY_SPACE_SEM;
  SYS(shmid = shmget(key,sizeof(int),shmflg));
  
  return shmid;
}

/* lecture de rc*/
int lireRc(){
	int shmid;
	key_t key;
	int* rc;
        
	key = KEY_SPACE_SEM;
	SYS(shmid = shmget(key,sizeof(int),IPC_EXCL | 0644));

	if ((rc = shmat(shmid,NULL,0)) == (int * ) -1) {
  		perror("Pas de mémoire partagée pour rc\n");
  		exit(1);
	}	
	return *rc;	
}

/*écriture de rc*/
void ecrireRc(int rc){
	int shmid;
	key_t key;
        int* old_rc;

	key = KEY_SPACE_SEM;
	SYS(shmid = shmget(key,sizeof(int),IPC_EXCL | 0644));

	if ((old_rc = shmat(shmid,NULL,0)) == (int * ) -1) {
  		perror("Pas de mémoire partagée pour rc\n");
  		exit(1);
	}
	*old_rc=rc;
}







