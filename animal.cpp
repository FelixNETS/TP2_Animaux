/**********************************************************************/
/* ANIMAL.CPP                                                         */
/* Conception : Jean-Christophe Latreille                             */
/**********************************************************************/
#include"animal.h"

/************************** INIT_ANIMAL *******************************/
/* Initialisation d'un animal                                         */
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
/**********************************************************************/

void get_position(const t_animal* animal, int* px, int* py) {
	*px = animal->posx;	// Obtention de la position en x
	*py = animal->posy;	// Obtention de la position en y
}

/************************** SET_POSITION ******************************/
/* Assignation d'une position a un animal                             */
/**********************************************************************/

void set_position(t_animal* animal, int px, int py) {
	animal->posx = px;	// Assignation de la nouvelle position en x
	animal->posy = py;	// Assignation de la nouvelle position en y
}

/************************ PUBERTE_ATTEINTE ****************************/
/* Verification de la cpatitude d'un animal a se reproduire           */
/**********************************************************************/

int  puberte_atteinte(const t_animal* animal, int puberte, int gestation) {
	// Si la puberte l'age de puberte est atteinte et que la periode de
	// gestation est completee, retourne 1
	if (animal->age >= puberte && animal->jrs_gest == gestation) return 1;

	// Si les deux conditions ne sont pas atteintes, retourne 0
	else return 0;
}

/***************************** INC_AGE ********************************/
/* Incrementation de l'age d'un animal et de sa periode de gestation  */
/**********************************************************************/

void inc_age(t_animal* animal, int age_puberte) {
	animal->age++;	// Incrementation de l'age de l'animal de 1

	// Si l'animal a atteint la puberte, incremente sa periode de gestation de 1
	if (animal->age >= age_puberte) animal->jrs_gest++;
}

/************************* RESET_GESTATION ****************************/
/* Reinitialisation du nombres de jours de gestation d'un animal      */
/**********************************************************************/

void reset_gestation(t_animal* animal, int val) {
	animal->jrs_gest = val;	// Reinitialise la periode de gestation d'un animal
}

/************************** AJOUT_ENERGIE *****************************/
/* Incrementation du niveau d'energie d'un animal                     */
/**********************************************************************/

void ajout_energie(t_animal* animal, int energie) {
	animal->energie_sante += energie;	// Incrementation du niveau d'energie de l'animal
}

/**************************** DEC_ENERGIE *****************************/
/* Decrementation du niveau d'energie d'un animal                     */
/**********************************************************************/

void dec_energie(t_animal* animal) {
	animal->energie_sante--;	// Decrementation du niveau d'energie de l'animal de 1
}

/*************************** GET_ENERGIE ******************************/
/* Obtentation du niveau d'energie d'un animal                        */
/**********************************************************************/

int  get_energie(t_animal* animal) {
	return animal->energie_sante;	// Obtention du niveau d'energie de l'animal
}

/***************************** EST_MORT *******************************/
/* Obtention du statut d'un animal (mort/vivant)                      */
/**********************************************************************/

int  est_mort(const t_animal* animal, int age_max) {
	// Si l'animal n'a plus d'energie ou qu'il a atteint sa fin de vie, retourne 1 (mort)
	if (animal->energie_sante == 0 || animal->age == age_max) return 1;

	// Si aucune condition n'est atteinte, retourne 0 (vivant)
	else return 0;
}
