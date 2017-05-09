/*
	File name: 	joueur.c
	Author: 	BERGE Benjamin, LAMBRICHT Antoine
	Serie:		1
*/
#include "joueur.h"


int main(int argc,char** argv){
	char name[NAME_SIZE];
	int client_socket,port;
	struct hostent *host;
	

	if( argc != 3 )
    {   fprintf(stderr,"Usage: %s ip port\n",argv[0]);
        exit(1);
    }
	
	if ((host=gethostbyname(argv[1])) == NULL) {
		perror("Client: gethostbyname failed");
		exit(EXIT_FAILURE);
	}
	port = atoi(argv[2]);

	initiateConnection(&client_socket,host,port);
	fprintf(stderr,"Connected\n");
	printf("Enter your name > ");
	scanf("%s", name);
	fflush(stdin);
	fflush(stdout);
	send_message(INSCRIPTION, name, client_socket);
	
	while(TRUE){
		get_request(client_socket);
		
	}
	close(client_socket);
	return EXIT_SUCCESS;
}

int receive_msg(char* msg, int fd) {
	int bytes_received;
	if ((bytes_received = recv(fd, msg, MESSAGE_SIZE, 0)) <= 0) {
		if (bytes_received == 0) {
			printf("Server disconnected.\n");
		}
		else {
			perror("Could not receive message\n");
		}
		return FALSE;
	}
	return TRUE;
}

void get_request(int server_socket){
	char msg[MESSAGE_SIZE];
	char* value;
    int action;
	char name[NAME_SIZE];
	if (receive_msg(msg,server_socket)){
		fprintf(stderr,"Message from server :%s\n",msg);
		value=strtok(msg," ");
		action=atoi(value);
		value=strtok(NULL," ");
		switch(action){
			case NAME_TAKEN:
				printf("Enter your name > ");
				scanf("%s", name);
				fflush(stdin);
				fflush(stdout);
				send_message(INSCRIPTION, name, server_socket);
				break;
			case INSCRIPTIONKO:
				fprintf(stderr,"%s",value);
				exit(1);
			default:
				perror("action invalide");
                exit(1);
		}
	}else{
		exit(1);
	}
	
}






