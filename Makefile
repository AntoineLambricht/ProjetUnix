#
#	File name: 	Makefile
#	Author: 	BERGE Benjamin, LAMBRICHT Antoine
#	Serie:		1
#
CC=/usr/bin/cc
CFLAGS=-W -Wall

all : server joueur

server : server.o socket.o util.o ipc.o color.o
	$(CC) -g -o server server.o util.o socket.o ipc.o color.o

server.o : server.c server.h util.h socket.h ipc.h color.h
	$(CC) -c server.c $(CFLAGS)

joueur : joueur.o util.o socket.o ipc.o color.o
	$(CC) -g -o joueur joueur.o util.o socket.o ipc.o color.o

joueur.o : joueur.c joueur.h util.h socket.h ipc.h color.h
	$(CC) -c joueur.c $(CFLAGS)

ipc.o: ipc.c ipc.h util.h
	$(CC) -c ipc.c $(CFLAGS)

util.o: util.c util.h
	$(CC) -c util.c $(CFLAGS)

socket.o: socket.c socket.h
	$(CC) -c socket.c $(CFLAGS)

color.o: color.c color.h
	$(CC) -c color.c $(CFLAGS)
