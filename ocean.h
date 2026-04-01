/******************************************************************************/
/*  OCEAN.H                                                                   */         
/*  Module qui permet la gestion des poissons et des requins dans l'ocean     */
/*  Conception : Jean-Christophe Latreille                                                     */
/******************************************************************************/
#define HAUTEUR 25
#define LARGEUR 110
#define RIEN -1

/* Type énuméré pour les 8 directions de déplacement */
typedef enum { HAUT, HAUT_DR, DROITE, BAS_DR, BAS, BAS_G, GAUCHE, HAUT_G } t_dir;

/* Type énuméré pour le contenu d'une case */
typedef enum { VIDE, POISSON, REQUIN } t_contenu;

/* Type structure pour le contenu d'une case de la grille */
typedef struct {
	t_contenu contenu; int numero; //Soit: VIDE, POISSON ou REQUIN
	//le numéro du poisson/requin à cet endroit, sinon -1
} t_case;

/* Type-tableau de la grille de la mer */
typedef t_case t_ocean[HAUTEUR][LARGEUR];

/******************************************************************************/
/*                    DÉCLARATIONS DE FONCTIONS                               */
/******************************************************************************/