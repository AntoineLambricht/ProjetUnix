/*
	File name: 	util.c
	Author: 	BERGE Benjamin, LAMBRICHT Antoine
	Serie:		1
*/
#include "util.h"

void lire_remove_emplacements(Card * buffer,Card * source,int size,int nbr){
    char l[nbr*2];
    int i,j,tab[nbr];
    int invalide=FALSE;
    printf("Nous allez maintenant choisir l'écart.\nEntrer l'emplacement des %d cartes de l'écart (en commancant par 1)\n",SIZE_ECART);
    printf("usage->1 2 3 ...\n");
    do{
        if(invalide){
            printf("\nInvalide, recommencer\n");
        }
        invalide=FALSE;
        scanf("%s",l);
        tab[0]=atoi(strtok(l," "));
        for(i=1;i<nbr-1;i++){
            fprintf(stderr,"%s",strtok(NULL," "));
            //tab[i]=atoi(strtok(NULL," "));
        }
        exit(0);
        
        /*Verification des doublons*/
        for(i=0;i<nbr;i++){
            for(j=i;j<nbr;j++){
                if(tab[i]==tab[j] || tab[i]>size){
                    invalide=TRUE;
                }
            }
        }
    
    }while(invalide);
    
    for(i=0;i<nbr;i++){
        buffer[i]=source[tab[i]];
    }
    
    
    
    
}