#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parseur.h"
#include "tree.h"

/* Déclaration de la racine de l'arbre */
rulename *request_tree;

rulename *createRulename(char *name, char *start, int len){

	rulename* rule = (rulename *) malloc(sizeof(rulename));
	if(rule == NULL){
		fprintf(stderr, "Erreur de création - Problème d'allocation.\n");
		return NULL;
	}

	/* Init. des vecteurs */
	rule->next = NULL;
	rule->child = NULL;

	/* Copie du nom de la rulename */
	rule->rulename = (char *) malloc(strlen(name) * sizeof(char));
	if(rule->rulename == NULL){
		fprintf(stderr, "Erreur de création - Problème d'allocation.\n");
		return NULL;
	}
	strcpy(rule->rulename, name);

	/* Copie du couple (start,len) */
	rule->start = start;
	rule->len = len;

	/* Renvoyer la structure */
	return rule;
}


int insertRulename(rulename *father, rulename *rule){

	rulename *elem = NULL,
		 *elem_prec = NULL;

	/* Pas de père précisé */
	if(father == NULL){
		fprintf(stderr, "Erreur d'insertion - Père non précisé.\n");
		return FALSE;
	}

	/* Insertion en tant que premier fils */ 
	if(father->child == NULL){
		father->child = rule;
		return TRUE;
	}

	/* Insertion à la suite de fils existants */
	elem_prec = father->child;
	elem = (father->child)->next;

	while(elem != NULL){
		elem_prec = elem;
		elem = elem->next;
	}

	elem_prec->next = rule;

	return TRUE;
}



void displayRulename(rulename *rule){

	printf("==[ Rulename %s ]==\n", rule->rulename);
	printf("Contient : %*.*s\n", rule->len, rule->len, rule->start);
	printf("==[ Fin ]==\n\n");
}



rulename *searchRulename(char* name, rulename *search_start, rulename **prec_node){

	/* Variables */
	rulename *node = NULL;

	/* Init */
	if(prec_node != NULL){
		*prec_node = 0x0;
	}

	/* Vérification des entrées */
	if(search_start == NULL){
		fprintf(stderr, "Erreur de recherche - Point de départ non précisé.\n");
		return NULL;
	}

	if(name == NULL){
		fprintf(stderr, "Erreur de recherche - Rulename non précisée.\n");
		return NULL;
	}

	/* Test du noeud de départ */
	if(strcmp(name, search_start->rulename) == 0){
		return search_start;
	}

	/* Recherche parmis les fils s'ils existent */
	if(search_start->child != NULL &&
	   (node = searchRulename(name, search_start->child, prec_node)) != NULL){

		if(prec_node != NULL && *prec_node == 0x0){
			*prec_node = search_start;
		}
		return node;
	}

	/* Recherche parmis les voisins s'ils existent */
	if(search_start->next != NULL &&
	   (node = searchRulename(name, search_start->next, prec_node)) != NULL){

		if(prec_node != NULL && *prec_node == 0x0){
			*prec_node = search_start;
		}
	   	return node;
	}

	/* Recherche infructueuse */
	return NULL;	
}



int delRulename(char *name, rulename **root){

	rulename *node = NULL,
		 *prec_node = NULL;

	/* Vérif des entrées */
	if(name == NULL){
		fprintf(stderr, "Erreur de suppression - Pas de rulename précisée.\n");
		return FALSE;
	}

	if(*root == NULL){
		fprintf(stderr, "Erreur de suppression - Pas de point de départ précisé.\n");
		return FALSE;
	}

	/* Recherche du noeud à supprimer + le noeud qui pointe vers lui */
	node = searchRulename(name, *root, &prec_node);

	/* Exclusion de l'arbre */

	if(prec_node == 0x0){
		/* On pointe directement sur l'élément à supprimer, modification du pointeur nécessaire */
		*root = node->next;
	}
	else{
		/* Sinon, il faut juste déterminer la "position" du noeud précédent */
		if(prec_node->child == node){
			prec_node->child = node->next;
		}
		else{
			prec_node->next = node->next;
		}
	}

	/* Suppression des fils du noeud */
	if(node->child != NULL){
		recursNodeDel(node);
	}

	return TRUE;
}



void recursNodeDel(rulename *node){

	/* Suppression des enfants du noeud s'ils existent */
	if(node->child != NULL){
		recursNodeDel(node->child);
	}

	/* Suppression des voisins du noeud s'ils existent */
	if(node->next != NULL){
		recursNodeDel(node->next);
	}

	/* Suppression du noeud */
	nodeDel(node);
}



void nodeDel(rulename *node){

	free(node->rulename);
	free(node);
}



int updateRulename(rulename *node, char *n_start, int n_len){

	if(node == NULL){
		fprintf(stderr, "Erreur de mise à jour - Pas de noeud précisé.\n");
		return FALSE;
	}

	node->start = n_start;
	node->len = n_len;

	return TRUE;
}

