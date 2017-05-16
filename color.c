/*
	File name: 	color.c
	Author: 	BERGE Benjamin, LAMBRICHT Antoine
	Serie:		1
*/

#include "color.h"

void print_tab_color(Card *cards,int nb){
    Card *q;
    int i=0;
    for(q=cards;q-cards<nb;q++){
        print_color(*q);
        if(q->num<10){
            printf(" ");
        }
        i++;
        if(i==5){
            printf("\n");
            i=0;
        }else{
            printf(" | ");
        }
    }
    printf("\n");
}

void print_color(Card card){
    int num=card.num;
    
    printf("%d ",num);
    switch(card.couleur){
        case PIQUE:
            couleurOn(0,noirTexte,blancFond);
            printf(PIQUE_C);
            couleurOff();
            break;
        case TREFLE:
            couleurOn(0,noirTexte,blancFond);
            printf(TREFLE_C);
            couleurOff();
            break;
        case COEUR:
            couleurOn(0,rougeTexte,noirFond);
            printf(COEUR_C);
            couleurOff();
            break;
        case CARREAU:
            couleurOn(0,rougeTexte,noirFond);
            printf(CARREAU_C);
            couleurOff();
            break;
        case PAYOO:
            printf("P");
            break;
    }
    
    
}