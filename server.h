/*
	File name: 	server.h
	Author: 	BERGE Benjamin, LAMBRICHT Antoine
	Serie:		1
*/

#include "socket.h"
#include "ipc.h"
#include "util.h"

#include 	<signal.h>
#include 	<sys/time.h>
#include 	<time.h>

#if ! defined (_SERVER_H_)
#define _SERVER_H_


void melanger(Card cartes[]);

void initCartes(Card cartes[]);

int receive_msg(Message *msg, int fd);

void process(player* p, Message *msg, player players[],int playerCount);

void removePlayer(player players[],int* playerCount,int index);

#endif
