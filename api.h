#ifndef __API_H__
#define __API_H__

/* == Structures == */

/* Défini un type pour la liste chaînée renvoyée en réponse de la requête de recherche dans l'arbre */
typedef struct _token{

	void *node;		/* Pointeur sur un noeud de l'arbre */
	struct _token *next;	/* Pointeur sur le prochain token */

} _Token;


/* == Prototypes == */

/* Retourne un pointeur sur la racine de l'arbre construit */
void *getRootTree();


/* Recherche dans l'arbre les noeuds d'étiquette égale à la chaîne passée en arg, à partir de start...
 * Si start == NULL, on commence à la racine  */
_Token *searchTree(void *start, char *name);


/* Renvoie un pointeur sur le premier carac de la rulename, et met la longueur de cette rulename dans
 * len si pointeur non NULL */
char *getElementTag(void *node, int *len);


/* Renvoie un pointeur sur le premier carac de la valeur du noeud, et met la longueur du noeud dans
 * len si pointeur non NULL */
char *getElementValue(void *node, int *len);


/* Supprime proprement la liste chaînée */
void purgeElement(_Token **r);


/* Appel du parseur, qui parse une chaîne req de longueur len */
int parseur(char *req, int len);

#endif
