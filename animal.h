/******************************************************************************/
/*  ANIMAL.H                                                                  */
/*  Module utilitaire qui permet de gérer un animal générique "t_animal".     */
/*  Conception : Eric Thé                                                     */
/******************************************************************************/
#if !defined (LIB_ANIMAL)
#define LIB_ANIMAL 1

#define MORT 1				// Valeur pour un animal mort
#define VIVANT 0			// Valeur pour un animal vivant

#define PUBERE 1		// Valeur pour la puberte atteinte
#define PRE_PUBERE 0		// Valeur pour la puberte non-atteinte

/* Type-structure pour un animal */
typedef struct {
	int   posx, posy;     //sa position
	int   age;            //son age (en jours)
	int   energie_sante;  //le niveau d'énergie
	int   jrs_gest;       //nombre de jours en gestation
} t_animal;


/******************************************************************************/
/*                    DÉCLARATIONS DE FONCTIONS                               */
/******************************************************************************/

/* Reçoit un animal et ses valeurs initiales, va initialiser l'animal reçu.   */
void init_animal(t_animal* animal, int px, int py, int age, int energie, int gest);

/* Reçoit un animal et retourne sa position via [*px, *py]. */
void get_position(const t_animal* animal, int* px, int* py);

/* Reçoit un animal et une position et va donner cette position à l'animal.   */
void set_position(t_animal* animal, int px, int py);

/* Reçoit un animal et retourne 1 si le poisson a attient l'age de
   puberté ET a terminé sa période de gestation (donc, il va procréer),
   retourne 0 sinon. */
int  puberte_atteinte(const t_animal* animal, int puberte, int gestation);

/* Reçoit un animal et va incrémenter son age ainsi que le nombre de jours
   en gestation de +1 jour si il est assez vieux pour procréer. */
void inc_age(t_animal* animal, int age_puberte);

/* Reçoit un animal et va réinitialiser les jours de gestation à "val".  */
void reset_gestation(t_animal* animal, int val);

/* Reçoit un animal et va incrémenter son niveau d'énergie de la valeur reçue. */
void ajout_energie(t_animal* animal, int energie);

/* Reçoit un animal et va décrémenter son niveau d'énergie de -1.  */
void dec_energie(t_animal* animal);

/* Reçoit un animal et va retourner son niveau d'énergie.  */
int  get_energie(t_animal* animal);

/* Retourne 1 si l'animal reçu vient de mourir de faim (plus d'énergie)
   OU si il a atteint son âge maximal (age_max). On retourne 0 sinon.  */
int  est_mort(const t_animal* animal, int age_max);

#endif