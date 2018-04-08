
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parseur.h"
#include "split.h"
#include "check.h"

/* ==[ Tableaux de caractères ]== */
const char unreserved[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghiljklmnopqrstuvwxyz0123456789-._~";
const char sub_delim[]  = "!$&'()*+,;=";
const char hexdig[]	= "0123456789ABCDEF";
const char alphas[]     = "abcdefghiljklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char digits[]     = "0123456789";
const char tchar[]      = "!#$%&'*+-.^_`|~0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghiljklmnopqrstuvwxyz";


int isPartOfList(char c, const char *list, int list_len){

	int i;

	for(i = 0 ; i < list_len ; i++){
		/* On a trouvé le caractère dans la liste */
		if(c == list[i]){
			return TRUE;
		}
	}

	/* Caractère absent de la liste */
	return FALSE;
}


int isIPv4(char *start, int len){

	int offset = 0,
	    number_len,
	    dot_count = 0;

	/* Vérification de la taille */
	if(len < 8 || len > 16){
		return FALSE;
	}

	while(offset < len){

		/* Traitement des 3 premiers octets avec vérification de la présence du délimiteur '.' */
		if(dot_count < 3 &&
		   (number_len = detectDelim(start+offset, len-offset, '.')) == NOT_FOUND){
			return FALSE;
		}
		
		/* Traitement du dernier octet qui va jusqu'à la fin du champ */
		if(dot_count == 3){
			number_len = len - offset;
		}

		/* Examen des caractères trouvés */
		switch(number_len){
			
			case 1:
				/* On vérifie que c'est bien un digit non nul */
				if(*(start+offset) < '0' || *(start+offset) > '9'){
					return FALSE;
				}
				/* Passage au champ suivant */
				offset += 2;
				dot_count++;
				break;

			case 2:
				/* On vérifie que c'est bien des digits */
				if((*(start+offset) < '1' || *(start+offset) > '9') ||
				   (*(start+offset+1) < '0' || *(start+offset+1) > '9')){
					return FALSE;
				}
				/* Passage au champ suivant */
				offset += 3;
				dot_count++;
				break;

			case 3:
				/* On vérifie que ça respecte bien la grammaire HTTP */
				if((*(start+offset) < '1' || *(start+offset) > '2') ||
				   (*(start+offset) == '1' && (*(start+offset+1) < '0' || *(start+offset+1) > '9' || *(start+offset+2) < '0' || *(start+offset+2) > '9')) ||
				   (*(start+offset) == '2' && (*(start+offset+1) < '0' || *(start+offset+1) > '4' || *(start+offset+2) < '0' || *(start+offset+2) > '9')) ||
				   (*(start+offset) == '2' && *(start+offset+1) == '5' && (*(start+offset+2) < '0' || *(start+offset+2) > '5'))){
					return FALSE;
				}
				/* Passage au champ suivant */
				offset += 4;
				dot_count++;
				break;
		}
	}

	return TRUE;
}


int isRegname(char *start, int len){

	int offset = 0;

	while(offset < len){

		/* Test pct-encoded */
		if(*(start+offset) == '%' && 
		   offset+2 < len &&
		   isPartOfList(*(start+offset+1), hexdig, strlen(hexdig)-1) && 
		   isPartOfList(*(start+offset+2), hexdig, strlen(hexdig)-1)){
			offset += 3;
		}
		/* Test sub-delim */
		else if(isPartOfList(*(start+offset), sub_delim, strlen(sub_delim))){
			offset += 1;
		}
		/* Test unreserved */
		else if(isPartOfList(*(start+offset), unreserved, strlen(unreserved))){
			offset += 1;
		}
		else{
			return FALSE;
		}
	}

	/* Tous les caractères appartiennent à des listes acceptées */
	return TRUE;
}


int isScheme(char *start, int len){

	int i;

	/* Premier caractère doit être un ALPHA */
	if(!isPartOfList(*start, alphas, strlen(alphas) - 1)){
		return FALSE;
	}

	for(i = 1 ; i < len ; i++){

		/* Si le caractère n'appartient à aucune des listes de caractères autorisés */
		if(!isPartOfList(*(start+i), alphas, strlen(alphas) - 1) &&
		   !isPartOfList(*(start+i), digits, strlen(digits) - 1) &&
		   !isPartOfList(*(start+i), "+-.", 3)){
			return FALSE;
		}
	}

	return TRUE;
}



int isToken(char *start, int len){

	int i;

	/* On vérifie que le champ contient au moins un caractère */
	if(len == 0){
		return FALSE;
	}

	for(i = 0 ; i < len ; i++){

		/* S'il existe un caractère invalide, on s'arrête */
		if(!isPartOfList(*(start+i), tchar, strlen(tchar) - 1)){
			return FALSE;
		}
	}

	return TRUE;
}



int isHTTPVers(char *start, int len){

	/* Vérification de la taille du champs */
	if(len != HTTP_VERS_LEN){
		return FALSE;
	}

	/* Vérification du champ */
	if(strncmp(start, "HTTP/", HTTP_NAME_LEN + 1) != 0 ||
	   !isPartOfList(*(start+POS_DIGIT_1), digits, strlen(digits) - 1) ||
	   *(start+POS_DOT) != '.' ||
	   !isPartOfList(*(start+POS_DIGIT_2), digits, strlen(digits) - 1)){
		return FALSE;
	}

	return TRUE;
}


int isSegment(char *start, int len){

	int offset = 0;

	while(offset < len){

		/* Test pct-encoded */
		if(*(start+offset) == '%' && 
		   offset+2 < len &&
		   isPartOfList(*(start+offset+1), hexdig, strlen(hexdig)-1) && 
		   isPartOfList(*(start+offset+2), hexdig, strlen(hexdig)-1)){
			offset += 3;
		}
		/* Test sub-delim */
		else if(isPartOfList(*(start+offset), sub_delim, strlen(sub_delim))){
			offset += 1;
		}
		/* Test unreserved */
		else if(isPartOfList(*(start+offset), unreserved, strlen(unreserved))){
			offset += 1;
		}
		/* Test ':' ou '@' */
		else if(isPartOfList(*(start+offset), ":@", 2)){
			offset += 1;
		}
		/* Caractère illégal */
		else{
			return FALSE;
		}
	}

	/* Tous les caractères appartiennent à des listes acceptées */
	return TRUE;
}



int isQuery(char* start, int len){

	int offset = 0;

	while(offset < len){

		/* Test pct-encoded */
		if(*(start+offset) == '%' && 
		   offset+2 < len &&
		   isPartOfList(*(start+offset+1), hexdig, strlen(hexdig)-1) && 
		   isPartOfList(*(start+offset+2), hexdig, strlen(hexdig)-1)){
			offset += 3;
		}
		/* Test sub-delim */
		else if(isPartOfList(*(start+offset), sub_delim, strlen(sub_delim))){
			offset += 1;
		}
		/* Test unreserved */
		else if(isPartOfList(*(start+offset), unreserved, strlen(unreserved))){
			offset += 1;
		}
		/* Test ':' ou '@' ou '/' ou '?' */
		else if(isPartOfList(*(start+offset), ":@/?", 4)){
			offset += 1;
		}
		/* Caractère illégal */
		else{
			return FALSE;
		}
	}

	/* Tous les caractères appartiennent à des listes acceptées */
	return TRUE;
}



int isPort(char *start, int len){

	int i;

	for(i = 0 ; i < len ; i++){
		/* Vérification que chaque caractère est un digit */
		if(*start < '0' || *start > '9'){
			return FALSE;
		}
	}

	return TRUE;
}



int isUserinfo(char *start, int len){

	int offset = 0;

	while(offset < len){

		/* Test pct-encoded */
		if(*(start+offset) == '%' && 
		   offset+2 < len &&
		   isPartOfList(*(start+offset+1), hexdig, strlen(hexdig)-1) && 
		   isPartOfList(*(start+offset+2), hexdig, strlen(hexdig)-1)){
			offset += 3;
		}
		/* Test sub-delim */
		else if(isPartOfList(*(start+offset), sub_delim, strlen(sub_delim))){
			offset += 1;
		}
		/* Test unreserved */
		else if(isPartOfList(*(start+offset), unreserved, strlen(unreserved))){
			offset += 1;
		}
		/* Test ':' */
		else if(*(start+offset) == ':'){
			offset += 1;
		}
		else{
			return FALSE;
		}
	}

	/* Tous les caractères appartiennent à des listes acceptées */
	return TRUE;
}


int isComment(char *start, int len, rulename *parent_node){

	int offset = 0,
	    comment_len;

	while(offset < len){

		/* Test quoted-pair */
		if(*(start+offset) == 92 &&
		   (*(start+offset) == ' ' || *(start+offset) == '\t' ||
		   (*(start+offset) >= '!' && *(start+offset) <= '~') ||	/* Test VCHAR */
		   (*(start+offset) >= 128 && *(start+offset) <= 255))){	/* Test obs-text */
		   	offset += 2;
		}
		/* Test c-text */
		else if(*(start+offset) == ' ' || *(start+offset) == '\t' ||
			(*(start+offset) >= '!' && *(start+offset) <= 39) ||	/* Test %x21-27 */
			(*(start+offset) >= '*' && *(start+offset) <= '[') ||	/* Test %x2A-5B */
			(*(start+offset) >= ']' && *(start+offset) <= '~') ||	/* Test %x5D-7E */
   		        (*(start+offset) >= 128 && *(start+offset) <= 255)){	/* Test obs-text */
			offset += 1;
		}
		/* Test comment */
		else if(*(start+offset) == '('){
			/* Parenthèse fermante manquante */
			if((comment_len = detectDelim(start+offset, len-offset, ')')) == NOT_FOUND){
				return FALSE;
			}
			/* Sous-champ comment invalide */
			if((comment_len = detectDelim(start+offset, len-offset, ')')) != NOT_FOUND &&
			   !splitLikeComment(start+offset, len-offset, parent_node)){
				return FALSE;
			}
			offset += comment_len;
		}
		/* Invalid char */
		else{
			return FALSE;
		}
	}

	/* Tous les caractères appartiennent à des listes acceptées */
	return TRUE;
}
