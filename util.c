/*
	File name: 	util.c
	Author: 	BERGE Benjamin, LAMBRICHT Antoine
	Serie:		1
*/
#include "util.h"
 
void send_message(int type, const char* payload, int socket) {
	char msg[MESSAGE_SIZE];
	sprintf(msg, "%d %s", type, payload);
	if (send(socket, msg, MESSAGE_SIZE, 0) == -1) {
		perror("Failed to send a message to the serveur");
		exit(1);
	}
}

