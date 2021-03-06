#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parseur.h"
#include "tree.h"
#include "split.h"
#include "api.h"
#include "check.h"


void *getRootTree(){

	/* Renvoyer le pointeur vers la rulename HTTP-message */
	return request_tree;
}


_Token *searchTree(void *start, char *name){

	_Token *list = NULL,
	       *new_Token = NULL;
	_Token **end_list = &list;
	rulename *r_node = NULL;

	/* Définition du point de départ */
	if(start == NULL){
		r_node = (rulename *) getRootTree();
	}
	else{
		r_node = (rulename *) start;
	}

	/* Examen du noeud courant */
	if(strcmp(r_node->rulename, name) == 0){

		/* En cas de match, création d'un nouveau token */
		if((new_Token = (_Token *) malloc(sizeof(_Token))) == NULL){
			fprintf(stderr, "Erreur d'allocation mémoire.\n");
			exit(0);
		}		

		/* Remplissage et intégration à la liste */
		new_Token->node = (rulename *) r_node;
		new_Token->next = list;
		list = new_Token;
		/* On fait avancer la fin de la liste */
		end_list = &new_Token->next;
	}

	/* Examen des éventuels enfants */
	if(r_node->child != NULL && (new_Token = searchTree(r_node->child, name)) != NULL){

		/* En cas de retour d'une liste, on l'ajoute à la fin de celle déjà constituée */
		*end_list = new_Token;
		/* On fait avancer la fin de la liste */
		while(new_Token != NULL){
			new_Token = new_Token->next;
		}
		end_list = &new_Token;
	}

	/* Examen des éventuels voisins */
	if(r_node->next != NULL && (new_Token = searchTree(r_node->next, name)) != NULL){

		/* En cas de retour d'une liste, on l'ajoute à la fin de celle déjà constituée */
		*end_list = new_Token;
	}

	/* Retour de la liste ainsi créée */
	return list;
}


char *getElementTag(void *node, int *len){

	rulename *r_node = (rulename *) node;

	//Vérification du paramètre
	if(node == NULL){
		fprintf(stderr, "Pas de noeud passé en paramètre.\n");
		return FALSE;
	}

	if(len != NULL){
		//Mettre la longueur de la rulename dans len
		*len = strlen(r_node->rulename);
	}

	return r_node->rulename;
}


char *getElementValue(void *node, int *len){

	rulename *r_node = (rulename *) node;

	//Vérification du paramètre
	if(node == NULL){
		fprintf(stderr, "Pas de noeud passé en paramètre.\n");
		return FALSE;
	}

	if(len != NULL){
		//Mettre la longueur de la valeur dans len
		*len = r_node->len;
	}

	return r_node->start;
}


void purgeElement(_Token **r){

	_Token *cur_tok = *r,
	       *prec_tok = NULL;

	while(cur_tok != NULL){		//Tant qu'il reste des tokens dans la liste
		//On enregistre la position de l'éventuel suivant
		prec_tok = cur_tok;
		cur_tok = cur_tok->next;
		//On libère l'élément courant
		free(prec_tok);
	}
}


