/**********************************************************************/
/* REQUIN.H                                                           */
/* Module de gestion du cycle de vie des requins					  */
/* Conception : Félix Nadeau				                          */
/**********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "animal.h"
#include "ocean.h"

/**********************************************************************/
/*                             CONSTANTES                             */
/**********************************************************************/

#define MAX_AGE_REQUIN	   1500		//l’âge maximal d’un requin  
#define NB_JRS_PUB_REQUIN	 90		//nombre de jours avant la puberté 
#define NB_JRS_GEST_REQUIN	 21		//nombre de jours de gestation 
#define JRS_DIGESTION         5		//valeur ajoutée à l'indice d’énergie après un repas  

/**********************************************************************/
/*							   STRUCTURES                             */
/**********************************************************************/

/* Type-structure pour la liste des requins */
typedef struct {
	t_animal* liste;
	int nb_requins;
	int taille_liste;
} t_liste_requins;

/**********************************************************************/
/*							    FONCTIONS                             */
/**********************************************************************/

/************************* CREER LISTE REQUIN *************************/
/*	Fonction generation des requins								  */
/*	PARAMS: struct liste requins, qte requins a generer, tab ocean  */
/**********************************************************************/

void creer_liste_requins(t_liste_requins* liste_requins,
	int nb, t_ocean ocean);

/************************* VIDER LISTE REQUIN *************************/
/*	Fonction vider la liste des requins							  */
/*	PARAMS: struct liste requins									  */
/**********************************************************************/

void vider_liste_requins(t_liste_requins* liste_requins);

/*************************** GET NB requinS **************************/
/*	Fonction qui retourne le nombre de requins dans la liste		  */
/*	PARAMS : struct liste requins						     		  */
/**********************************************************************/

int get_nb_requins(t_liste_requins liste_requins);

/************************* DEPLACER requinS **************************/
/*	Fonction qui déplace un requin d'un case voisine				  */
/*	PARAMS: struct tableau ocean, struct liste requins, # du REQUIN **/
/**********************************************************************/

void deplacer_requins(t_ocean* ocean, t_animal* requin, int i);

/**************************** GET REQUIN ******************************/
/*	Fonction qui retourne les stats d'un requin choisi				  */
/*	PARAMS: struct liste requins, int # du requin choisi			  */
/**********************************************************************/

static t_animal get_requin(t_liste_requins liste_requins, int i);

/**************************** SET REQUIN ******************************/
/*	Fonction qui perment de set les stats d'un requin choisi		  */
/*	PARAMS: requin à modif, stats (age, energie, gestation, pos)	  */
/*	Inscrire -1 dans les champs qui ne sont pas a modifier			  */
/**********************************************************************/

void set_requin(t_animal* requin, int age, int energie,
	int gest, int posx, int posy);

/************************** ELIMINIER REQUIN **************************/
/*	Fonction permet elimination d'un requin choisi de la lise		  */
/*	PARAMS: liste des requins, grille ocean, # du requin			  */
/**********************************************************************/

void eliminer_requin(t_liste_requins* liste_requins, t_ocean* ocean, int i);

/************************* AJOUT BEBE REQUIN **************************/
/*	Fonction fait naître un nouveau requin et l'ajoute a la liste	  */
/*	PARAMS:															  */
/**********************************************************************/

int ajout_bebe_requin(t_liste_requins* liste_requins,
	t_ocean* ocean, int i);

/*********************** LIBERER LISTE REQUINS ************************/
/*	Fonction qui libere la memoire allouee a la liste				  */
/*	PARAMS: liste des requins										  */
/**********************************************************************/

void liberer_liste_requin(t_liste_requins* liste_requins);