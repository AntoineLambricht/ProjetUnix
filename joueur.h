/*
	File name: 	joueur.h
	Author: 	BERGE Benjamin, LAMBRICHT Antoine
	Serie:		1
*/
#if ! defined (_JOUEUR_H_)
#define _JOUEUR_H_

#include 	<fcntl.h>
#include 	<signal.h>
#include "util.h"
#include "socket.h"
#include "ipc.h"
#include "color.h"

Message inscription();



void register_cards(Message msg, int socket, Card* our_cards, int *our_size);

void lire_remove_emplacements(Card * buffer,Card * source,int *size,int nbr);

int contains_color(int couleur, Card* our_cards,int our_size);

void choose_card(int socket, Card* our_cards, int *our_size);

int receive_msg(Message *msg, int fd);

void timer_handler(int signal);

void shutdown_joueur();

void quit_handler(int signal);

#endif
