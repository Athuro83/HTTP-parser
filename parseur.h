/*=
 *
 * 	Fichier de définitions des structures et
 * 		variables du parseur.
 *
 *= 	
 */


#ifndef __PARSEUR_H__
#define __PARSEUR_H__


/* ===[ Structures ]=== */

/*
 * 	Structure rulename
 *
 * Représente un noeud de l'arbre de dérivation.
 * Stocke la sous-chaîne correspondant à la rulename nommée dans le champs rulename.
 */
typedef struct rulename{

	char* rulename;		/* Nom de la rulename ABNF stockée */
	char* start;		/* Premier caractère de la chaîne stockée */
	int len;		/* Longueur de la chaîne stockée */

	struct rulename *next; 	/* Pointeur vers la prochaine rulename de l'étage, ou NULL si dernière rulename de l'étage */
	struct rulename *child;	/* Pointeur vers la liste des fils de cette rulename, ou NULL s'il s'agit d'une rulename terminale */

} rulename;


/* ===[ Constantes ]=== */

#define TRUE 1
#define FALSE 0

#endif
