/**********************************************************************/
/* MAIN.CPP                                                           */
/* Conception : Jean-Christophe Latreille                             */
/**********************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <conio.h>

#include "poisson.h"
#include "requin.h"

/************************** GESTION DE MODE ***************************/

#define MODE_AFF 0	// Valeur de selection du mode affichage
#define MODE_ECR 1	// Valeur de selection du mode ecriture

/************************ PARAMETRES DE DEPART ************************/

#define NB_POISSONS	200		// Nombre de poissons de depart
#define NB_REQUINS 40		// Nombre de requins de depart
#define NB_ITERATIONS 3000	// Nombre maximal d'iterations

/**********************************************************************/
/*                             PROTOTYPES                             */
/**********************************************************************/

// Cette fonction demande a l'utilisateur en quelle mode demarer le   //
// programme. Elle ne recoit aucun parametre.						  //
int demander_mode();

void get_requins_voisins(const t_ocean ocean, int px, int py, t_liste_requins* liste_requins);
/**********************************************************************/
/*                                MAIN                                */
/**********************************************************************/

void main() {
	int mode = demander_mode(),	// Demande du mode a l'utilisateur
		temps = 0,				// Compteur de nombre de jours
		p,						// Compteur du nombre de poissons
		r,						// Compteur du nombre de requins
		nb_poissons,			// Nombre de poissons
		nb_requins,				// Nombre de requins
		px_poisson,				// Position en x d'un poisson
		py_poisson,				// Position en y d'un poisson
		px_requin,				// Position en x d'un requin
		py_requin,				// Position en y d'un requin
		statut_poisson,			// Statut d'un poisson (Mange/Vivant)
		statut_requin,			// Statut d'un requin (Mange/Vivant)
		pub_requin,				// Valeur pour le statut de la puberte d'un requin
		pub_poisson,			// Valeur pour le statut de la puberte d'un poisson

	// Initialisation des listes a vide
	t_liste_poissons l_poissons = {};	// Liste de poissons
	t_liste_requins l_requins = {};	// Liste de requins
	t_ocean ocean = {};				// Grille de l'ocean

	srand(time(NULL));	// Initialise les valeurs aleatoires

	vider_liste_poissons(&l_poissons);
	vider_liste_requins(&l_requins);

	
	// Si le mode ecriture est selectionne
	//if (mode == MODE_ECR) {
	
	// On genere les listes de poissons et de requins de maniere aleatoire
	creer_liste_poisson(&l_poissons, NB_POISSONS, ocean);
	creer_liste_requin(&l_requins, NB_REQUINS, ocean);

	// On obtient le nombre de requins et de poissons
	nb_poissons = get_nb_poissons(l_poissons);
	nb_requins = get_nb_requins(l_requins);

	afficher_etat(temps, nb_poissons, nb_requins);	// On affiche l'etat de depart
	afficher_ocean(ocean);	// On affiche l'ocean de depart

	// Pour chaque iteration
	for (temps; temps <= NB_ITERATIONS; temps++) {
		temps++;	// On augmente le temps (l'iteration)

		// Pour chaque poisson de la liste de poissons
		for (p = 0; p < nb_poissons, p++) {
			// Obtention de la position du poisson
			get_position(&l_poissons[p], &px_poisson, &py_poisson);
			// Verifie si un requin peut le manger
			statut_poisson = get_requins_voisins(ocean, px_poisson,
							 py_poisson, &l_requins);
			// Verifie si le poisson est mort de vieillesse
			statut_poisson = est_mort(&l_poissons[p], MAX_AGE_POISSON);


			// Si le poisson est mort, on l'elimine
			if (statut_poisson == MORT) eliminer_poisson(&l_poissons, &ocean, p);
		}

		// Pour chaque requin de la liste de requins
		for (r = 0; r < nb_requins, r++) {
			// Obtention de la position du requin
			get_position(&l_requins[r], &px_requin, &py_requin);
			// Verifie si le poisson est mort de vieillesse ou de faim
			statut_requin = est_mort(&l_requins[r], MAX_AGE_REQUIN);

			// Si le requin est mort, on l'elimine
			if (statut_requin == MORT) eliminer_requin(&l_requins, &ocean, r);
		}

		// On obtient le nouveau nombre de requins et de poissons
		nb_poissons = get_nb_poissons(l_poissons);
		nb_requins = get_nb_requins(l_requins);

		// Pour chaque requin restant
		for (r = 0; r < nb_requins, r++) {
			// On verifie si le requin a atteint la puberte
			pub_requin = puberte_atteinte(&l_requins[r], NB_JRS_PUB_REQUIN,
						 NB_JRS_GEST_REQUIN);

			// Si le requin a atteint la puberte
			if (pub_requin == PUBERE) {
				ajout_bebe_requin(&l_requins, &ocean, r);	// On ajoute un bebe requin

				// On reinitialise le nombre de jours de gestation a -1 puisqu'il vient de 
				// procreer et on va l'augmenter de +1 par la suite. Le nombre de jours doit 
				// donc etre a 0.
				reset_gestation(&l_requins[r], -1);
			}

			// Sinon on le deplace
			else deplacer_requins(&ocean, &l_requins[r], r);

			// On augmente son age et son nombre de jours de gestation si possible
			inc_age(&l_requins, NB_JRS_PUB_REQUIN);
			// On decremente son niveau d'energie
			dec_energie(&l_requins[r]);
		}

		// Pour chaque poisson restant
		for (p = 0; p < nb_poissons, p++) {
			// On verifie si le poisson a atteint la puberte
			pub_poisson = puberte_atteinte(&l_poissons[p], NB_JRS_PUB_POISSON,
						  NB_JRS_GEST_POISSON);

			// Si le poisson a atteint la puberte
			if (pub_poisson == PUBERE) {
				ajout_bebe_poisson(&l_poissons, &ocean, p);	// On ajoute un bebe poisson

				// On reinitialise le nombre de jours de gestation a -1 puisqu'il vient de 
				// procreer et on va l'augmenter de +1 par la suite. Le nombre de jours doit 
				// donc etre a 0.
				reset_gestation(&l_poissons[p], -1);
				dec_energie(&l_poisson[p]);
			}

			// Sinon on le deplace
			else deplacer_poisson(&ocean, &l_poisson[p], p);

			// On augmente son age et son nombre de jours de gestation si possible
			inc_age(&l_poissons, NB_JRS_PUB_POISSON);
		}

		afficher_etat(temps, nb_poissons, nb_requins);
		afficher_ocean(ocean);
		delai_ecran(250);

	}
	
}

