#include <stdio.h>
#include <stdlib.h>

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



int detectCRLF(char *start){

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
