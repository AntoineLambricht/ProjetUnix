/*
	File name: 	util.h
	Author: 	BERGE Benjamin, LAMBRICHT Antoine
	Serie:		1
*/

#if ! defined (_UTIL_H_)
#define _UTIL_H_

#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include	<unistd.h>


#define SYS(call) ((call) == -1) ? (perror(#call ": ERROR"),exit(1)) : 0

#define TRUE 1
#define FALSE 0

#define OK 0
#define KO 1

#define NB_CARDS 60
#define MAX_PLAYERS 4
#define MAX_CARD_BY_PLAYER 30
#define SIZE_ECART 5


#define NAME_SIZE 40
#define MESSAGE_SIZE 255

#define INSCRIPTION 0
#define NAME_TAKEN 1
#define INSCRIPTIONKO 2
#define DISTRIBUTION 3

#define PIQUE 1
#define TREFLE 2
#define CARREAU 3
#define COEUR 4
#define PAYOO 5

typedef struct card{
  unsigned char num;
  unsigned char couleur;
}Card;

typedef struct player {
	int socket;
	char name[NAME_SIZE];
	int points;
} player;

typedef struct dist{
    int nbr;
    Card cards[MAX_CARD_BY_PLAYER];
} Dist;

/*Union of what a payload can be*/
union Payload{
	/*distribution*/
        Dist dist;  
	
	/*ecart*/
	Card ecart[5];
	
	/*jouer une carte*/
	Card carte;
	
	/*Message*/
	char str[MESSAGE_SIZE];
	
	/*Name pour inscription*/

	char name[NAME_SIZE];
};

typedef struct message{
	int action;
	union Payload payload;
}Message;

void lire_remove_emplacements(Card * buffer,Card * source,int size,int nbr);



#endif
