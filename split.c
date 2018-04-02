#include <stdio.h>
#include <stdlib.h>

#include "parseur.h"
#include "tree.h"
#include "check.h"
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


int detectArobase(char *start, int r_len){

	int len = 0;

	/* On avance dans la chaîne jusqu'à trouver un '@' ou la fin de la chaîne */
	while(len <= r_len &&
	      *(start+len) != '@'){
		len++;
	}

	if(len > r_len){
		/* Si on a pas trouvé, on renvoie NOT_FOUND */
		return NOT_FOUND;
	}
	else{
		/* On renvoie le nombre de caractères du départ jusqu'à @ exclu */
		return len;
	}
}


int detectDelim(char *start, int r_len, char delim){

	int len = 0;

	/* On avance dans la chaîne jusqu'à trouver un délimiteur ou la fin de la chaîne */
	while(len <= r_len &&
	      *(start+len) != delim){
		len++;
	}

	if(len > r_len){
		/* Si on a pas trouvé, on renvoie NOT_FOUND */
		return NOT_FOUND;
	}
	else{
		/* On renvoie le nombre de caractères du départ jusqu'au delim exclu */
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
		//fprintf(stderr, "Erreur : Absolute-path ne commence pas par un '/'.\n");
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

		/* Vérification syntaxique des segments */
		if(!isSegment(c_start, segment_len)){
			recursNodeDel(origin_node);
			recursNodeDel(path_node);
			return FALSE;
		}
		
		/* Ajout du segment à l'arbre */
		insertRulename(path_node, createRulename("segment", c_start, segment_len));

		/* On avance dans le champ */
		c_start += segment_len + 1;
		processed_char += segment_len + 1;
	}

	/* Test de la présence d'un éventuel dernier segment */
	if(processed_char < path_len){

		/* Vérification syntaxique du segment */
		if(!isSegment(c_start, path_len - processed_char)){
			recursNodeDel(origin_node);
			recursNodeDel(path_node);
			return FALSE;
		}
		
		/* Ajout du segment */
		insertRulename(path_node, createRulename("segment", c_start, path_len - processed_char));
	}

	/* Ajout du node path au node origin */
	insertRulename(origin_node, path_node);

	/* Ajout du node origin au node parent */
	insertRulename(parent_node, origin_node);

	return TRUE;
}



int splitLikeAbsoluteForm(char *start, int r_len, rulename *parent_node){

	int path_len,
	    scheme_len;
	rulename *absolute_node = NULL,
		 *URI_node = NULL;

	/* Création de la rulename absolute */
	absolute_node = createRulename("absolute-form", start, r_len);
	URI_node = createRulename("absolute-URI", start, r_len);
	insertRulename(absolute_node, URI_node);

	/* Détection et ajout d'une éventuelle query */
	if((path_len = recoverQuery(start, r_len, URI_node)) == NOT_FOUND){
		/* Si on a pas trouvé, le chemin prend tout le champs */
		path_len = r_len;
	}

	/* Détection du scheme et du hier-part */
	if((scheme_len = detectColon(start, path_len)) == NOT_FOUND){
		/* En cas d'abscence de délimiteur ':', on retourne FALSE */
		//fprintf(stderr, "Erreur : Délimiteur de l'absolute-URI absent.\n");
		recursNodeDel(absolute_node);
		return FALSE;
	}

	/* Verification syntaxique du scheme */
	if(!isScheme(start, scheme_len)){
		recursNodeDel(absolute_node);
		return FALSE;
	}
	
	/* Insertion du scheme */
	insertRulename(URI_node, createRulename("scheme", start, scheme_len));

	//TODO : Verif syntaxique de la hier-part
	//Horrible et traumatisante - à traiter en dernier dernier dernier
	
	/* Insertion du hier-part */
	insertRulename(URI_node, createRulename("hier-part", start + scheme_len + 1, path_len - (scheme_len + 1)));

	/* Ajout du node absolute au node parent */
	insertRulename(parent_node, absolute_node);

	return TRUE;
}



