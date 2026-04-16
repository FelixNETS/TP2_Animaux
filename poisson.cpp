/**********************************************************************/
/* POISSON.CPP                                                        */
/* Conception : Félix Nadeau				                          */
/**********************************************************************/
#include "poisson.h"

/****************************** VERIF POS *****************************/
/*	Fonction pour assurer la creation des poissons dans une case vide */
/*	PARAMS: struct liste poissons, nb de poissons, posx, posy		  */
/**********************************************************************/

int verif_pos_poisson(t_liste_poissons liste_poissons,
	int nb_poissons, int x, int y) {

	/* si le poisson est genere au memes coordonnees qu'un poisson */
	/* existant, on retourne 0 pour indiquer un echec			   */

	for (int i = 0; i <= nb_poissons; i++) {

		if ((x == liste_poissons.liste[i].posx) &&
			(y == liste_poissons.liste[i].posy))
			return 0;
	}

	return 1;		// retourne succes si la posisiton est vacante
}

/**************************** INIT_POISSON ****************************/
/*	Fonction initialisation aleatoire des stats des poissons generes  */
/*	PARAMS: struct liste poissons, int # du poisson					  */
/**********************************************************************/

static t_animal init_poisson(t_liste_poissons liste_poissons,
	int nb_poissons) {

	int temp_x, temp_y, temp_age;	// storage stats temporaire pour validation
	t_animal poisson = { };			// poisson buffer pour ajouter a la liste si ok

	do {
		temp_x = alea(0, LARGEUR - 1);		// assigne pos x alea dans ocean
		temp_y = alea(0, HAUTEUR - 1);		// assigne pos y alea dans ocean

		/* TANT QUE la position assignee n'est pas vide */
	} while (!verif_pos_poisson(liste_poissons, nb_poissons, temp_x, temp_y));

	temp_age = alea(0, MAX_AGE_POISSON);	// assigne age alea au poisson

	init_animal(&poisson, temp_x, temp_y, temp_age,
		ENERGIE_INIT_POISSON, 0);			// les stats sont ajout. au poisson buffer

	return poisson;							// retour du poisson buffer
}

/************************* CREER LISTE POISSON ************************/
/*	Fonction generation des poissons								  */
/*	PARAMS: struct liste poissons, qte poissons a generer, tab ocean  */
/**********************************************************************/

void creer_liste_poissons(t_liste_poissons* liste_poissons,
	int nb, t_ocean ocean) {

	t_animal poisson = { 0 };		// poisson buffer pour ajouter a la liste

	liste_poissons->taille_liste = 500;		// TEMPORAIRE***
	liste_poissons->liste = (t_animal*)malloc(500 * sizeof(t_animal));

	/* ajout poisson a la liste initiale "nb" fois */

	for (int i = 0; i < nb; i++) {

		poisson = init_poisson(*liste_poissons, nb);	// init, poisson buffer

		liste_poissons->liste[i] = poisson;	// ajout du buffer a la fin de la liste

		/* ajout du poisson dans l'ocean AVEC SON NUMERO dans sa case */
		ocean[poisson.posy][poisson.posx].contenu = POISSON;
		ocean[poisson.posy][poisson.posx].numero = i;

		liste_poissons->nb_poissons++;	// incremente qte de poissons
	}
}

/************************* VIDER LISTE POISSON ************************/
/*	Fonction vider la liste des poissons							  */
/*	PARAMS: struct liste poissons									  */
/**********************************************************************/

void vider_liste_poissons(t_liste_poissons* liste_poissons) {

	liste_poissons->nb_poissons = 0;	// set qte de poissons a 0
}

/*************************** GET NB POISSONS **************************/
/*	Fonction qui retourne le nombre de poissons dans la liste		  */
/*	PARAMS : struct liste poissons						     		  */
/**********************************************************************/

int get_nb_poissons(t_liste_poissons liste_poissons) {

	return liste_poissons.nb_poissons;	// retourne la qte de poissons
}

/************************* DEPLACER POISSONS **************************/
/*	Fonction qui déplace un poisson d'un case voisine				  */
/*	PARAMS: struct tableau ocean, struct liste poissons, # du poisson */
/**********************************************************************/

void deplacer_poisson(t_ocean* ocean, t_animal* poisson, int i) {

	t_case case_poisson;			// case poisson a ajouter a l'ocean
	case_poisson.contenu = POISSON; // assigne val POISSON (1) a la case
	case_poisson.numero = i;		// assigne id du poisson a la case

	int temp_x = poisson->posx,		// buffer pos x prend pos x du poisson	
		temp_y = poisson->posy;		// buffer pos y prend pos y du poisson	

	/* verif qu'il y a des cases vides adjacentes */
	if (get_cases_libres(*ocean, temp_x, temp_y)) {

		effacer_case(ocean, temp_x, temp_y);	// efface contenu ancienne case

		get_case_voisine_alea(*ocean, temp_x, temp_y,
			&temp_x, &temp_y);		// cherche une case voisine aleatoire

		/* CAS PARTICULIER l'ocean "wrap around" si on depasse la limite */
		/* droite ou gauche on passe directement de l'autre cote         */
		if (temp_x == LARGEUR) temp_x = 0;
		if (temp_x < 0) temp_x = LARGEUR - 1;

		// ajout contenu nouvelle case
		set_contenu(ocean, temp_x, temp_y, case_poisson);

		poisson->posx = temp_x;		// set nouvelle pos x du poisson
		poisson->posy = temp_y;		// set nouvelle pos y du poisson
	}
}

