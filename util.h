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
#include    <unistd.h>


#define SYS(call) ((call) == -1) ? (perror(#call ": ERROR"),exit(1)) : 0

#define TRUE 1
#define FALSE 0

#define OK 0
#define KO 1

#define MAX_TURN 1

#define CHIFFRE_PAYOO 7
#define POINTS_PAYOO 40
#define NB_CARDS 60
#define MAX_PLAYERS 4
#define MAX_CARD_BY_PLAYER 30
#define SIZE_ECART 5

#define NAME_SIZE 40
#define MESSAGE_SIZE 255

#define INSCRIPTION 0
#define PAPAYOO 1
#define INSCRIPTIONKO 2
#define DISTRIBUTION 3
#define DISTRIBUTION_ECART 4
#define DEMANDE_CARTE 5
#define ENVOI_PLI 6
#define DEMANDE_POINTS 7
#define ALERTE_FIN_PARTIE 8
#define ENVOI_ECART 9
#define REPONSE_CARTE 10
#define REPONSE_POINTS 11
#define PLI_UPDATE 12

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

typedef struct pli{
	unsigned char nbr;
	Card pli[MAX_PLAYERS];
} Pli;

/*Union of what a payload can be*/
union Payload{
	/*distribution*/
    Dist dist;  
	
	/*ecart*/
	Card ecart[SIZE_ECART];
	
	/*jouer une carte*/
	Card carte;
	
	/*Message*/
	char str[MESSAGE_SIZE];
	
	/*Name pour inscription*/

	char name[NAME_SIZE];
	
	/*Points*/
	unsigned char points;
	
	/*Envois plis*/
	Pli pli;
	
	/*couleur du papayoo*/
	unsigned char papayoo;
};

typedef struct message{
	int action;
	union Payload payload;
}Message;





#endif
