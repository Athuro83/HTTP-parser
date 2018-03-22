#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parseur.h"
#include "tree.h"
#include "split.h"
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
	char *start_c,
	     *data_start_c,
	     *header_name;
	int field_len,
	    header_name_len,
	    data_len,
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
		//Traitement d'un champ header
		else{
			if((header_name_len = detectColon(start_c, len)) == NOT_FOUND){
				fprintf(stderr, "Header %*.*s non conventionnel. On passe...\n", field_len, field_len, start_c);
				continue;
			}

			//Création du nom du header avec les infos contenues dans le champ
			header_name = (char *) malloc((header_name_len+HEADER_SUFFIX_LEN)*sizeof(char));
			strncpy(header_name, start_c, header_name_len);
			strcat(header_name, "-header");

			//Création du noeud père qui contient tout le header
			header = createRulename(header_name, start_c, field_len);

			//Recherche de la valeur du header
			data_start_c = start_c + header_name_len + 1;
			if((data_len = removeOWS(&data_start_c, field_len-(header_name_len+1))) != 0){
				//TODO : Verif syntaxique de la valeur, en fonction du nom du header
				
				//Création du noeud data
				*(header_name+header_name_len) = '\0';
				insertRulename(header, createRulename(header_name, data_start_c, data_len));
			}

			//Libération de l'espace pour le nom du header
			free(header_name);

			//Insertion du noeud header
			insertRulename(request_tree, header);
		}

	}while(!headers_end);


	/* == Récupération du body s'il existe == */
	start_c = start_c + 2;
	//Si on a pas atteint la fin de la requête
	if(((req + len - 1) - start_c) > 0){
		//Création d'un noeud body
		insertRulename(request_tree, createRulename("body", start_c, (req + len - 1) - start_c));
	}
	return 1;
}

