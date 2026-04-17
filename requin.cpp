/**********************************************************************/
/* requin.CPP                                                        */
/* Conception : Félix Nadeau				                          */
/**********************************************************************/
#include "requin.h"

/****************************** VERIF POS *****************************/
/*	Fonction pour assurer la creation des requins dans une case vide  */
/*	PARAMS: struct liste requins, nb de requins, posx, posy			  */
/**********************************************************************/

int verif_pos_requin(t_liste_requins liste_requins,
	int nb_requins, int x, int y) {

	/* si le requin est genere au memes coordonnees qu'un requin */
	/* existant, on retourne 0 pour indiquer un echec			 */

	for (int i = 0; i <= nb_requins; i++) {

		if ((x == liste_requins.liste[i].posx) &&
			(y == liste_requins.liste[i].posy))
			return 0;
	}

	return 1;		// retourne succes si la posisiton est vacante
}

/**************************** INIT_REQUIN *****************************/
/*	Fonction initialisation aleatoire des stats des requins generes   */
/*	PARAMS: struct liste requins, int # du requin					  */
/**********************************************************************/

static t_animal init_requin(t_liste_requins liste_requins,
	int nb_requins) {

	int temp_x, temp_y, temp_age, energie, gest;	// storage stats temp pour validation
	t_animal requin = { };					// requin buffer pour add a la liste si ok

	do {
		temp_x = alea(0, LARGEUR - 1);		// assigne pos x alea dans ocean
		temp_y = alea(0, HAUTEUR - 1);		// assigne pos y alea dans ocean

		/* TANT QUE la position assignee n'est pas vide */
	} while (!verif_pos_requin(liste_requins, nb_requins, temp_x, temp_y));

	temp_age = alea(0, MAX_AGE_REQUIN);	// assigne age alea au requin

	energie = alea(JRS_DIGESTION, JRS_DIGESTION * 4);	// assigne dig alea

	if (temp_age >= NB_JRS_PUB_REQUIN) gest = alea(1, NB_JRS_GEST_REQUIN);
	else gest = 0;

	init_animal(&requin, temp_x, temp_y, temp_age,
		energie, gest);			// les stats sont ajout. au requin buffer

	return requin;				// retour du requin buffer
}

/************************* CREER LISTE REQUIN *************************/
/*	Fonction generation des requins									  */
/*	PARAMS: struct liste requins, qte requins a generer, tab ocean    */
/**********************************************************************/

void creer_liste_requins(t_liste_requins* liste_requins,
	int nb, t_ocean ocean, int max) {

	t_animal requin = { 0 };		// requin buffer pour ajouter a la liste

	liste_requins->taille_liste = max;		// alloc memoire max requise
	liste_requins->liste = (t_animal*)malloc(max * sizeof(t_animal));

	/* ajout requin a la liste initiale "nb" fois */

	for (int i = 0; i < nb; i++) {

		requin = init_requin(*liste_requins, nb);	// init, requin buffer

		liste_requins->liste[i] = requin;	// ajout du buffer a la fin de la liste

		/* ajout du requin dans l'ocean AVEC SON NUMERO dans sa case */
		ocean[requin.posy][requin.posx].contenu = REQUIN;
		ocean[requin.posy][requin.posx].numero = i;

		liste_requins->nb_requins++;	// incremente qte de requins
	}
}

/************************* VIDER LISTE REQUINS ************************/
/*	Fonction vider la liste des requins								  */
/*	PARAMS: struct liste requins									  */
/**********************************************************************/

void vider_liste_requins(t_liste_requins* liste_requins) {

	liste_requins->nb_requins = 0;	// set qte de requins a 0
}

/*************************** GET NB REQUINS ***************************/
/*	Fonction qui retourne le nombre de requins dans la liste		  */
/*	PARAMS : struct liste requins						     		  */
/**********************************************************************/

int get_nb_requins(t_liste_requins liste_requins) {

	return liste_requins.nb_requins;	// retourne la qte de requins
}

/************************* DEPLACER REQUINS ***************************/
/*	Fonction qui déplace un requin d'un case voisine				  */
/*	PARAMS: struct tableau ocean, struct liste requins, # du requin   */
/**********************************************************************/

void deplacer_requins(t_ocean* ocean, t_animal* requin, int i) {

	t_case case_requin;			  // case requin a ajouter a l'ocean
	case_requin.contenu = REQUIN; // assigne val requin (1) a la case
	case_requin.numero = i;		  // assigne id du requin a la case

	int temp_x = requin->posx,		// buffer pos x prend pos x du requin	
		temp_y = requin->posy;		// buffer pos y prend pos y du requin	

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
		set_contenu(ocean, temp_x, temp_y, case_requin);

		requin->posx = temp_x;		// set nouvelle pos x du requin
		requin->posy = temp_y;		// set nouvelle pos y du requin
	}
}

/**************************** GET requin ******************************/
/*	Fonction qui retourne les stats d'un requin choisi				  */
/*	PARAMS: struct liste requins, int # du requin choisi			  */
/**********************************************************************/

