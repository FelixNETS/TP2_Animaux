/**********************************************************************/
/* MAIN.CPP                                                           */
/* Conception : Jean-Christophe Latreille                             */
/**********************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <conio.h>

#include "util.h"
#include "poisson.h"
#include "requin.h"

#define MODE_AFF 0	// Valeur de selection du mode affichage
#define MODE_ECR 1	// Valeur de selection du mode ecriture

void main() {
	int mode = demander_mode();	// Demande du mode a l'utilisateur

	srand(time(NULL));	// Initialise les valeurs aleatoires
	
	if (mode == MODE_ECR) {

	}


}


/**********************************************************************/
int demander_mode() {
	int reponse;	// Valeur ASCII de la reponse appuyee au clavier

	// Boucle qui continue tant et aussi longtemps que l'utilisateur n'a pas entre o/O/n/N
	do {
		// Demande du mode a l'utilisateur
		printf("Souhaitez vous demarrer la simulation en mode affichage? (O/N) ");
		reponse = _getch();	// Attente de l'entree d'une touche par l'utilisateur (o/O/n/N)

		// Si la reponse n'est pas o/O/n/N
		if (reponse != 'o' && reponse != 'O' && reponse != 'n' && reponse != 'N') {
			printf("Reponse invalide! Vous devez entrer O (oui) ou N (non)");
			delai_ecran(1500);	// Delai pour permettre la lecture du message d'erreur
		}

	} while (reponse != 'o' && reponse != 'O' && reponse != 'n' && reponse != 'N')
	
	// Si la reponse est oui, on assigne le mode affichage (0)
	if (reponse == 'o' || reponse == 'O') return MODE_AFF;

	// Si la reponse est non, on assigne le mode ecriture (1)
	else if (reponse == 'n' || reponse == 'N') return MODE_ECR;

}