/**********************************************************************/
/*                           LES FONCTIONS                            */
/**********************************************************************/

/************************** DEMANDER_MODE *****************************/
/* Demande le mode de fonctionnement a l'utilisateur.                 */
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

/************************** DEMANDER_MODE *****************************/
/* Demande le mode de fonctionnement a l'utilisateur.                 */
/**********************************************************************/
void get_requins_voisins(const t_ocean ocean, int px, int py, t_liste_requins* liste_requins) {
	int dir = alea(HAUT, HAUT_G),	// Direction aleatoire a verifier
		dx = px,					// Case a verifier en x
		dy = py,					// Case a verifier en y
		est_vide = 0,				// Verificateur de case vide (0: non-vide, 1: vide)
		num_requin;


	// Boucle qui verifie chaque direction possible
	while (!est_vide) {
		// Gestion de chaque direction de maniere independante, ajuste la position en x (dx)
		// et en y (dy) selon la direction a verifier
		switch (dir) {
		case HAUT:
			dy--;
			break;

		case HAUT_DR:
			dx++;
			dy--;
			break;

		case DROITE:
			dx++;
			break;

		case BAS_DR:
			dx++;
			dy++;
			break;

		case BAS:
			dy++;
			break;

		case BAS_G:
			dx--;
			dy++;
			break;

		case GAUCHE:
			dx--;
			break;

		case HAUT_G:
			dx--;
			dy--;
			break;
		}
		// Si la case n'est pas hors-limites et que le contenu de la case
		// est un requin
		if (dy >= 0 && dy < HAUTEUR && ocean[dy][dx].contenu == REQUIN) {
			num_requin = ocean[dy][dx].numero;	// On obtient le numero du requin
			// On incremente l'energie du rquin
			ajout_energie(&liste_requin[num_requin], JRS_DIGESTION);
			return MORT;	// On retourne que le poisson est mort
		}
	}
	return VIVANT;	// On retourne que le poisson est vivant
}