/**********************************************************************/
/* MAIN.CPP                                                           */
/* Conception : Jean-Christophe Latreille                             */
/**********************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>

#include "poisson.h"
#include "requin.h"

/************************** GESTION DE MODE ***************************/

#define MODE_AFF 0	// Valeur de selection du mode affichage
#define MODE_ECR 1	// Valeur de selection du mode ecriture

/************************ PARAMETRES DE DEPART ************************/

#define NB_POISSONS	200		// Nombre de poissons de depart
#define NB_REQUINS 40		// Nombre de requins de depart
#define NB_ITERATIONS 5000	// Nombre maximal d'iterations

/**********************************************************************/
/*                             PROTOTYPES                             */
/**********************************************************************/

/************************** DEMANDER_MODE *****************************/
/* Demande le mode de fonctionnement a l'utilisateur.                 */
/**********************************************************************/

int demander_mode();

/*********************** GET_REQUINS_VOISINS **************************/
/* recherche de requins voisin a un poisson			                  */
/**********************************************************************/

int get_requins_voisins(const t_ocean ocean, int px, int py, t_liste_requins* liste_requins);

/************************* TRAITER POISSONS ***************************/
/* traitement des poissons vivants deplaement et naissance            */
/**********************************************************************/

void traiter_poissons(t_liste_poissons* l_poissons, t_ocean* ocean,
	int nb_poissons, int pub_poisson, int p);

/********************** TRAITER POISSONS MORTS ************************/
/* gestion de la mort des poissons					                  */
/**********************************************************************/

void traiter_poissons_morts(t_liste_poissons* l_poissons, t_liste_requins* l_requins,
	t_ocean* ocean, int* nb_poissons, int p, int px_poisson,
	int py_poisson, int statut_poisson);

/************************** TRAITER REQUINS ***************************/
/* traitement des requins vivants deplaement et naissance             */
/**********************************************************************/

void traiter_requins(t_liste_requins* l_requins, t_ocean* ocean, int nb_requins,
	int pub_requin, int r);

/*********************** TRAITER REQUINS MORTS ************************/
/* gestion de la mort des requins					                  */
/**********************************************************************/

void traiter_requins_morts(t_liste_requins* l_requins, t_ocean* ocean,
	int* nb_requins, int r, int px_requin, int py_requin, int statut_requin);

/**********************************************************************/
/*                                MAIN                                */
/**********************************************************************/

