/*======================================================
 *
 * 	Fichier d'entête des fonctions de manipulation
 * 		de l'arbre de dérivation	
 *
 *====================================================== 	
 */
#ifndef __TREE_H__
#define __TREE_H__

/*==================================================
 *
 * 			Fonction createRulename
 *
 * 	But:
 * 	Créer une nouveau noeud représentant une
 * 	rulename HTTP
 *
 * 	Paramètres:
 *	- name : Le nom de la rulename HTTP stockée
 *	dans ce noeud.
 *	- start : Un pointeur sur le premier caractère
 *	de la sous-chaîne liée à la rulename.
 *	- len : La taille de la sous-chaîne
 *
 *	Retour:
 *	- Un pointeur sur le nouveau noeud en cas
 *	de succès.
 *	- NULL sinon.
 *
 *==================================================
 */
rulename *createRulename(char *name, char *start, int len);


/*==================================================
 *
 * 			Fonction insertRulename
 *
 * 	But:
 * 	Insère un noeud dans l'arbre de dérivation,
 * 	en tant que fils d'un autre noeud.
 *
 * 	Paramètres:
 * 	- father : Pointeur vers le noeud parent du
 * 	noeud à insérer.
 * 	- rule : Pointeur vers le noeud à insérer.
 *
 * 	Retour:
 * 	- TRUE si l'insertion a bien eu lieu.
 *	- FALSE sinon.
 *
 *==================================================
 */
int insertRulename(rulename *father, rulename *rule);


/*==================================================
 *
 * 			Fonction displayRulename
 *
 * 	But:
 * 	Affiche de façon formatée le contenu d'un
 * 	noeud.
 *
 * 	Paramètres:
 * 	- rule : Pointeur vers le noeud à afficher.
 *
 *==================================================
 */
void displayRulename(rulename *rule);


/*==================================================
 *
 * 			Fonction searchRulename
 *
 * 	But:
 * 	Cherche un noeud dans un sous-arbre en
 * 	connaissant seulement son nom.
 *
 * 	Paramètres:
 * 	- name : La rulename HTTP du noeud à trouver.
 * 	- search_start : Pointeur vers le sommet du
 * 	sous-arbre dans lequel chercher.
 * 	- prec_node : Optionnel. Si fournit, renvoie
 * 	un pointeur sur le noeud précédent l'élément
 * 	cherché, ou 0x0 si l'élément recherché est le
 * 	sommet du sous-arbre.
 *
 * 	Retour:
 * 	- Un pointeur sur l'élément cherché si il
 * 	existe.
 * 	- NULL sinon.
 *
 *==================================================
 */
rulename *searchRulename(char* name, rulename *search_start, rulename **prec_node);


/*==================================================
 *
 * 			Fonction delRulename
 *
 * 	But:
 * 	Supprime un noeud repéré par sa rulename HTTP,
 * 	ainsi que tous ses fils.
 *
 * 	Paramètres:
 * 	- name : La rulename HTTP a supprimer.
 * 	- root : Un pointeur sur le pointeur vers la
 * 	racine de l'arbre où se trouve le noeud.
 *
 * 	Retour:
 * 	- TRUE si l'élément a bien été supprimé.
 * 	- FALSE sinon.
 *
 *==================================================
 */
int delRulename(char *name, rulename **root);



/*==================================================
 *
 * 			Fonction recursNodeDel
 *
 * 	But:
 * 	Supprime de façon récursive les fils et voisins
 * 	d'un noeud, ainsi que le noeud lui-même.
 *
 * 	Paramètres:
 * 	- node : Pointeur vers le noeud de départ de
 * 	la récursion.
 *
 *==================================================
 */
void recursNodeDel(rulename *node);



/*==================================================
 *
 * 			Fonction nodeDel
 *
 * 	But:
 * 	Supprime un noeud.
 *
 * 	Paramètres:
 * 	- node : Pointeur vers le noeud à supprimer.
 *
 *==================================================
 */
void nodeDel(rulename *node);



/*==================================================
 *
 * 			Fonction updateRulename
 *
 * 	But:
 * 	Mettre à jour un noeud.
 *
 * 	Paramètres:
 * 	- node : Pointeur sur le noeud à mettre à
 * 	jour.
 * 	- n_start : Nouveau pointeur sur le caractère
 * 	de départ.
 * 	-n_len : Nouvelle taille de chaîne.
 *
 * 	Retour:
 * 	- TRUE si la mise à jour a été effectuée.
 * 	- FALSE sinon.
 *
 *==================================================
 */
int updateRulename(rulename *node, char *n_start, int n_len);

#endif
