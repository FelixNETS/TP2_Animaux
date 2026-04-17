/**********************************************************************/
/* POISSON.H                                                          */
/* Module de gestion du cycle de vie des poissons					  */
/* Conception : F�lix Nadeau				                          */
/**********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "animal.h"
#include "ocean.h"

/**********************************************************************/
/*                             CONSTANTES                             */
/**********************************************************************/

#define MAX_AGE_POISSON		 60		//l��ge maximal d�un poisson  
#define NB_JRS_PUB_POISSON	 10		//nombre de jours avant la pubert� 
#define NB_JRS_GEST_POISSON	  5		//nombre de jours de gestation 
#define ENERGIE_INIT_POISSON  3		//valeur initiale d'�nergie d�un b�b�-poisson 

/**********************************************************************/
/*							   STRUCTURES                             */
/**********************************************************************/

/* Type-structure pour la liste des poissons */
typedef struct {
	t_animal* liste;
	int nb_poissons;
	int taille_liste;
} t_liste_poissons;

/**********************************************************************/
/*							    FONCTIONS                             */
/**********************************************************************/

/************************* CREER LISTE POISSON ************************/
/*	Fonction generation des poissons								  */
/*	PARAMS: struct liste poissons, qte poissons a generer, tab ocean  */
/**********************************************************************/

void creer_liste_poissons(t_liste_poissons* liste_poissons,
	int nb, t_ocean ocean, int max);

/************************* VIDER LISTE POISSON ************************/
/*	Fonction vider la liste des poissons							  */
/*	PARAMS: struct liste poissons									  */
/**********************************************************************/

void vider_liste_poissons(t_liste_poissons* liste_poissons);

/*************************** GET NB POISSONS **************************/
/*	Fonction qui retourne le nombre de poissons dans la liste		  */
/*	PARAMS : struct liste poissons						     		  */
/**********************************************************************/

int get_nb_poissons(t_liste_poissons liste_poissons);

/************************* DEPLACER POISSONS **************************/
/*	Fonction qui d�place un poisson d'un case voisine				  */
/*	PARAMS: struct tableau ocean, struct liste poissons, # du poisson */
/**********************************************************************/

void deplacer_poisson(t_ocean* ocean, t_animal* poisson, int i);

/**************************** GET POISSON *****************************/
/*	Fonction qui retourne les stats d'un poisson choisi				  */
/*	PARAMS: struct liste poissons, int # du poisson choisi			  */
/**********************************************************************/

static t_animal get_poisson(t_liste_poissons liste_poissons, int i);

/**************************** SET POISSON *****************************/
/*	Fonction qui perment de set les stats d'un poisson choisi		  */
/*	PARAMS: poisson � modif, stats (age, energie, gestation, pos)	  */
/*	Inscrire -1 dans les champs qui ne sont pas a modifier			  */
/**********************************************************************/

void set_poisson(t_animal* poisson, int age, int energie,
	int gest, int posx, int posy);

/************************** ELIMINIER POISSON *************************/
/*	Fonction permet elimination d'un poisson choisi de la lise		  */
/*	PARAMS: liste des poissons, grille ocean, # du poisson			  */
/**********************************************************************/

void eliminer_poisson(t_liste_poissons* liste_poissons,
	t_ocean* ocean, int i);

/************************* AJOUT BEBE POISSON *************************/
/*	Fonction fait naître un nouveau poisson et l'ajoute a la liste	  */
/*	PARAMS: liste des poissons, grille ocean, # du poisson parent     */
/*	RETOUR: 1 si la naissance a reussi, 0 sinon (pas de place,        */
/*	        fausse couche ou population maximale atteinte)             */
/**********************************************************************/

int ajout_bebe_poisson(t_liste_poissons* liste_poissons,
	t_ocean* ocean, int i);

/*********************** LIBERER LISTE POISSONS ***********************/
/*	Fonction qui libere la memoire allouee a la liste				  */
/*	PARAMS: liste des poissons										  */
/**********************************************************************/

void liberer_liste_poissons(t_liste_poissons* liste_poissons);