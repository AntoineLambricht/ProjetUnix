#
#	File name: 	Makefile
#	Author: 	BERGE Benjamin, LAMBRICHT Antoine
#	Serie:		1
#
CC=/usr/bin/cc
CFLAGS=-W -Wall

all : server joueur

server : server.o socket.o util.o sharedMemory.o
	$(CC) -g -o server server.o util.o socket.o sharedMemory.o
server.o : server.c server.h util.h socket.h sharedMemory.h
	$(CC) -c server.c $(CFLAGS)

joueur : joueur.o util.o socket.o sharedMemory.o
	$(CC) -g -o joueur joueur.o util.o socket.o sharedMemory.o
joueur.o : joueur.c joueur.h util.h socket.h sharedMemory.h
	$(CC) -c joueur.c $(CFLAGS)

sharedMemory.o: sharedMemory.c sharedMemory.h util.h
	$(CC) -c sharedMemory.c $(CFLAGS)

util.o: util.c util.h
	$(CC) -c util.c $(CFLAGS)

socket.o: socket.c socket.h
	$(CC) -c socket.c $(CFLAGS)
