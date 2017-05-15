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



void get_request(int client_socket);

#endif
