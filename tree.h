/*=
 *
 * 	Fichier d'entête des fonctions de manipulation
 * 		de l'arbre de dérivation	
 *
 *= 	
 */
#ifndef __TREE_H__
#define __TREE_H__

/* Fonction de création d'un nouveau noeud/rulename */
rulename *createRulename(char *rulename, char *start, int len);


/* Fonction d'insertion d'un noeud dans l'arbre, en tant que fils d'un noeud existant.
 * Retourne TRUE si l'insertion est ok, FALSE sinon */
int insertRulename(rulename *father, rulename *rule);


/* Affiche les informations contenues dans un noeud */
void displayRulename(rulename *rule);

/* Renvoie le pointeur vers le noeud de rulename spécifiée, ou NULL si la rulename est absente */
rulename *searchRulename(char* rulename);

#endif