static t_animal get_requin(t_liste_requins liste_requins, int i) {

	return liste_requins.liste[i];	// retourne le requin demande 
}

/**************************** SET REQUIN ******************************/
/*	Fonction qui perment de set les stats d'un requin choisi		  */
/*	PARAMS: requin à modif, stats (age, energie, gestation, pos)	  */
/*	Inscrire -1 dans les champs qui ne sont pas a modifier			  */
/**********************************************************************/

void set_requin(t_animal* requin, int age, int energie,
	int gest, int posx, int posy) {

	/* set les stats d'un requin a la valeur demandee. peut choisir */
	/* ne pas modifier certaines valeurs en entrant un nb negatif   */

	if (age >= 0 && age < MAX_AGE_REQUIN) requin->age = age;
	if (energie >= 0) requin->energie_sante = energie;
	if (gest >= 0) requin->jrs_gest = gest;
	if (posx >= 0) requin->posx = posx;
	if (posy >= 0) requin->posy = posy;
}

/************************** ELIMINIER REQUIN **************************/
/*	Fonction permet elimination d'un requin choisi de la lise		  */
/*	PARAMS: liste des requins, grille ocean, # du requin			  */
/**********************************************************************/

void eliminer_requin(t_liste_requins* liste_requins,
	t_ocean* ocean, int i) {

	t_case case_requin;			  // case requin a ajouter a l'ocean
	case_requin.contenu = REQUIN; // assigne val requin (1) a la case
	case_requin.numero = i;		  // assigne id du requin a la case

	int dernier = liste_requins->nb_requins - 1;	// dern requin de la liste

	int ix = liste_requins->liste[i].posx,			// pos x du requin choisi
		iy = liste_requins->liste[i].posy,			// pos y du requin choisi
		dx = liste_requins->liste[dernier].posx,	// pos x du dernier requin
		dy = liste_requins->liste[dernier].posy;	// pos y du dernier requin

	/* le requin doit etre dans la range des requins existants */
	if (i <= dernier) {

		/* si le requin n'est pas le dernier */
		if (i < dernier) {

			/* on le remplace par le dernier et on met le dernier a */
			/* la place du requin choisi dans l'ocean              */
			liste_requins->liste[i] = liste_requins->liste[dernier];
			set_contenu(ocean, dx, dy, case_requin);
		}

		effacer_case(ocean, ix, iy);	// vide la case du requin choisi

		liste_requins->nb_requins--;	// decr la qte de requins dand la liste
	}
}

/************************* AJOUT BEBE REQUIN **************************/
/*	Fonction fait naître un nouveau requin et l'ajoute a la liste	  */
/*	PARAMS:															  */
/**********************************************************************/

int ajout_bebe_requin(t_liste_requins* liste_requins,
	t_ocean* ocean, int i) {

	t_animal parent = liste_requins->liste[i];	// buffer requin parent

	/* case a ajouter */
	t_case case_requin;
	case_requin.contenu = REQUIN;
	case_requin.numero = liste_requins->nb_requins;

	/* buffers de position du parent et du bebe */
	int parentx = parent.posx,
		parenty = parent.posy,
		bebex, bebey,

		cases_libres = get_cases_libres(*ocean, parentx, parenty),

		j = liste_requins->nb_requins;

	/* si le bebe n'a pas de place pour etre ne, il ne nait pas (ret 0)*/
	if (!cases_libres) return 0;

	/* si le parent fait une fausse couche ou que la population est capped */
	/* le bebe ne nait pas (ret 0) et le nb jrs gest du requin est reset  */
	if (j >= liste_requins->taille_liste) {

		reset_gestation(&parent, -NB_JRS_GEST_REQUIN);
		liste_requins->liste[i] = parent;
		return 0;
	}

	liste_requins->nb_requins++;		// incr la qte de requins

	/* determine lieu de naissance du requin */
	get_case_voisine_alea(*ocean, parentx, parenty, &bebex, &bebey);

	liste_requins->liste[j].posx = bebex;	// assigne le x a la vraie position
	liste_requins->liste[j].posy = bebey;  // assigne le y a la vraie position

	/* set energie du bebe a energie init et son age et jours gest a 0 */
	set_requin(&liste_requins->liste[j], 0, 3 * JRS_DIGESTION,
		0, -1, -1);

	set_contenu(ocean, bebex, bebey, case_requin);

	reset_gestation(&parent, -NB_JRS_GEST_REQUIN);	// reset jrs gest du parent
	liste_requins->liste[i] = parent;

	return 1;	// retourne 1 pour indiquer accouchement succes
}

/*********************** LIBERER LISTE REQUINS ************************/
/*	Fonction qui libere la memoire allouee a la liste				  */
/*	PARAMS: liste des requins										  */
/**********************************************************************/

void liberer_liste_requin(t_liste_requins* liste_requins) {

	free(liste_requins->liste);			// libere memoire

	liste_requins->liste = NULL;		// reset pointeur

	liste_requins->taille_liste = 0;	// reset taille de liste
}