#include "api.h"


void *getRootTree(){

}


_token *searchTree(void *start, char *name){

}


char *getElementTag(void *node, int *len){

}


char *getElementValue(void *node, int *len){

}


void purgeElement(_token **r){

}


int parseur(char *req, int len){

	/* Variables */
	rulename *start_line = NULL,
		 *header = NULL;
	char *start_c;
	int field_len,
	    headers_end = 0;


	/* Initialisation : On crée la rulename mère HTTP-message */
	request_tree = createRulename("HTTP-message", req, len);


	/* == Récupération de la start-line == */
	start_line = createRulename("start-line", req, len);

	/* = Récupération de la méthode */

	//Recherche
	start_c = req;	
	if((field_len = detectWS(start_c, len)) == NOT_FOUND){
		fprintf(stderr, "Erreur : Champ method non trouvé.\n");
		return -1;
	}

	//TODO : vérif syntaxique de la méthode
	
	//Insertion du champ
	insertRulename(start_line, createRulename("method", start_c, field_len));

	/* = Récupération de la request-target = */

	//Recherche après la fin du champ méthode
	start_c = start_c + field_len + 1;
	if((field_len = detectWS(start_c, len)) == NOT_FOUND){
		fprintf(stderr, "Erreur : Champ request-target non trouvé.\n");
		return -1;
	}

	//TODO : décomposition de la request-target
	
	//Insertion du champ
	insertRulename(start_line, createRulename("request-target", start_c, field_len));

	/* = Récupération de la version HTTP = */

	//Recherche après la fin du champ request-target
	start_c = start_c + field_len + 1;
	if((field_len = detectCRLF(start_c, len)) == NOT_FOUND){
		fprintf(stderr, "Erreur : Champ HTTP-version non trouvé.\n");
		return -1;
	}

	//TODO : vérif syntaxique de la version HTTP
	
	//Insertion du champ
	insertRulename(start_line, createRulename("HTTP-version", start_c, field_len));

	/* = Mise à jour du noeud start-line et insertion = */
	updateRulename(start_line, req, (start_c+field_len)-req);
	insertRulename(request_tree, start_line);


	/* == Récupération des headers jusqu'au double CRLF == */
	do
	{
		start_c = start_c + field_len + 2;
		//Fin des champs d'entête 
		if((field_len = detectCRLF(start_c, len)) <= 0){
			headers_end = 1;
		}

	}while(!headers_end);
}

