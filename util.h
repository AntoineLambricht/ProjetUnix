/*
	File name: 	util.h
	Author: 	BERGE Benjamin, LAMBRICHT Antoine
	Serie:		1
*/
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include	<unistd.h>

#if ! defined (_UTIL_H_)

#define TRUE 1
#define FALSE 0

#define OK 0
#define KO 1

#define NAME_SIZE 40
#define MESSAGE_SIZE 255

#define INSCRIPTION 0
#define NAME_TAKEN 1 
#define INSCRIPTIONKO 2

void send_message(int type, const char* payload, int socket);

#endif