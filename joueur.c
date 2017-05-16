/*
	File name: 	joueur.c
	Author: 	BERGE Benjamin, LAMBRICHT Antoine
	Serie:		1
*/
#include "joueur.h"

Card* our_cards;
int main(int argc,char** argv){
	int client_socket,port;
	struct hostent *host;
    
	if( argc != 3 ){
		   fprintf(stderr,"Usage: %s ip port\n",argv[0]);
        exit(1);
    }

	if ((host=gethostbyname(argv[1])) == NULL) {
		perror("Client: gethostbyname failed");
		exit(EXIT_FAILURE);
	}
	port = atoi(argv[2]);

	initSharedMemory(FALSE);
	init_semaphore(FALSE);


	initiateConnection(&client_socket,host,port);
	
	fprintf(stderr,"Connected\n");
	
	inscription(client_socket);

	while(TRUE){
		/*fprintf(stderr,"Nb players = %d\n",shm_ptr->nbPlayers);*/
		lirePoints();
		get_request(client_socket);

	}
	close(client_socket);
	return EXIT_SUCCESS;
}

int receive_msg(Message *msg, int fd) {
	int bytes_received;
	if ((bytes_received = recv(fd, msg, sizeof(Message), 0)) <= 0) {
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

void inscription(int server_socket){
	char name[NAME_SIZE];
	Message inscription;
	
	printf("Enter your name > ");
	scanf("%s", name);
	fflush(stdin);
	fflush(stdout);
				
	inscription.action = INSCRIPTION;
	strcpy(inscription.payload.name,name);
				
	send_message(inscription, server_socket);
}

void get_request(int server_socket){
	Message msg;
	if (receive_msg(&msg,server_socket)){
		fprintf(stderr,"Message action from server :%d\n",msg.action);
		
		switch(msg.action){
			case NAME_TAKEN:
				inscription(server_socket);
				break;
			case INSCRIPTIONKO:
				fprintf(stderr,"%s",msg.payload.str);
				exit(1);
            case DISTRIBUTION:
                register_cards(msg,server_socket);
                break;
			default:
				perror("action invalide");
                exit(1);
		}
	}else{
		exit(1);
	}

}

void register_cards(Message msg, int socket){
    Message m;
    int res,i;
    Card ecart[SIZE_ECART];
    Dist deck= msg.payload.dist;
    int nbr = deck.nbr;
    our_cards=deck.cards;
    print_tab_color(our_cards,nbr);
    printf("Nous allez maintenant choisir l'écart.\nEntrer l'emplacement des %d cartes de l'écart (en commancant par 1)\n",SIZE_ECART);
    printf("usage->1 2 3 ...\n");
    fflush(stdin);
    for(i=0;i<SIZE_ECART;i++){
        printf("Entrer la %d carte", SIZE_ECART-i);
        scanf("%d",&res);
        ecart[i]=our_cards[res-1];
    }
    for(i=0;i<SIZE_ECART;i++){
        m.payload.ecart[i]=ecart[i];
    }
    /*lire_remove_emplacements(m.payload.ecart,our_cards,nbr,SIZE_ECART);*/
    m.action=DISTRIBUTION;
   
    send_message(m,socket);
    
    
    
}
