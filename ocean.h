/******************************************************************************/
/*  OCEAN.H                                                                   */
/*  Module qui permet la gestion des poissons et des requins dans l'ocean     */
/*  Conception : Jean-Christophe Latreille                                    */
/******************************************************************************/
#pragma once

#include "util.h"

#define HAUTEUR 25
#define LARGEUR 110
#define RIEN -1

/* Type �num�r� pour les 8 directions de d�placement */
typedef enum { HAUT, HAUT_DR, DROITE, BAS_DR, BAS, BAS_G, GAUCHE, HAUT_G } t_dir;

/* Type �num�r� pour le contenu d'une case */
typedef enum { VIDE, POISSON, REQUIN } t_contenu;

/* Type structure pour le contenu d'une case de la grille */
typedef struct {
	t_contenu contenu;	//Soit: VIDE, POISSON ou REQUIN
	int numero;			//le num�ro du poisson/requin � cet endroit, sinon -1
} t_case;

/* Type-tableau de la grille de la mer */
typedef t_case t_ocean[HAUTEUR][LARGEUR];

/******************************************************************************/
/*                    D�CLARATIONS DE FONCTIONS                               */
/******************************************************************************/

// Recoit l'ocean et met toutes ses cases a {VIDE, RIEN}
// PARAM: ocean - pointeur vers la grille de l'ocean a vider
void vider_ocean(t_ocean* ocean);

// Recoit une position dans l'ocean et retourne son contenu
// PARAM: ocean - grille de l'ocean (lecture seule); px, py - coordonnees de la case a lire
// RETOUR: le contenu de la case (VIDE, POISSON ou REQUIN)
t_contenu get_contenu(const t_ocean ocean, int px, int py);

// Recoit une position d'un animal dans l'ocean et retourne son numero
// PARAM: ocean - grille de l'ocean (lecture seule); px, py - coordonnees de la case a lire
// RETOUR: le numero de l'animal present a cette case, ou RIEN (-1) si la case est vide
int get_numero(const t_ocean ocean, int px, int py);

// Recoit une position dans l'ocean et ajoute un nouveau contenu/numero a cet endroit
// PARAM: ocean - pointeur vers la grille de l'ocean; px, py - coordonnees de la case a modifier
//        nouv_case - structure t_case contenant le nouveau contenu et le numero a assigner
void set_contenu(t_ocean* ocean, int px, int py, t_case nouv_case);

// Recoit une position dans l'ocean et met son contenu a {VIDE, RIEN}
// PARAM: ocean - pointeur vers la grille de l'ocean; px, py - coordonnees de la case a effacer
void effacer_case(t_ocean* ocean, int px, int py);

// Recoit une poisition dans l'ocean et retourne le nombre de cases voisines qui sont libres
// PARAM: ocean - grille de l'ocean (lecture seule); px, py - coordonnees de la case a verifier
// RETOUR: le nombre de cases voisines libres (valeur entre 0 et 8)
int get_cases_libres(const t_ocean ocean, int px, int py);

// Recoit une position dans l'ocean et retourne une case voisine libre aleatoire
// PARAM: ocean - grille de l'ocean (lecture seule); px, py - coordonnees de la case de depart
//        rx, ry - pointeurs dans lesquels sont stockees les coordonnees de la case voisine libre trouvee
void get_case_voisine_alea(const t_ocean ocean, int px, int py, int* rx, int* ry);

// Recoit l'ocean et affiche son contenu a l'ecran
// PARAM: ocean - grille de l'ocean (lecture seule)
void afficher_ocean(const t_ocean ocean);

