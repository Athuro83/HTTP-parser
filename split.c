#include <stdio.h>
#include <stdlib.h>

#include "parseur.h"
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



int removeOWS(char **start, int h_len){

	int data_len = 0,
	    len = 0;

	/* On avance tant qu'il y a des espaces et qu'on a pas dépassé la fin du champ */
	while(len <= h_len &&
	      **start == ' '){
		*start += 1;
		len++;
	}

	/* On a trouvé le début du champ, on compte jusqu'au prochain espace ou bien la sortie du champ */
	while(len <= h_len &&
	      *(*start+data_len) != ' '){
		data_len++;
		len++;
	}

	return data_len;
}
