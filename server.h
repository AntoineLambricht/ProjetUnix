/*
	File name: 	server.h
	Author: 	BERGE Benjamin, LAMBRICHT Antoine
	Serie:		1
*/
#include "util.h"
#include "socket.h"

#include 	<signal.h>
#include 	<sys/time.h>

#if ! defined (_SERVER_H_)
#define _SERVER_H_

typedef struct player {
	int socket;
	char name[NAME_SIZE];
	int point;
} player;

int receive_msg(char* msg, int fd);

void process(player* p, char* msg, player players[],int playerCount);

void removePlayer(player players[],int* playerCount,int index);

#endif
