/*
	File name: 	server.c
	Author: 	BERGE Benjamin, LAMBRICHT Antoine
	Serie:		1
*/
#include "server.h"


int timer_is_over;

void timer_handler(int signal){
	if (signal == SIGALRM) {
		/*TODO si il n'y à pas asser de joueurs restart l'inscription (ou continuer d'attendre ?)
		sinon lancer la partie*/
		timer_is_over = TRUE;
		fprintf(stderr,"Timer end\n");
	}
}


int main(int argc,char** argv){
	/*char buffer[256];*/
	Card cartes[NB_CARDS];
	Card ecarts[MAX_PLAYERS][SIZE_ECART];
	player players[MAX_PLAYERS] = {{0}};
	int server_socket,port,highestFd,playerCount = 0;
	int playing = FALSE;
	int game_state = 0;
	int turn_state = 0;
	int player_turn_state = 0;
	int ecartCount = 0;
	struct timeval timeout;
	struct sigaction timer;
	fd_set fdset;
	Message message;
	Card pli[MAX_PLAYERS];
	
	initSharedMemory(TRUE);
	init_semaphore(TRUE);

	initCartes(cartes);
	
	
	melanger(cartes);

	if( argc != 2 ){
		fprintf(stderr,"Usage: %s port\n",argv[0]);
		exit(1);
	}
	/*initialise le server pour qu'il réagisse au signal SIGALARM*/
	timer.sa_handler = &timer_handler;
	sigemptyset(&timer.sa_mask);
	sigaction(SIGALRM, &timer, NULL);

	port = atoi(argv[1]);

	initiateServer(&server_socket,port);




	while(TRUE){

		int action,i,j;


		FD_ZERO(&fdset);
		FD_SET(server_socket,&fdset);
		highestFd = server_socket+1;
		for (i = 0; i < MAX_PLAYERS; i++) {
			if (players[i].socket > 0) {
				FD_SET(players[i].socket, &fdset);
			}
			if (players[i].socket >= highestFd) {
				highestFd = players[i].socket+1;
			}
		}

		timeout.tv_sec  = 2;
		timeout.tv_usec = 500000;

		action = select(8,&fdset,NULL,NULL,&timeout);

		if(action >0){
			//si le socket d'inscription est modifié
			if(FD_ISSET(server_socket,&fdset)){
				
				struct sockaddr_in clientAdress;
				int len = sizeof(clientAdress);
				
				int clientSkt = accept(server_socket,(struct sockaddr *)&clientAdress,(socklen_t*)&len);
			
				fprintf(stderr,"Connection from %s %d\n",inet_ntoa(clientAdress.sin_addr), ntohs(clientAdress.sin_port));
			
				
				
				if(playerCount<MAX_PLAYERS && !playing){
					//inscription de l'utilisateur
					Message msg;
					Message nameTaken;
					if(receive_msg(&msg,clientSkt)){
						if(msg.action == INSCRIPTION){
							int i,nameOK;
							nameOK = TRUE;
							//test si un joueur à déjà ce nom
							for(i=0;i<playerCount;i++){
								if(strcmp(players[i].name,msg.payload.name)==0){
									nameOK = FALSE;
									break;
								}
							}
							//si le nom est bon , on enregistre le joueur 
							if(nameOK){
								strcpy(players[playerCount].name, msg.payload.name);
								players[playerCount++].socket = clientSkt;
								
								
								ecrirePlayers(players,playerCount);
								fprintf(stderr,"Player %s à été inscrit (socket : %d) \n",players[playerCount-1].name,players[playerCount-1].socket);
								
								if(playerCount == 2){
									fprintf(stderr,"Timer start\n");
									alarm(30);
								}
							}							
							//sinon on lui envoie un message
							else{
								nameTaken.action = INSCRIPTIONKO;
								strcpy(nameTaken.payload.str,"Inscription refusé : Nom déjà pris\n");
								send_message(nameTaken,clientSkt);
								close(clientSkt);
							}
						}
					}else{
						close(clientSkt);
					}
					
				}else{
					message.action = INSCRIPTIONKO;
					strcpy(message.payload.str,"Impossible de s'inscrire pour le moment\n");
					send_message(message,clientSkt);
				}
			}
			// pour chaque joueur enregistré , on test si son socket à été modifié
			for (i = 0; i < playerCount; i++) {
				if (FD_ISSET(players[i].socket, &fdset)) {
					//si oui , on lis le message 
					Message msg;
					Message distribution_ecart;
					if (receive_msg(&msg, players[i].socket)) {					
						switch(msg.action){
							
							case ENVOI_ECART:
								memcpy(&ecarts[i],msg.payload.ecart,sizeof(Card)*SIZE_ECART);
								ecartCount++;
								fprintf(stderr,"Ecart reçu de %s\n",players[i].name);
								if(ecartCount == playerCount){
									/*distribution des écarts*/
									fprintf(stderr,"Tout les écart on été reçu\n");
									for (j = 0; j < playerCount; j++) {
										distribution_ecart.action = DISTRIBUTION_ECART;
										if(j==playerCount-1){
											memcpy(distribution_ecart.payload.ecart,&ecarts[0],sizeof(Card)*SIZE_ECART);
										}else{
											memcpy(distribution_ecart.payload.ecart,&ecarts[j+1],sizeof(Card)*SIZE_ECART);
										}
										send_message(distribution_ecart,players[j].socket);
										game_state = 2;
									}
								}
								break;
							case REPONSE_CARTE:
								pli[i]=msg.payload.carte;
								ecrirePlis(pli);
								//TODO changer le game state
								break;
							case REPONSE_POINTS:
								//TODO
								
								break;
							default:
								perror("action invalide\n");
								exit(1);
						}
					} else {
						fprintf(stderr,"Removing player \n");
						removePlayer(players,&playerCount,i);
						for (j = 0; j < MAX_PLAYERS; j++){
							fprintf(stderr,"Player %d -> %s \n",j,players[j].name);
						}
					}

				}
			}
		}
		if(playing){
			switch(game_state){
				//debut de manche
				case 0:
					distribution(players,playerCount,cartes);
                    game_state=1;
					break;
				//choix et redistribution des écarts
				case 1:
					// ne rien faire ? 
					break;
				//tirage au sort du papayoo
				case 2:
					//TODO
					break;
				//tours
				case 3:
					//TODO
					switch(turn_state){
						//debut du tour
						case 1:
							switch(player_turn_state){
								//waiting for response ?
								case 1:
									break;
								//get response , switch player turn
								case 2:
									
									break;
								
							}
							break;
						//fin du tour et envois du plis 
						case 2:
							break;
							
					}
					break;
				
				default:
					break;
			}			
		}else{
			if(timer_is_over){
				if(playerCount>=2){
					playing = TRUE;

				}else{
					alarm(30);
				}
			}
		}

	}
    close(server_socket);
	return EXIT_SUCCESS;
}

