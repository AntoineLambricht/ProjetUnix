/*
	File name: 	joueur.c
	Author: 	BERGE Benjamin, LAMBRICHT Antoine
	Serie:		1
*/
#include "joueur.h"

Card* our_cards;
int our_size;
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

	//initialise la connection et l'inscription
	Message msg = inscription();
	initiateConnection(&client_socket,host,port,msg);
	fprintf(stderr,"Connected\n");
	
	while(TRUE){
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





void choose_card(int socket){
    Message msg;
    Card c [1];
    int couleur, contains;
    printf("On est dans choose card\n");
    Card* pli = lirePlis();
    couleur=pli[0].couleur;
    contains = contains_color(couleur);
	printf("Couleur : %d",couleur);
    if(couleur!=0){
        char *couleur_str;
        switch(couleur){
            case TREFLE:
                couleur_str="trefle";
                break;
            case PIQUE:
                couleur_str="Pique";
                break;
            case COEUR:
                couleur_str="coeur";
                break;
            case CARREAU:
                couleur_str="carreau";
                break;
            case PAYOO:
                couleur_str="payoo";
                break;
        }
        printf("La couleur est %s\n",couleur_str);
    }
    printf("Entrer l'emplacement de la carte que vous désirez placer\n");
    lire_remove_emplacements(c,our_cards,&our_size,1);
    while(couleur!=0 && couleur!=msg.payload.carte.couleur && contains){
        printf("Cette carte n'est pas de la bonne couleur\n");
        lire_remove_emplacements(c,our_cards,&our_size,1);
    }
    msg.payload.carte=c[0];
    msg.action=REPONSE_CARTE;
	fprintf(stderr,"Carte envoyée : %d couleur %d",msg.payload.carte.num,msg.payload.carte.couleur);
    send_message(msg,socket);
}

int contains_color(int couleur){
    Card *q;
    if(couleur==0){
        return FALSE;
    }
    for(q=our_cards;q-our_cards<our_size;q++){
        if(q->couleur==couleur){
            return TRUE;
        }
    }
    return FALSE;
}

void get_request(int server_socket){
	Message msg;
    int couleur_payoo;
	if (receive_msg(&msg,server_socket)){
		fprintf(stderr,"Message action from server :%d\n",msg.action);
		int action = msg.action;
		switch(action){
			case INSCRIPTIONKO:
                fprintf(stderr,"%s",msg.payload.str);
                exit(1);
            case DISTRIBUTION:
                register_cards(msg,server_socket);
                break;
            case DISTRIBUTION_ECART:;
		int new_size;
		new_size=MAX_CARD_BY_PLAYER;
		memcpy(our_cards+our_size,msg.payload.ecart,sizeof(Card)*SIZE_ECART);
		our_size=new_size;
                printf("Ecart reçu\n");
                print_tab_color(msg.payload.ecart, SIZE_ECART);
                break;
            case PAPAYOO:
                couleur_payoo=msg.payload.papayoo;
                break;
            case DEMANDE_CARTE:
                printf("Vos cartes\n");
                print_tab_color(our_cards, our_size);
                printf("On va vers choose card\n");
                choose_card(server_socket);
                break;
            case DEMANDE_POINTS:
				//TODO
		break;
            case PLI_UPDATE:
                fprintf(stderr,"UPDATE PLI\n"); 
		break;
            case ALERTE_FIN_PARTIE:
				//TODO
		break;
            default:
		perror("action invalide");
                exit(1);
		}
	}else{
		exit(1);
	}

}

Message inscription(){
	char name[NAME_SIZE];
	Message inscription;
	
	printf("Enter your name > ");
	scanf("%s", name);
	fflush(stdin);
	fflush(stdout);
				
	inscription.action = INSCRIPTION;
	strcpy(inscription.payload.name,name);
				
	return inscription;
}

void register_cards(Message msg, int socket){
    Message m;
    Dist deck= msg.payload.dist;
    int nbr = deck.nbr;
    our_cards=deck.cards;
    print_tab_color(our_cards,nbr);
    printf("Vous allez maintenant choisir l'ecart\n");
    lire_remove_emplacements(m.payload.ecart,our_cards,&nbr,SIZE_ECART);
    our_size=nbr;
    m.action=ENVOI_ECART;
   
    send_message(m,socket);
    
}


void lire_remove_emplacements(Card * buffer,Card * source,int *size,int nbr){
    char l[nbr*2];
    Card new_source[*size-nbr];
    int i,j,x,tab[nbr];
    int invalide=FALSE;
    char * token;
    /*Entrée des cartes*/
    printf("Entrer l'emplacement des %d cartes (en commancant par 0)\n",nbr);
    printf("usage->1-2-3 ...\n");
    /*validation du bon format*/
    do{
        if(invalide){
            printf("\nInvalide, recommencer\n");
        }
        invalide=FALSE;
        scanf("%s",l);
        printf("\n%s\n",l);
        token=strtok(l,"-");
        tab[0]=atoi(token);
        i=1;
        
        
        while(i<nbr && token!=NULL){
            token=strtok(NULL,"-");
            if(token!=NULL){
                tab[i]=atoi(token);
                i++;
            }
        }
        if(i!=6){
            invalide=TRUE;
            break;
        }
        
        /*Verification des doublons et de l'absence de la carte*/
        for(i=0;i<nbr;i++){
            for(j=i;j<nbr;j++){
                if(tab[i]==tab[j] || tab[i]>*size){
                    invalide=TRUE;
                }
            }
        }
    
    }while(invalide);
    
    /*copie de l'ecart dans le buffer*/
    for(i=0;i<nbr;i++){
        buffer[i]=source[tab[i]];
    }
    /*réécriture de la source sans l'ecart*/
    *size=*size-nbr;
    j=0;
    i=0;
    x=0;
    while(i<*size){
        if(j==tab[x]){
            j++;
            x++;
        }else{
            new_source[i]=source[j];
            i++;
            j++;
        }
    }
    source=new_source;    
}

