/*
	File name: 	server.h
	Author: 	BERGE Benjamin, LAMBRICHT Antoine
	Serie:		1
*/

#if ! defined (_SERVER_H_)
#define _SERVER_H_

#include "socket.h"
#include "ipc.h"
#include "util.h"
#include "color.h"

#include 	<signal.h>
#include 	<sys/time.h>
#include 	<time.h>

#define ALARM 10

/*game_state variables*/
#define START_ROUND 0
#define	WAIT_FOR_ECART 1
#define	RANDOM_PAPAYOO 2
#define TURN 3
#define END_ROUND 4
/*turn_state*/
#define INIT_TURN 0
#define	START_TURN 1
#define	END_TURN 2

/*player_turn_state*/
#define	SEND_DEMEND 0
#define WAIT_RESPONSE 1
#define END_PLAYER_TURN 2







void melanger(Card cartes[]);

void initCartes(Card cartes[]);

int receive_msg(Message *msg, int fd);

void process(player* p, Message *msg, player players[],int playerCount);

void removePlayer(player players[],int* playerCount,int index);

void distribution(player players[],int playerCount,Card cartes[]);

void ecart_redistribution(Message m);

#endif
