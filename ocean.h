/******************************************************************************/
/*  OCEAN.H                                                                   */         
/*  Module qui permet la gestion des poissons et des requins dans l'ocean     */
/*  Conception : Jean-Christophe Latreille                                    */
/******************************************************************************/
#include "util.h"

#define HAUTEUR 25
#define LARGEUR 110
#define RIEN -1

/* Type énuméré pour les 8 directions de déplacement */
typedef enum { HAUT, HAUT_DR, DROITE, BAS_DR, BAS, BAS_G, GAUCHE, HAUT_G } t_dir;

/* Type énuméré pour le contenu d'une case */
typedef enum { VIDE, POISSON, REQUIN } t_contenu;

/* Type structure pour le contenu d'une case de la grille */
typedef struct {
	t_contenu contenu;	//Soit: VIDE, POISSON ou REQUIN
	int numero;			//le numéro du poisson/requin à cet endroit, sinon -1
} t_case;

/* Type-tableau de la grille de la mer */
typedef t_case t_ocean[HAUTEUR][LARGEUR];

/******************************************************************************/
/*                    DÉCLARATIONS DE FONCTIONS                               */
/******************************************************************************/

// Recoit l'ocean et met toutes ses cases a {VIDE, RIEN}
void vider_ocean(t_ocean *ocean);

// Recoit une position dans l'ocean et retourne son contenu
t_contenu get_contenu(const t_ocean ocean, int px, int py);

// Recoit une position d'un animal dans l'ocean et retourne son numero
int get_numero(const t_ocean ocean, int px, int py);

// Recoit une position dans l'ocean et ajoute un nouveau contenu/numero a cet endroit
void set_contenu(t_ocean *ocean, int px, int py, t_case nouv_case);

// Recoit une position dans l'ocean et met son contenu a {VIDE, RIEN}
void effacer_case(t_ocean *ocean, int px, int py);

// Recoit une poisition dans l'ocean et retourne le nombre de cases voisines qui sont libres
int get_cases_libres(const t_ocean ocean, int px, int py);

// Recoit une position dans l'ocean et retourne une case voisine libre aleatoire
void get_case_voisine_alea(const t_ocean ocean, int px, int py, int *rx, int *ry);

// Recoit l'ocean et affiche son contenu a l'ecran
void afficher_ocean(const t_ocean ocean);