void removePlayer(player players[],int* playerCount,int index){
	int j;
	close(players[index].socket);
	players[index].socket = 0;
	memcpy(players[index].name, "\0", NAME_SIZE);
	(*playerCount)--;

	for (j = index+1; j <= *playerCount; j++) {
		players[j-1].socket = players[j].socket;
		sprintf(players[j-1].name, "%s", players[j].name);
	}
	players[j-1].socket = 0;
	memcpy(players[j-1].name, "\0", NAME_SIZE);
	ecrirePlayers(players,*playerCount);

}


int receive_msg(Message *msg, int fd) {
	int bytes_received;
	if ((bytes_received = recv(fd, msg, sizeof(Message), 0)) <= 0) {
		if (bytes_received == 0) {
			printf("Client disconnected.\n");
		}
		else {
			perror("Could not receive message");
		}
		return FALSE;
	}
	return TRUE;
}

void initCartes(Card cartes[]){
	int i,c = 1;
	for(i=1;i<=NB_CARDS;i++){
		if(c<PAYOO){
			cartes[i-1].couleur = c;
			
			if(i%10 == 0){
				c+=1;
				cartes[i-1].num = 10;
			}else{
				cartes[i-1].num = (i%10);
			}
		}else{
			cartes[i-1].num = (i-40);
			cartes[i-1].couleur = c;
		}
		
	}
}

void melanger(Card cartes[]){
	srand(time(NULL));
    size_t i;
    for (i = 0; i < NB_CARDS-1; i++) {
		size_t j = i + rand() / (RAND_MAX / (NB_CARDS - i) + 1);
        Card t = cartes[j];
        cartes[j] = cartes[i];
        cartes[i] = t;
	}
    
}

void distribution(player players[],int playerCount,Card cartes[]){
    Message deck;
    Dist dist;
    Card *cartes_player;
	int i, n = NB_CARDS/playerCount;
    int x,j=0;
    cartes_player=malloc(n*sizeof(Card));
        
    for(i=0;i<playerCount;i++){
        memcpy(cartes_player,cartes+j,n*sizeof(Card));
        dist.nbr=n;
        for(x=0;x<n;x++){
            dist.cards[x]=cartes_player[x];
        }
        deck.action = DISTRIBUTION;
        deck.payload.dist =dist;
        send_message(deck,players[i].socket);
        j+=n;
    }
}