int parseur(char *req, int len){

	/* Variables */
	rulename *start_line = NULL,
		 *request_line = NULL,
		 *request_target = NULL,
		 *header = NULL,
		 *header_data = NULL;
	char *start_c,
	     *data_start_c,
	     *header_name;
	int field_len,
	    header_name_len,
	    data_len,
	    headers_end = 0;


	/* Initialisation : On crée la rulename mère HTTP-message */
	request_tree = createRulename("HTTP-message", req, len);


	/* == Récupération de la request-line == */
	request_line = createRulename("request-line", req, len);

	/* = Récupération de la méthode */

	//Recherche
	start_c = req;	
	if((field_len = detectWS(start_c, len)) == NOT_FOUND){
		fprintf(stderr, "Erreur : Champ method non trouvé.\n");
		/* Purge de l'arbre */
		recursNodeDel(request_tree);
		recursNodeDel(request_line);
		return FALSE;
	}

	/* Vérification syntaxique de la méthode */
	if(!isToken(start_c, field_len)){
		fprintf(stderr, "Erreur : Le champ method contient des caractères illégaux.\n");
		/* Purge de l'arbre */
		recursNodeDel(request_tree);
		recursNodeDel(request_line);
		return FALSE;
	}
	
	//Insertion du champ
	insertRulename(request_line, createRulename("method", start_c, field_len));

	/* = Récupération de la request-target = */

	//Recherche après la fin du champ méthode
	start_c = start_c + field_len + 1;
	if((field_len = detectWS(start_c, len)) == NOT_FOUND){
		fprintf(stderr, "Erreur : Champ request-target non trouvé.\n");
		/* Purge de l'arbre */
		recursNodeDel(request_tree);
		recursNodeDel(request_line);
		return FALSE;
	}
	request_target = createRulename("request-target", start_c, field_len);

	/* Décomposition de la request-target */
	if(!splitLikeAsteriskForm(start_c, field_len, request_target) &&
	   !splitLikeOriginForm(start_c, field_len, request_target) &&
	   !splitLikeAbsoluteForm(start_c, field_len, request_target) &&
	   !splitLikeAuthorityForm(start_c, field_len, request_target)){
		fprintf(stderr, "Erreur : Champ request-target non conforme.\n");
		/* Purge de l'arbre */
		recursNodeDel(request_tree);
		recursNodeDel(request_line);
		return FALSE;
	}
	
	//Insertion du champ
	insertRulename(request_line, request_target);

	/* = Récupération de la version HTTP = */

	//Recherche après la fin du champ request-target
	start_c = start_c + field_len + 1;
	if((field_len = detectCRLF(start_c, len)) == NOT_FOUND){
		fprintf(stderr, "Erreur : Champ HTTP-version non trouvé.\n");
		/* Purge de l'arbre */
		recursNodeDel(request_tree);
		recursNodeDel(request_line);
		return FALSE;
	}

	/* Vérification syntaxique de la version HTTP */
	if(!isHTTPVers(start_c, field_len)){
		fprintf(stderr, "Erreur : Le champ HTTP-version contient des caractères illégaux.\n");
		/* Purge de l'arbre */
		recursNodeDel(request_tree);
		recursNodeDel(request_line);
		return FALSE;
	}
	
	//Insertion du champ
	insertRulename(request_line, createRulename("HTTP-version", start_c, field_len));

	/* = Mise à jour du noeud request-line et insertion = */
	updateRulename(request_line, req, (start_c+field_len)-req);
	start_line = createRulename("start-line", req, (start_c+field_len)-req);
	insertRulename(start_line, request_line);
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

			/* Détection de l'espace invalide entre le header name et le ':' */
			if(*(start_c+header_name_len-1) == ' '){
				//fprintf(stderr, "Espace invalide détecté ! On passe...\n");
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

				//Création du noeud data
				*(header_name+header_name_len) = '\0';
				header_data = createRulename(header_name, data_start_c, data_len);
				insertRulename(header, header_data);

				//TODO : Verif syntaxique de la valeur, en fonction du nom du header
				if(strncmp("Host", start_c, strlen("Host")-1) == 0){
					/* Parsing d'un header Host */
					if(!splitHost(data_start_c, data_len, header_data)){
						recursNodeDel(header);
						printf("Non conforme\n");
						continue;
					}
				}
				else if(strncmp("User-Agent", start_c, strlen("User-Agent")-1) == 0){
					/* Parsing d'un header User-Agent */
					if(!splitUserAgent(data_start_c, data_len, header_data)){
						recursNodeDel(header);
						printf("UserAgent prob\n");
						continue;
					}
				}
				else if(strncmp("Connection", start_c, strlen("Connection")-1) == 0){
					/* Parsing d'un header Connection */
					if(!splitConnection(data_start_c, data_len, header_data)){
						recursNodeDel(header);
						printf("Connection prob\n");
						continue;
					}
				}
				else if(strncmp("Accept", start_c, strlen("Accept")-1) == 0){
					/* Parsing d'un header Accept */
				}


			}

			//Libération de l'espace pour le nom du header
			free(header_name);

			//Insertion du noeud header
			insertRulename(request_tree, header);
		}

	}while(!headers_end);

	if(field_len == NOT_FOUND){
		printf("Entête incomplète.\n");
		return FALSE;
	}

	/* == Récupération du body s'il existe == */
	start_c = start_c + 2;
	//Si on a pas atteint la fin de la requête
	if(((req + len - 1) - start_c) > 0){
		//Création d'un noeud body
		insertRulename(request_tree, createRulename("body", start_c, (req + len - 1) - start_c));
	}

	/* Requête parsée avec succès */
	return TRUE;
}

