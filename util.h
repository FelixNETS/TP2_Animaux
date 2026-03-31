/**********************************************************************/
/* UTIL.H   Librairie de fonctions utilitaires.                       */
/* Contient des fonctions pour la génération de nombres aléatoires et */
/* pour l'affichages des poissons, requins et autres messages.        */
/**********************************************************************/
#if !defined UTIL
#define UTIL 1

#define CH_POISSON 42        //caractère-poisson (un '*')
#define CH_REQUIN  55        //caractère-requin  (un '7')
#define DEBUT_MER   2        //ligne de départ de la zone d'affichage de la mer

/**********************************************************************/
/*                   FONCTIONS DE NOMBRES ALEATOIRES                  */
/**********************************************************************/

void init_alea();
/* Fonction pour initialiser le générateur aléatoire. */

int  alea(int min, int max);
/* Fonction aléatoire qui renvoie un entier inclu entre [min..max]. */


/**********************************************************************/
/*                   FONCTIONS D'AFFICHAGES-CONSOLE                   */
/**********************************************************************/

void afficher_etat(int iter, int nb_poissons, int nb_requins);
/* Reçoit: numéro d'itération, nombre de poissons, nombre de requins.
   Va afficher ces valeurs au haut de la grille de la mer.  */

void message(const char *mess);
/* Affiche un message texte a la 4ieme ligne de la console texte. */

void effacer_ligne(int y);
/* Efface le contenu de la ligne-écran "y". */

void afficher_char(char ch, int x, int y);
/* Affichera 'ch', qui est soit CH_POISSON ou CH_REQUIN, à la position (y, x). 
   Le caractère CH_REQUIN sera affiché en rouge. */

void delai_ecran(int msec);
/* Effectue un delai de "msec" millisecondes. */

#endif