void main() {

	int mode = demander_mode(),	// Demande du mode a l'utilisateur
		temps = 0,				// Compteur de nombre de jours
		p = 0,					// Compteur du nombre de poissons
		r = 0,					// Compteur du nombre de requins
		nb_poissons = 0,		// Nombre de poissons
		nb_requins = 0,			// Nombre de requins
		px_poisson = 0,			// Position en x d'un poisson
		py_poisson = 0,			// Position en y d'un poisson
		px_requin = 0,			// Position en x d'un requin
		py_requin = 0,			// Position en y d'un requin
		statut_poisson = 0,		// Statut d'un poisson (Mange/Vivant)
		statut_requin = 0,		// Statut d'un requin (Mange/Vivant)
		pub_requin = 0,			// Valeur pour le statut de la puberte d'un requin
		pub_poisson = 0,		// Valeur pour le statut de la puberte d'un poisson
		max_poissons = 500,		// Quantite maximale de poissons permise
		max_requins = 80;		// Quantite maximale de requins permise

	// Initialisation des listes a vide
	t_liste_poissons l_poissons = {};	// Liste de poissons
	t_liste_requins l_requins = {};	// Liste de requins
	t_ocean ocean = {};				// Grille de l'ocean

	srand(time(NULL));	// Initialise les valeurs aleatoires

	vider_liste_poissons(&l_poissons);
	vider_liste_requins(&l_requins);

	FILE* stats = NULL;
	
	// Si le mode ecriture est selectionne on cree le fichier 
	if (mode == MODE_ECR) {
		stats = fopen("C:\\Users\\filna\\OneDrive\\Desktop\\stats3.txt", "w");
	}

	// On genere les listes de poissons et de requins de maniere aleatoire
	creer_liste_poissons(&l_poissons, NB_POISSONS, ocean, max_poissons);
	creer_liste_requins(&l_requins, NB_REQUINS, ocean, max_requins);

	// On obtient le nombre de requins et de poissons
	nb_poissons = get_nb_poissons(l_poissons);
	nb_requins = get_nb_requins(l_requins);

	afficher_etat(temps, nb_poissons, nb_requins);	// On affiche l'etat de depart
	afficher_ocean(ocean);	// On affiche l'ocean de depart

	// Pour chaque iteration
	for (temps; temps < NB_ITERATIONS; temps++) {

		// traitement des poissons morts
		traiter_poissons_morts(&l_poissons, &l_requins, &ocean, &nb_poissons,
			p, px_poisson, py_poisson, statut_poisson);

		// traitement des requins morts
		traiter_requins_morts(&l_requins, &ocean, &nb_requins, r,
			px_requin, py_requin, statut_requin);

		// On obtient le nouveau nombre de requins et de poissons
		nb_poissons = get_nb_poissons(l_poissons);
		nb_requins = get_nb_requins(l_requins);

		// traitement des requins restants
		traiter_requins(&l_requins, &ocean, nb_requins, pub_requin, r);

		// traitement des poissons restants
		traiter_poissons(&l_poissons, &ocean, nb_poissons, pub_poisson, p);

		// On update le nouveau nombre de requins et de poissons
		nb_poissons = get_nb_poissons(l_poissons);
		nb_requins = get_nb_requins(l_requins);

		if (mode == MODE_ECR) {

			// imprime les donnees dans le fichier texte
			fprintf(stats, "%d\t %d\t %d\n", temps, nb_poissons, nb_requins);
		}
		else {

			// on fait les affichages avec les nouvelles valeurs
			afficher_etat(temps, nb_poissons, nb_requins);
			afficher_ocean(ocean);
			delai_ecran(50);		// clock de chaque iteration
		}

		if (!nb_poissons) {

			// message d'extinction et on sort de la boucle
			message("Extinction poissons!");
			break;
		}
		if (!nb_requins) {

			// message d'extinction et on sort de la boucle
			message("Extinction requins!");
			break;
		}

	}

	// affichage final
	afficher_etat(temps, nb_poissons, nb_requins);
	afficher_ocean(ocean);

	// free la memoire de heap utilisee
	liberer_liste_poissons(&l_poissons);
	liberer_liste_requin(&l_requins);
	
	// fermeture du fichier si utilise
	if (mode == MODE_ECR) {
		fclose(stats);
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
		message("Souhaitez vous demarrer la simulation en mode affichage? (O/N) ");
		reponse = tolower(_getch());	// Attente de l'entree d'une touche par l'utilisateur (o/O/n/N)

		// Si la reponse n'est pas o/O/n/N
		if (reponse != 'o' && reponse != 'n') {
			message("Reponse invalide! Vous devez entrer O (oui) ou N (non) ");
			delai_ecran(1500);	// Delai pour permettre la lecture du message d'erreur
		}

	} while (reponse != 'o' && reponse != 'n');

	// efface le message
	effacer_ligne(-1);
	
	// Si la reponse est oui, on assigne le mode affichage (0)
	if (reponse == 'o') return MODE_AFF;

	// Si la reponse est non, on assigne le mode ecriture (1)
	else if (reponse == 'n') return MODE_ECR;

}

/*********************** GET_REQUINS_VOISINS **************************/
/* recherche de requins voisin a un poisson			                  */
/**********************************************************************/

int get_requins_voisins(const t_ocean ocean, int px, int py, t_liste_requins* liste_requins) {
	int dir = alea(HAUT, HAUT_G),	// Direction aleatoire a verifier
		dx = px,					// Case a verifier en x
		dy = py,					// Case a verifier en y
		num_requin;


	// Boucle qui verifie chaque direction possible
	for (dir = HAUT; dir <= HAUT_G; dir++) {
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
			ajout_energie(&liste_requins->liste[num_requin], JRS_DIGESTION);
			return MORT;	// On retourne que le poisson est mort
		}
	}
	return VIVANT;	// On retourne que le poisson est vivant
}

/************************* TRAITER POISSONS ***************************/
/* traitement des poissons vivants deplaement et naissance            */
/**********************************************************************/

