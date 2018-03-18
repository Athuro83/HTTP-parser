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


/* Renvoie le pointeur vers le noeud de rulename spécifiée, ou NULL si la rulename est absente.
 * Commence la recherche à partir de search_start */
rulename *searchRulename(char* name, rulename *search_start, rulename **prec_node);


/* Fonction de suppression d'une rulename  :
 * Supprime proprement le noeud associé à la rulename name ainsi que tous ses fils.
 */
int delRulename(char *name, rulename **root);



/* Fonction de suppression récursive :
 * Supprime proprement le noeud passé en paramètre ainsi que tous ses fils et ses voisins.
 */
void recursNodeDel(rulename *node);



/* Fonction de suppression :
 * Supprime proprement le noeud passé en paramètre.
 */
void nodeDel(rulename *node);

#endif
