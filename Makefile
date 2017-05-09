#
#	File name: 	Makefile
#	Author: 	BERGE Benjamin, LAMBRICHT Antoine
#	Serie:		1
#
CC=gcc
CFLAGS=-W -Wall -pedantic

all : server joueur

server : server.o util.o socket.o
	$(CC) -g -o server server.o util.o socket.o
server.o : server.c server.h util.h socket.h
	$(CC) -c server.c $(CFLAGS)
 
joueur : joueur.o util.o socket.o
	$(CC) -g -o joueur joueur.o util.o socket.o
joueur.o : joueur.c joueur.h util.h socket.h
	$(CC) -c joueur.c $(CFLAGS)

util.o: util.c util.h
	$(CC) -c util.c $(CFLAGS)

socket.o: socket.c socket.h
	$(CC) -c socket.c $(CFLAGS)