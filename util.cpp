/**********************************************************************/
/* UTIL.CPP   Librairie de fonctions utilitaires.                     */
/**********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"util.h"
#include"winconsole.h"

/**********************************************************************/
/* Fonctions pour énérer une valeur aléatoire entière.                */
/**********************************************************************/

/* Fonction pour initialiser le générateur aléatoire. */
void init_alea() {
	srand(time(NULL));
}

/* Fonction aléatoire qui renvoie un entier inclu entre [min..max]. */
int  alea(int min, int max) {
	return (int)((1.0 * rand()) / (RAND_MAX + 1) * (max - min + 1)) + min;
}


/************************** DELAI ECRAN *******************************/
/* Effectuer un delai de "msec" millisecondes.                        */
/**********************************************************************/
void delai_ecran(int msec) {
	delay(msec);      //encpasulation de la fonction de "winconsole.h"
}

/************************** EFFACER_LIGNE *****************************/
/* Efface le contenu de la ligne-écran "y".                           */
/**********************************************************************/
void effacer_ligne(int y) {
	gotoxy(0, y + DEBUT_MER);     //on efface cette ligne à l'écran
	clreol();
}

/*************************** AFFICHER CHAR ****************************/
/* Affichera 'ch' qui est soit CH_POISSON ou CH_REQUIN, à la position */
/* (y, x).   Le caractère CH_REQUIN sera affiché en rouge.            */
/**********************************************************************/
void afficher_char(char ch, int x, int y) {
	gotoxy(x, y + DEBUT_MER);     //aller à la position-écran de cette case

	if (ch == CH_REQUIN) {
		textcolor(LIGHTRED);
		printf("%c", ch);       //caractère-requin en ROUGE
		textcolor(WHITE);
	}
	else
		printf("%c", ch);       //c'est un poisson
}

/****************************** AFFICHER ETAT *********************************/
/* Reçoit: numéro d'itération, nombre de poissons, nombre de requins.         */
/* Va afficher ces valeurs au haut de la grille de la mer.                    */
/******************************************************************************/
void afficher_etat(int iter, int nb_poissons, int nb_requins) {
	gotoxy(1, 0); clreol();
	gotoxy(1, 0); printf("ITERATION: %4d", iter);

	clreol();
	printf("\tPoissons = %3d\tRequins = %2d", nb_poissons, nb_requins);
}

/********************************* MESSAGE ************************************/
/* Va afficher un message texte a la 2ieme ligne de la console texte.         */
/******************************************************************************/
void message(const char* mess) {
	gotoxy(1, 1); clreol();
	gotoxy(1, 1); printf("%s", mess);
}

/******************************************************************************/
/******************************************************************************/
