#include <stdio.h>
#include <stdlib.h>

#include "split.h"


int detectWS(char *start){

	int len = 0;

	/* On avance dans la chaîne jusqu'à trouver un ' ' ou la fin de la chaîne */
	while(*(start+len) != '\0' &&
	      *(start+len) != ' '){
		len++;
	}

	if(*(start+len) == ' '){
		/* On renvoie le nombre de caractères du départ jusqu'à l'espace exclu */
		return len;
	}
	else{
		return -1;
	}
}



int detectCRLF(char *start){

	int len = 0;

	while(*(start + len) != '\0' &&
	      !(*(start+len) == '\r' && *(start+len+1) == '\n')){
		len++;
	}

	if(*(start+len) == '\0'){
		return -1;
	}
	else{
		return len;
	}
}
