/**********************************************************************/
/* ANIMAL.CPP                                                         */
/* Conception : Jean-Christophe Latreille                             */
/**********************************************************************/
#include"animal.h"
#include<stdlib.h>

/************************** INIT_ANIMAL *******************************/
/* Initialisation d'un animal                                         */
/* PARAM: animal - pointeur vers l'animal a initialiser               */
/*        px, py - position initiale en x et en y dans l'ocean        */
/*        age - age initial de l'animal                               */
/*        energie - niveau d'energie/sante initial                    */
/*        gest - nombre de jours de gestation initial                 */
/**********************************************************************/

void init_animal(t_animal* animal, int px, int py, int age, int energie, int gest) {
	if (animal == NULL)		// Verification de la validite du pointeur
		return;

	// Assignation de la position de l'animal
	animal->posx = px;
	animal->posy = py;

	// Assignation de l'age de l'animal
	animal->age = age;

	// Assignation du niveau d'energie de l'animal
	animal->energie_sante = energie;

	// Assignation du nombre de jours de gestation de l'animal
	animal->jrs_gest = gest;
}

/************************** GET_POSITION ******************************/
/* Obtention de la position d'un animal                               */
/* PARAM: animal - pointeur vers l'animal dont on veut la position    */
/*        px, py - pointeurs dans lesquels seront stockees la pos. x  */
/*                 et la pos. y de l'animal                           */
/**********************************************************************/

void get_position(const t_animal* animal, int* px, int* py) {
	*px = animal->posx;	// Obtention de la position en x
	*py = animal->posy;	// Obtention de la position en y
}

/************************** SET_POSITION ******************************/
/* Assignation d'une position a un animal                             */
/* PARAM: animal - pointeur vers l'animal a repositionner             */
/*        px, py - nouvelle position en x et en y dans l'ocean        */
/**********************************************************************/

void set_position(t_animal* animal, int px, int py) {
	animal->posx = px;	// Assignation de la nouvelle position en x
	animal->posy = py;	// Assignation de la nouvelle position en y
}

/************************ PUBERTE_ATTEINTE ****************************/
/* Verification de la capacite d'un animal a se reproduire            */
/* PARAM: animal - pointeur vers l'animal a verifier (lecture seule)  */
/*        puberte - age minimal requis pour la reproduction            */
/*        gestation - nombre de jours de gestation requis             */
/* RETOUR: PUBERE (1) si les deux conditions sont atteintes,          */
/*         PRE_PUBERE (0) sinon                                        */
/**********************************************************************/

int  puberte_atteinte(const t_animal* animal, int puberte, int gestation) {
	// Si la puberte l'age de puberte est atteinte et que la periode de
	// gestation est completee, retourne 1
	if (animal->age >= puberte && animal->jrs_gest >= gestation) return PUBERE;

	// Si les deux conditions ne sont pas atteintes, retourne 0
	else return PRE_PUBERE;
}

/***************************** INC_AGE ********************************/
/* Incrementation de l'age d'un animal et de sa periode de gestation  */
/* PARAM: animal - pointeur vers l'animal a vieillir                  */
/*        age_puberte - age a partir duquel le compteur de gestation   */
/*                      commence a etre incremente                     */
/**********************************************************************/

void inc_age(t_animal* animal, int age_puberte) {
	animal->age++;	// Incrementation de l'age de l'animal de 1

	// Si l'animal a atteint la puberte, incremente sa periode de gestation de 1
	if (animal->age >= age_puberte) animal->jrs_gest++;
}

/************************* RESET_GESTATION ****************************/
/* Reinitialisation du nombres de jours de gestation d'un animal      */
/* PARAM: animal - pointeur vers l'animal dont on reinitialise la     */
/*                 gestation                                           */
/*        val - valeur a assigner au compteur de jours de gestation   */
/**********************************************************************/

void reset_gestation(t_animal* animal, int val) {
	animal->jrs_gest = val;	// Reinitialise la periode de gestation d'un animal
}

/************************** AJOUT_ENERGIE *****************************/
/* Incrementation du niveau d'energie d'un animal                     */
/* PARAM: animal - pointeur vers l'animal dont on augmente l'energie  */
/*        energie - valeur a ajouter au niveau d'energie              */
/**********************************************************************/

void ajout_energie(t_animal* animal, int energie) {
	animal->energie_sante += energie;	// Incrementation du niveau d'energie de l'animal
}

/**************************** DEC_ENERGIE *****************************/
/* Decrementation du niveau d'energie d'un animal de 1                */
/* PARAM: animal - pointeur vers l'animal dont on diminue l'energie   */
/**********************************************************************/

void dec_energie(t_animal* animal) {
	animal->energie_sante--;	// Decrementation du niveau d'energie de l'animal de 1
}

/*************************** GET_ENERGIE ******************************/
/* Obtention du niveau d'energie d'un animal                          */
/* PARAM: animal - pointeur vers l'animal dont on lit l'energie       */
/* RETOUR: la valeur du niveau d'energie/sante de l'animal            */
/**********************************************************************/

int  get_energie(t_animal* animal) {
	return animal->energie_sante;	// Obtention du niveau d'energie de l'animal
}

/***************************** EST_MORT *******************************/
/* Obtention du statut d'un animal (mort/vivant)                      */
/* PARAM: animal - pointeur vers l'animal a verifier (lecture seule)  */
/*        age_max - age maximal de vie de l'espece de l'animal        */
/* RETOUR: MORT (1) si l'energie est <= 0 ou l'age max est atteint,   */
/*         VIVANT (0) sinon                                            */
/**********************************************************************/

int  est_mort(const t_animal* animal, int age_max) {
	// Si l'animal n'a plus d'energie ou qu'il a atteint sa fin de vie, retourne 1 (mort)
	if (animal->energie_sante <= 0 || animal->age == age_max) return MORT;

	// Si aucune condition n'est atteinte, retourne 0 (vivant)
	else return VIVANT;
}
