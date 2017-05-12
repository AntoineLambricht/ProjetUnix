/*
	File name: 	util.h
	Author: 	BERGE Benjamin, LAMBRICHT Antoine
	Serie:		1
*/
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include	  <unistd.h>

#if ! defined (_UTIL_H_)
#define _UTIL_H_

#define SYS(call) ((call) == -1) ? (perror(#call ": ERROR"),exit(1)) : 0

#define TRUE 1
#define FALSE 0

#define OK 0
#define KO 1

#define MAX_PLAYERS 4

#define NAME_SIZE 40
#define MESSAGE_SIZE 255

#define INSCRIPTION 0
#define NAME_TAKEN 1
#define INSCRIPTIONKO 2

typedef struct card{
  unsigned char num;
  unsigned char couleur;
}Card;

typedef struct player {
	int socket;
	char name[NAME_SIZE];
	int point;
} player;

void send_message(int type, const char* payload, int socket);

#endif
