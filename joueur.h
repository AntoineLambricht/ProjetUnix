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

Message inscription();

void get_request(int client_socket);

void register_cards(Message msg, int socket);

void lire_remove_emplacements(Card * buffer,Card * source,int *size,int nbr);

int contains_color(int couleur);

void choose_card(int socket);

#endif
