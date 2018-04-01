#include <stdio.h>
#include <stdlib.h>

#include "parseur.h"
#include "tree.h"
#include "split.h"


int detectWS(char *start, int r_len){

	int len = 0;

	/* On avance dans la chaîne jusqu'à trouver un ' ' ou la fin de la chaîne */
	while(len <= r_len &&
	      *(start+len) != ' '){
		len++;
	}

	if(*(start+len) == ' '){
		/* On renvoie le nombre de caractères du départ jusqu'à l'espace exclu */
		return len;
	}
	else{
		/* Si on a pas trouvé, on renvoie NOT_FOUND */
		return NOT_FOUND;
	}
}



int detectCRLF(char *start, int r_len){

	int len = 0;

	/* On avance dans la chaîne jusqu'à trouver un '\r\n' ou la fin de la chaîne */
	while(len < r_len &&
	      !(*(start+len) == '\r' && *(start+len+1) == '\n')){
		len++;
	}

	if(len >= r_len){
		/* Si on a pas trouvé, on renvoie NOT_FOUND */
		return NOT_FOUND;
	}
	else{
		/* On renvoie le nombre de caractères du départ jusqu'au CRLF exclu */
		return len;
	}
}


int detectColon(char *start, int r_len){

	int len = 0;

	/* On avance dans la chaîne jusqu'à trouver un ':' ou la fin de la chaîne */
	while(len <= r_len &&
	      *(start+len) != ':'){
		len++;
	}

	if(len > r_len){
		/* Si on a pas trouvé, on renvoie NOT_FOUND */
		return NOT_FOUND;
	}
	else{
		/* On renvoie le nombre de caractères du départ jusqu'au : exclu */
		return len;
	}
}


int detectInterrogationPoint(char *start, int r_len){

	int len = 0;

	/* On avance dans la chaîne jusqu'à trouver un ':' ou la fin de la chaîne */
	while(len <= r_len &&
	      *(start+len) != '?'){
		len++;
	}

	if(len > r_len){
		/* Si on a pas trouvé, on renvoie NOT_FOUND */
		return NOT_FOUND;
	}
	else{
		/* On renvoie le nombre de caractères du départ jusqu'au ? exclu */
		return len;
	}
}


int detectSlash(char *start, int r_len){

	int len = 0;

	/* On avance dans la chaîne jusqu'à trouver un '/' ou la fin de la chaîne */
	while(len <= r_len &&
	      *(start+len) != '/'){
		len++;
	}

	if(len > r_len){
		/* Si on a pas trouvé, on renvoie NOT_FOUND */
		return NOT_FOUND;
	}
	else{
		/* On renvoie le nombre de caractères du départ jusqu'au / exclu */
		return len;
	}
}


int removeOWS(char **start, int h_len){

	int data_len = 0,
	    len = 0;

	/* On avance tant qu'il y a des espaces et qu'on a pas dépassé la fin du champ */
	while(len < h_len &&
	      **start == ' '){
		*start += 1;
		len++;
	}

	/* On a trouvé le début du champ, on compte jusqu'au prochain espace ou bien la sortie du champ */
	while(len < h_len &&
	      *(*start+data_len) != ' '){
		data_len++;
		len++;
	}

	return data_len;
}


int splitLikeAsteriskForm(char *start, int r_len, rulename *parent_node){

	/* Si on a bien une asterisque, on ajoute le noeud et on renvoie TRUE */
	if(r_len == 1 && *start == '*'){
		insertRulename(parent_node, createRulename("asterisk-form", start, r_len));
		return TRUE;
	}
	/* Sinon, on renvoie FAUX */
	else{
		return FALSE;
	}
}


int splitLikeOriginForm(char *start, int r_len, rulename *parent_node){

	int path_len,
	    processed_char = 0,
	    segment_len;
	char *c_start = start;
	rulename *origin_node = NULL,
		 *path_node = NULL;

	/* Création de la rulename origin */
	origin_node = createRulename("origin-form", start, r_len);

	/* Détection et ajout d'une éventuelle query */
	if((path_len = recoverQuery(start, r_len, origin_node)) == NOT_FOUND){
		/* Si on a pas trouvé, le chemin prend tout le champs */
		path_len = r_len;
	}

	/* Première vérification : Le chemin commence par un '/' */
	if(*c_start != '/'){
		fprintf(stderr, "Erreur - Absolute-path ne commence pas par un '/'.\n");
		recursNodeDel(origin_node);
		return FALSE;
	}
	c_start += 1;
	processed_char += 1;

	/* Création de la rulename path */
	path_node = createRulename("absolute-path", start, path_len);

	/* Boucle de vérification et récupération des segments */
	while((segment_len = detectSlash(c_start, path_len - processed_char)) != NOT_FOUND &&
	      processed_char < path_len){

		//TODO : Vérif syntaxique des segments - Renvoyer FALSE en cas de mismatch
		
		/* Ajout du segment à l'arbre */
		insertRulename(path_node, createRulename("segment", c_start, segment_len));

		/* On avance dans le champ */
		c_start += segment_len + 1;
		processed_char += segment_len + 1;
	}

	/* Test de la présence d'un éventuel dernier segment */
	if(processed_char < path_len){

		//TODO : Vérif syntaxique du segment
		
		/* Ajout du segment */
		insertRulename(path_node, createRulename("segment", c_start, path_len - processed_char));
	}

	/* Ajout du node path au node origin */
	insertRulename(origin_node, path_node);

	/* Ajout du node origin au node parent */
	insertRulename(parent_node, origin_node);

	return TRUE;
}


int recoverQuery(char *start, int r_len, rulename *parent_node){

	int pre_query_len;

	/* Si on ne trouve pas de délimiteur '?', on s'arrête */
	if((pre_query_len = detectInterrogationPoint(start, r_len)) == NOT_FOUND){
		return NOT_FOUND;
	}

	//TODO : vérif syntaxique de la query
	
	/* Ajout de la query à l'arbre de dérivation */
	insertRulename(parent_node, createRulename("query", start + pre_query_len + 1, r_len - pre_query_len - 1));

	/* Renvoyer la longueur entre caractère de départ et délimiteur '?' */
	return pre_query_len;
}
