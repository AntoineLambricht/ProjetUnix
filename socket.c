/*
	File name: 	socket.c
	Author: 	BERGE Benjamin, LAMBRICHT Antoine
	Serie:		1
*/

#include "socket.h"

void send_message(Message m, int socket) {
	fprintf(stderr,"Message send :%d\n",m.action);
	if (send(socket, &m, sizeof(Message),0) == -1) {
		perror("Failed to send a message to the serveur");
		exit(1);
	}
}


void initiateServer(int *server_socket,int port){
	struct sockaddr_in my_address;
	if((*server_socket = socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("Erreur socket server");
		exit(1);
	}
	memset(&my_address,0,sizeof(struct sockaddr_in));
	my_address.sin_family = AF_INET;
	my_address.sin_addr.s_addr = htonl(INADDR_ANY);
	my_address.sin_port = htons(port);

	if( bind(*server_socket, (struct sockaddr *)&my_address, sizeof(my_address)) < 0 ){
		perror("server - bind");
        exit(1);
    }


	if (listen(*server_socket,4)) {
		perror("Listen");
		exit(EXIT_FAILURE);
	}

	/*fprintf(stderr,"Server initiate at %s %d\n",inet_ntoa(my_address.sin_addr), ntohs(my_address.sin_port));*/

}

void initiateConnection(int *client_socket,struct hostent *host,int port){
	struct sockaddr_in server_address;
	if((*client_socket = socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("Erreur socket server");
		exit(1);
	}

	memset(&server_address,0,sizeof(struct sockaddr_in));
	server_address.sin_family = AF_INET;
	server_address.sin_addr = *((struct in_addr*)host->h_addr);
	server_address.sin_port = htons(port);

	if( connect(*client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0 ){
		perror("client - connect");
        exit(1);
    }
}
