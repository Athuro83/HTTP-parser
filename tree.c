#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parseur.h"
#include "tree.h"


rulename *createRulename(char *name, char *start, int len){

	rulename* rule = (rulename *) malloc(sizeof(rulename));

	/* Init. des vecteurs */
	rule->next = NULL;
	rule->child = NULL;

	/* Copie du nom de la rulename */
	rule->rulename = (char *) malloc(strlen(name) * sizeof(char));
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