void traiter_poissons(t_liste_poissons* l_poissons, t_ocean* ocean,
	int nb_poissons, int pub_poisson, int p) {

	// Pour chaque poisson restant
	for (p = 0; p < nb_poissons; p++) {
		// On verifie si le poisson a atteint la puberte
		pub_poisson = puberte_atteinte(&l_poissons->liste[p], NB_JRS_PUB_POISSON,
			NB_JRS_GEST_POISSON);

		// Si le poisson a atteint la puberte
		if (pub_poisson == PUBERE) {
			ajout_bebe_poisson(l_poissons, ocean, p);	// On ajoute un bebe poisson

			// On reinitialise le nombre de jours de gestation a -1 puisqu'il vient de 
			// procreer et on va l'augmenter de +1 par la suite. Le nombre de jours doit 
			// donc etre a 0.
			// reset_gestation(&l_poissons.liste[p], -1);
			dec_energie(&l_poissons->liste[p]);
		}

		// Sinon on le deplace
		else deplacer_poisson(ocean, &l_poissons->liste[p], p);

		// On augmente son age et son nombre de jours de gestation si possible
		inc_age(&l_poissons->liste[p], NB_JRS_PUB_POISSON);
	}
}

/********************** TRAITER POISSONS MORTS ************************/
/* gestion de la mort des poissons					                  */
/**********************************************************************/

void traiter_poissons_morts(t_liste_poissons* l_poissons, t_liste_requins* l_requins,
	t_ocean* ocean, int* nb_poissons, int p, int px_poisson,
	int py_poisson, int statut_poisson) {

	// Pour chaque poisson de la liste de poissons
	for (p = 0; p < *nb_poissons; p++) {
		// Obtention de la position du poisson
		get_position(&l_poissons->liste[p], &px_poisson, &py_poisson);
		// Verifie si un requin peut le manger
		statut_poisson = get_requins_voisins(*ocean, px_poisson,
			py_poisson, l_requins);

		// Verifie si le poisson est mort de vieillesse si pas mange
		if (!statut_poisson) {
			statut_poisson = est_mort(&l_poissons->liste[p], MAX_AGE_POISSON);
		}

		// Si le poisson est mort, on l'elimine
		if (statut_poisson == MORT) {
			eliminer_poisson(l_poissons, ocean, p);
			*nb_poissons = get_nb_poissons(*l_poissons);
			p--;
		}
	}
}

/************************** TRAITER REQUINS ***************************/
/* traitement des requins vivants deplaement et naissance             */
/**********************************************************************/

void traiter_requins(t_liste_requins* l_requins, t_ocean* ocean, int nb_requins, int pub_requin, int r) {
	// Pour chaque requin restant
	for (r = 0; r < nb_requins; r++) {
		// On verifie si le requin a atteint la puberte
		pub_requin = puberte_atteinte(&l_requins->liste[r], NB_JRS_PUB_REQUIN,
			NB_JRS_GEST_REQUIN);

		// Si le requin a atteint la puberte
		if (pub_requin == PUBERE) {
			ajout_bebe_requin(l_requins, ocean, r);	// On ajoute un bebe requin

			// On reinitialise le nombre de jours de gestation a -1 puisqu'il vient de 
			// procreer et on va l'augmenter de +1 par la suite. Le nombre de jours doit 
			// donc etre a 0.
			// reset_gestation(&l_requins.liste[r], -1);
		}

		// Sinon on le deplace
		else deplacer_requins(ocean, &l_requins->liste[r], r);

		// On augmente son age et son nombre de jours de gestation si possible
		inc_age(&l_requins->liste[r], NB_JRS_PUB_REQUIN);
		// On decremente son niveau d'energie
		dec_energie(&l_requins->liste[r]);
	}
}

/*********************** TRAITER REQUINS MORTS ************************/
/* gestion de la mort des requins					                  */
/**********************************************************************/

void traiter_requins_morts(t_liste_requins* l_requins, t_ocean* ocean,
	int* nb_requins, int r, int px_requin, int py_requin, int statut_requin) {

	// Pour chaque requin de la liste de requins
	for (r = 0; r < *nb_requins; r++) {
		// Obtention de la position du requin
		get_position(&l_requins->liste[r], &px_requin, &py_requin);
		// Verifie si le poisson est mort de vieillesse ou de faim
		statut_requin = est_mort(&l_requins->liste[r], MAX_AGE_REQUIN);

		// Si le requin est mort, on l'elimine
		if (statut_requin == MORT) {
			eliminer_requin(l_requins, ocean, r);
			*nb_requins = get_nb_requins(*l_requins);
			r--;
		}
	}
}