/*
	File name: 	joueur.h
	Author: 	BERGE Benjamin, LAMBRICHT Antoine
	Serie:		1
*/
#if ! defined (_JOUEUR_H_)
#define _JOUEUR_H_

#include 	<fcntl.h>

#include "util.h"
#include "socket.h"
#include "ipc.h"
#include "color.h"

void inscription();

void get_request(int client_socket);

void register_cards(Message msg);

#endif
