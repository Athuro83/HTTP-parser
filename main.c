#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "api.h" 
/// Incluez ici les fichiers d'entête nécessaires pour l'execution de ce programme.  
/// La fonction parseur doit être dans un autre fichier .c 
/// N'ajouter aucun autre code dans ce fichier. 
int main(int argc, char *argv[])
{
	char req[]="GET /cest/notre/projet HTTP/1.0\r\nHost:\t www.google.com\r\nUser-Agent: Wget/1.16 (linux-gnu)\r\nTransfer-Encoding: gzip;\ntar\r\nConnection: ,pouet, tumblr   ,onch\t,\r\n\r\n";
	if (argc != 2 ) { printf("usage: %s <rulename>\n",argv[0]); return 0; }
	if (parseur(req,strlen(req))) {
		_Token *r,*tok; 
		r=searchTree(NULL,argv[1]); 
		tok=r; 
		while (tok) {
			int l; 
			char *s; 
			s=getElementValue(tok->node,&l); 
			printf("FOUND [%.*s]\n",l,s);
			tok=tok->next; 
		}
		purgeElement(&r); 
	}
	else {
		return 0; 
	}
		return 1; 
}