/**************************** GET POISSON *****************************/
/*	Fonction qui retourne les stats d'un poisson choisi				  */
/*	PARAMS: struct liste poissons, int # du poisson choisi			  */
/**********************************************************************/

static t_animal get_poisson(t_liste_poissons liste_poissons, int i) {

	return liste_poissons.liste[i];	// retourne le poisson demande 
}

/**************************** SET POISSON *****************************/
/*	Fonction qui perment de set les stats d'un poisson choisi		  */
/*	PARAMS: poisson à modif, stats (age, energie, gestation, pos)	  */
/*	Inscrire -1 dans les champs qui ne sont pas a modifier			  */
/**********************************************************************/

void set_poisson(t_animal* poisson, int age, int energie,
	int gest, int posx, int posy) {

	/* set les stats d'un poisson a la valeur demandee. peut choisir */
	/* ne pas modifier certaines valeurs en entrant un nb negatif    */

	if (age >= 0 && age < MAX_AGE_POISSON) poisson->age = age;
	if (energie >= 0) poisson->energie_sante = energie;
	if (gest >= 0) poisson->jrs_gest = gest;
	if (posx >= 0) poisson->posx = posx;
	if (posy >= 0) poisson->posy = posy;
}

/************************** ELIMINIER POISSON *************************/
/*	Fonction permet elimination d'un poisson choisi de la lise		  */
/*	PARAMS: liste des poissons, grille ocean, # du poisson			  */
/**********************************************************************/

void eliminer_poisson(t_liste_poissons* liste_poissons,
	t_ocean* ocean, int i) {

	t_case case_poisson;			// case poisson a ajouter a l'ocean
	case_poisson.contenu = POISSON; // assigne val POISSON (1) a la case
	case_poisson.numero = i;		// assigne id du poisson a la case

	int dernier = liste_poissons->nb_poissons - 1;	// dern poisson de la liste

	int ix = liste_poissons->liste[i].posx,			// pos x du poisson choisi
		iy = liste_poissons->liste[i].posy,			// pos y du poisson choisi
		dx = liste_poissons->liste[dernier].posx,	// pos x du dernier poisson
		dy = liste_poissons->liste[dernier].posy;	// pos y du dernier poisson

	/* le poisson doit etre dans la range des poissons existants */
	if (i <= dernier) {

		/* si le poisson n'est pas le dernier */
		if (i < dernier) {

			/* on le remplace par le dernier et on met le dernier a */
			/* la place du poisson choisi dans l'ocean              */
			liste_poissons->liste[i] = liste_poissons->liste[dernier];
			set_contenu(ocean, dx, dy, case_poisson);
		}

		effacer_case(ocean, ix, iy);	// vide la case du poisson choisi

		liste_poissons->nb_poissons--;	// decr la qte de poissons dand la liste
	}
}

/************************* AJOUT BEBE POISSON *************************/
/*	Fonction fait naître un nouveau poisson et l'ajoute a la liste	  */
/*	PARAMS:															  */
/**********************************************************************/

int ajout_bebe_poisson(t_liste_poissons* liste_poissons,
	t_ocean* ocean, int i) {

	t_animal parent = liste_poissons->liste[i];	// buffer poisson parent

	/* case a ajouter */
	t_case case_poisson;
	case_poisson.contenu = POISSON;
	case_poisson.numero = liste_poissons->nb_poissons;

	/* buffers de position du parent et du bebe */
	int parentx = parent.posx,
		parenty = parent.posy,
		bebex, bebey,

		/* generation de probabilite de fausse couche et nb de cases libres */
		fausse_couche = alea(0, 2),
		cases_libres = get_cases_libres(*ocean, parentx, parenty),

		j = liste_poissons->nb_poissons;

	/* si le bebe n'a pas de place pour etre ne, il ne nait pas (ret 0)*/
	if (!cases_libres) return 0;

	/* si le parent fait une fausse couche ou que la population est capped */
	/* le bebe ne nait pas (ret 0) et le nb jrs gest du poisson est reset  */
	if ((!fausse_couche) || (j >= liste_poissons->taille_liste)) {

		reset_gestation(&parent, -NB_JRS_GEST_POISSON);
		liste_poissons->liste[i] = parent;
		return 0;
	}

	liste_poissons->nb_poissons++;		// incr la qte de poissons

	/* determine lieu de naissance du poisson */
	get_case_voisine_alea(*ocean, parentx, parenty, &bebex, &bebey);

	liste_poissons->liste[j].posx = bebex;	// assigne le x a la vraie position
	liste_poissons->liste[j].posy = bebey;  // assigne le y a la vraie position

	/* set energie du bebe a energie init et son age et jours gest a 0 */
	set_poisson(&liste_poissons->liste[j], 0, ENERGIE_INIT_POISSON,
		0, -1, -1);

	reset_gestation(&parent, -NB_JRS_GEST_POISSON);	// reset jrs gest du parent
	liste_poissons->liste[i] = parent;

	return 1;	// retourne 1 pour indiquer accouchement succes
}

/*********************** LIBERER LISTE POISSONS ***********************/
/*	Fonction qui libere la memoire allouee a la liste				  */
/*	PARAMS: liste des requins										  */
/*	PARAMS: liste des poissons										  */
/**********************************************************************/

void liberer_liste_poissons(t_liste_poissons* liste_poissons) {

	free(liste_poissons->liste);		// libere memoire

	liste_poissons->liste = NULL;		// reset pointeur

	liste_poissons->taille_liste = 0;	// reset taille de liste
}