int splitLikeAuthorityForm(char *start, int r_len, rulename *parent_node){

	int userinfo_len,
	    port_len;
	rulename *authority_form_node = NULL,
		 *authority_node = NULL,
		 *host_node = NULL;

	/* Création de la rulename authority-form */
	authority_form_node = createRulename("authority-form", start, r_len);
	authority_node = createRulename("authority", start, r_len);
	insertRulename(authority_form_node, authority_node);

	/* Récupération d'un éventuel champ 'userinfo' */
	if((userinfo_len = recoverUserinfo(start, r_len, authority_node)) == NOT_FOUND){
		userinfo_len = 0;
	}

	/* Récupération d'un éventuel champ 'port' */
	if((port_len = recoverPort(start + (userinfo_len == 0 ? 0 : userinfo_len + 1), r_len, authority_node)) == NOT_FOUND){
		port_len = r_len;
	}

	/* Récupération du champ 'host' */
	host_node = createRulename("host", start + (userinfo_len == 0 ? 0 : userinfo_len + 1), port_len - (userinfo_len == 0 ? 0 : userinfo_len + 1));

	/* Découpage et vérification syntaxique de l'host */
	if(isIPv4(start + (userinfo_len == 0 ? 0 : userinfo_len + 1), port_len - (userinfo_len == 0 ? 0 : userinfo_len + 1))){
		/* C'est une IPv4 */
		insertRulename(host_node, createRulename("IPv4address", start + (userinfo_len == 0 ? 0 : userinfo_len + 1), port_len - (userinfo_len == 0 ? 0 : userinfo_len + 1)));
	}
	else if(isRegname(start + (userinfo_len == 0 ? 0 : userinfo_len + 1), port_len - (userinfo_len == 0 ? 0 : userinfo_len + 1))){
		/* C'est un reg-name */
		insertRulename(host_node, createRulename("reg-name", start + (userinfo_len == 0 ? 0 : userinfo_len + 1), port_len - (userinfo_len == 0 ? 0 : userinfo_len + 1)));
	}
	else{
		/* Ce n'est pas un champ reconnu, on retourne une erreur et on supprime proprement le noeud */
		recursNodeDel(authority_form_node);
		return FALSE;
	}
	
	/* Insertion du champ host dans l'arbre */
	insertRulename(authority_node, host_node);

	/* Ajout du node authority au node parent */
	insertRulename(parent_node, authority_form_node);

	return TRUE;
}


int recoverQuery(char *start, int r_len, rulename *parent_node){

	int pre_query_len;

	/* Si on ne trouve pas de délimiteur '?', on s'arrête */
	if((pre_query_len = detectInterrogationPoint(start, r_len)) == NOT_FOUND){
		return NOT_FOUND;
	}

	/* Vérification syntaxique de la query */
	if(!isQuery(start, r_len)){
		return FALSE;
	}
	
	/* Ajout de la query à l'arbre de dérivation */
	insertRulename(parent_node, createRulename("query", start + pre_query_len + 1, r_len - pre_query_len - 1));

	/* Renvoyer le nombre de caractères entre le caractère de départ et le délimiteur */
	return pre_query_len;
}


int recoverUserinfo(char *start, int r_len, rulename *parent_node){
	
	int len;

	/* Si on ne trouve pas de délimiteur '@', on s'arrête */
	if((len = detectArobase(start, r_len)) == NOT_FOUND){
		return NOT_FOUND;
	}

	/* Vérification syntaxique de l'userinfo */
	if(!isUserinfo(start, r_len)){
		return FALSE;
	}
	
	/* Ajout de l'userinfo à l'arbre de dérivation */
	insertRulename(parent_node, createRulename("userinfo", start, len));

	/* Renvoyer la longueur du champ récupéré */
	return len;
}


int recoverPort(char *start, int r_len, rulename *parent_node){

	int len;

	/* Si on ne trouve pas de délimiteur ':', on s'arrête */
	if((len = detectColon(start, r_len)) == NOT_FOUND){
		return NOT_FOUND;
	}

	/* Vérification syntaxique du port */
	if(!isPort(start, r_len)){
		return FALSE;
	}
	
	/* Ajout du port à l'arbre de dérivation */
	insertRulename(parent_node, createRulename("port", start + len + 1, r_len - len - 1));

	/* Renvoyer le nombre de caractères entre le caractère de départ et le délimiteur */
	return len;
}
