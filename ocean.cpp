/**********************************************************************/
/* OCEAN.CPP                                                         */
/* Conception : Jean-Christophe Latreille                             */
/**********************************************************************/
#include"ocean.h"

/**************************** VIDER_OCEAN *****************************/
/* Vide l'ocean de tout son contenu                                   */
/* PARAM: ocean - pointeur vers la grille de l'ocean a vider          */
/**********************************************************************/

void vider_ocean(t_ocean* ocean) {
	int i, j;	// Compteurs pour la boucle "for"

	for (i = 0; i < HAUTEUR; i++) {
		for (j = 0; j < LARGEUR; j++) {
			(*ocean)[i][j] = { VIDE, RIEN };
		}
	}
}

/**************************** GET_CONTENU *****************************/
/* Obtient le contenu d'une case a une position donnee                */
/* PARAM: ocean - grille de l'ocean (lecture seule)                   */
/*        px, py - coordonnees de la case a lire                      */
/* RETOUR: le contenu de la case (VIDE, POISSON ou REQUIN)            */
/**********************************************************************/

t_contenu get_contenu(const t_ocean ocean, int px, int py) {
	return ocean[py][px].contenu;
}

/***************************** GET_NUMERO *****************************/
/* Obtient le numero d'un animal a une position donnee                */
/* PARAM: ocean - grille de l'ocean (lecture seule)                   */
/*        px, py - coordonnees de la case a lire                      */
/* RETOUR: le numero de l'animal present, ou RIEN (-1) si case vide   */
/**********************************************************************/

int get_numero(const t_ocean ocean, int px, int py) {
	return ocean[py][px].numero;
}

/**************************** SET_CONTENU *****************************/
/* Assigne un contenu et un numero a une position donnee              */
/* PARAM: ocean - pointeur vers la grille de l'ocean                  */
/*        px, py - coordonnees de la case a modifier                  */
/*        nouv_case - structure t_case avec le nouveau contenu/numero  */
/**********************************************************************/

void set_contenu(t_ocean* ocean, int px, int py, t_case nouv_case) {
	(*ocean)[py][px] = nouv_case;
}

/*************************** EFFACER_CASE *****************************/
/* Effacer le contenu et le numero d'une position donnee              */
/* PARAM: ocean - pointeur vers la grille de l'ocean                  */
/*        px, py - coordonnees de la case a effacer                   */
/**********************************************************************/

void effacer_case(t_ocean* ocean, int px, int py) {
	(*ocean)[py][px] = { VIDE, RIEN };
}

/************************** GET_CASES_LIBRES **************************/
/* Retourne le nombre de cases vides autour d'une position donnee     */
/* PARAM: ocean - grille de l'ocean (lecture seule)                   */
/*        px, py - coordonnees de la case a verifier                  */
/* RETOUR: le nombre de cases voisines libres (valeur entre 0 et 8)   */
/**********************************************************************/

int get_cases_libres(const t_ocean ocean, int px, int py) {
	int nb_cases = 0,	// Compteur du nombre de cases voisines libres
		dir,			// Compteur de direction pour la boucle "for"
		dx = px,		// Case a verifier en x
		dy = py;		// Case a verifier en y

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

		// Si la case n'est pas a l'extremite de l'ocean (hors-limites)
		if (dy >= 0 && dy < HAUTEUR) {
			// Si le contenu de la case est libre (pas un animal, donc "VIDE")
			if (ocean[dy][dx].contenu == VIDE) nb_cases++;	// Incrementation du compteur
		}


		// Reinitialision de la position a verifier a la position originale
		dx = px;
		dy = py;
	}

	return nb_cases;	// On retourne le nombre de cases libres
}

/*********************** GET_CASE_VOISINE_ALEA ************************/
/* Retourne une case voisine libre aleatoire                          */
/* PARAM: ocean - grille de l'ocean (lecture seule)                   */
/*        px, py - coordonnees de la case de depart                   */
/*        rx, ry - pointeurs dans lesquels sont stockees les          */
/*                 coordonnees de la case voisine libre trouvee        */
/**********************************************************************/

void get_case_voisine_alea(const t_ocean ocean, int px, int py, int* rx, int* ry) {
	int dir = alea(HAUT, HAUT_G),	// Direction aleatoire a verifier
		dx = px,					// Case a verifier en x
		dy = py,					// Case a verifier en y
		est_vide = 0;				// Verificateur de case vide (0: non-vide, 1: vide)


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
		// est libre (pas un animal, donc "VIDE")
		if (dy >= 0 && dy < HAUTEUR

			&& ocean[dy][dx].contenu == VIDE) est_vide = 1;	// On change le verificateur
		if (dy >= 0 && dy < HAUTEUR && ocean[dy][dx].contenu == VIDE) {

			est_vide = 1;	// On change le verificateur
		}

		else {
			dir = alea(HAUT, HAUT_G);	// On essaie une nouvelle direction

			// Reinitialision de la position a verifier a la position originale
			dx = px;
			dy = py;
		}
	}

	// On assigne les positions de la case libre aux pointeurs
	*rx = dx;
	*ry = dy;

}

/*************************** AFFICHER_OCEAN ***************************/
/* Affiche les poissons et les requins dans l'ocean                   */
/* PARAM: ocean - grille de l'ocean (lecture seule)                   */
/**********************************************************************/

void afficher_ocean(const t_ocean ocean) {
	int i, j,		// Compteurs pour la boucle "for"
		contenu;	// Contenu des differentes cases

	for (j = 0; j < HAUTEUR; j++) {

		effacer_ligne(j);

		for (i = 0; i < LARGEUR; i++) {
			contenu = get_contenu(ocean, i, j);

			switch (contenu) {
			case VIDE:
				break;

			case POISSON:
				afficher_char(CH_POISSON, i, j);
				break;

			case REQUIN:
				afficher_char(CH_REQUIN, i, j);
				break;
			}
		}
	}
}