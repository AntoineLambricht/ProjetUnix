/*
	File name: 	socket.h
	Author: 	BERGE Benjamin, LAMBRICHT Antoine
	Serie:		1
*/

#if ! defined (_SOCKET_H_)

#include    <stdio.h>
#include    <stdlib.h>
#include    <sys/socket.h>
#include    <sys/types.h>
#include	<arpa/inet.h>
#include    <netinet/in.h>
#include    <netdb.h>
#include	<unistd.h>
#include 	<errno.h>
#include    <string.h>

#define h_addr h_addr_list[0] 

void initiateServer(int *server_socket,int port);

void initiateConnection(int *client_socket,struct hostent *host,int port);

#endif