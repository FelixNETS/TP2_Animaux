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

/************************** GESTION DE MODE ***************************/
#define MODE_AFF 0	// Valeur de selection du mode affichage
#define MODE_ECR 1	// Valeur de selection du mode ecriture

/*********************** PARAMETRES DE DEPART *************************/
#define NB_POISSONS	200		// Nombre de poissons de depart
#define NB_REQUINS 40		// Nombre de requins de depart
#define NB_ITERATIONS 3000	// Nombre maximal d'iterations



void main() {
	int mode = demander_mode(),	// Demande du mode a l'utilisateur
		temps = 0;				// Compteur de nombre de jours

	// Initialisation des listes a vide
	t_liste_poissons l_poissons = {};	// Liste de poissons
	t_liste_requins l_requins = {};	// Liste de requins
	t_ocean ocean = {};				// Grille de l'ocean

	srand(time(NULL));	// Initialise les valeurs aleatoires

	vider_liste_poissons
	
	// Si le mode ecriture est selectionne
	if (mode == MODE_ECR) {

	}
	
	// On genere les listes de poissons et de requins de maniere aleatoire
	creer_liste_poisson(*l_poissons, NB_POISSONS, ocean);
	creer_liste_requin(*l_requins, NB_REQUINS, ocean);

	// On affiche l'ocean de depart
	afficher_ocean(ocean);
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

