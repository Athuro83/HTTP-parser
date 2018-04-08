/*===================================================
 *
 * 		Module Split :
 *
 * 	Regroupe les fonctions de détection
 * 	de délimiteurs et division de champ
 * 	en sous-champs selon les règles de
 * 	la grammaire HTTP.
 *
 *=================================================== 	
 */

#ifndef __SPLIT_H__
#define __SPLIT_H__

/* == Protoypes == */

/*==================================================
 *
 * 			Fonction detectOWS
 *
 * 	But:
 * 	Donne le nombre de caractères entre le
 * 	caractère de départ et le premier OWS(' ' ou
 * 	'\t') rencontré.
 *
 * 	Paramètres:
 * 	- start : Pointeur sur le caractère de départ
 * 	- r_len : Taille du champ à ne pas dépasser
 *
 * 	Retour:
 * 	- Le nombre de caractères entre start et le
 * 	premier OWS si il a été trouvé.
 * 	- NOT_FOUND s'il n'a pas été trouvé.
 *
 *==================================================
 */
int detectOWS(char *start, int r_len);


/*==================================================
 *
 * 			Fonction detectCRLF
 *
 * 	But:
 * 	Donne le nombre de caractères entre le
 * 	caractère de départ et le premier CRLF("\r\n")
 * 	rencontré.
 *
 * 	Paramètres:
 * 	- start : Pointeur sur le caractère de départ
 * 	- r_len : Taille du champ à ne pas dépasser
 *
 * 	Retour:
 * 	- Le nombre de caractères entre start et le
 * 	premier CRLF s'il a été trouvé.
 * 	- NOT_FOUND sinon.
 *
 *==================================================
 */
int detectCRLF(char *start, int r_len);


/*==================================================
 *
 * 			Fonction detectDelim
 *
 * 	But:
 * 	Donne le nombre de caractères entre le
 * 	caractère de départ et le premier caractère
 * 	délimiteur rencontré.
 *
 * 	Paramètres:
 *  	- start : Pointeur sur le caractère de départ
 * 	- r_len : Taille du champ à ne pas dépasser
 * 	- delim : Le caractère délimiteur recherché
 *
 * 	Retour:
 *  	- Le nombre de caractères entre start et le
 * 	premier délimiteur s'il a été trouvé.
 * 	- NOT_FOUND sinon.
 *
 *
 *==================================================
 */
int detectDelim(char *start, int r_len, char delim);


/*==================================================
 *
 * 			Fonction removeOWS
 *
 * 	But:
 * 	Permet d'enlever les OWS potentiels d'une
 * 	configuration comme :
 * 			OWS value OWS
 * 	Positionne le pointeur *start sur le
 * 	premier caractère de "value", et retourne
 * 	le nombre de caractères de "value".
 *
 * 	Paramètres:
 * 	- start : Adresse du pointeur sur le premier
 * 	caractère du champ.
 * 	- h_len : Taille du champ à ne pas dépasser
 *
 * 	Retour:
 * 	- Le nombre de caractère du champ.
 *
 *==================================================
 */
int removeOWS(char **start, int h_len);


/*==================================================
 *
 * 			Fonction splitLikeAsteriskForm
 *
 * 	But:
 *	Tente de découper la request-target selon la
 *	rulename HTTP "asterik-form".
 *
 * 	Paramètres:
 *  	- start : Pointeur sur le caractère de départ
 * 	- r_len : Taille du champ à ne pas dépasser
 *	- parent_node : Pointeur sur le noeud parent
 *	dans l'arbre de dérivation
 *
 * 	Retour:
 * 	- TRUE si le découpage est un succès. Entraîne
 * 	la création et l'attache des noeuds correspondants.
 * 	- FALSE si le découpage a échoué pour une
 * 	raison quelconque.
 *
 *==================================================
 */
int splitLikeAsteriskForm(char *start, int r_len, rulename *parent_node);


/*==================================================
 *
 * 			Fonction splitLikeOriginForm
 *
 * 	But:
 *	Tente de découper la request-target selon la
 *	rulename 'origin-form'.
 *
 * 	Paramètres:
 *   	- start : Pointeur sur le caractère de départ
 * 	- r_len : Taille du champ à ne pas dépasser
 *	- parent_node : Pointeur sur le noeud parent
 *	dans l'arbre de dérivation
 *
 *
 * 	Retour:
 * 	- TRUE si le découpage est un succès. Entraîne
 * 	la création et l'attache des noeuds correspondants.
 * 	- FALSE si le découpage a échoué pour une
 * 	raison quelconque.
 *
 *==================================================
 */
int splitLikeOriginForm(char *start, int r_len, rulename *parent_node);


/*==================================================
 *
 * 			Fonction splitLikeAbsoluteForm
 *
 * 	But:
 *	Tente de découper la request-target selon la
 *	rulename 'absolute-form'.
 *
 * 	Paramètres:
 *   	- start : Pointeur sur le caractère de départ
 * 	- r_len : Taille du champ à ne pas dépasser
 *	- parent_node : Pointeur sur le noeud parent
 *	dans l'arbre de dérivation
 *
 *
 * 	Retour:
 * 	- TRUE si le découpage est un succès. Entraîne
 * 	la création et l'attache des noeuds correspondants.
 * 	- FALSE si le découpage a échoué pour une
 * 	raison quelconque.
 *
 *==================================================
 */
int splitLikeAbsoluteForm(char *start, int r_len, rulename *parent_node);


/*==================================================
 *
 * 			Fonction splitLikeAuthorityForm
 *
 * 	But:
 *	Tente de découper la request-target selon la
 *	rulename 'absolute-form'.
 *
 * 	Paramètres:
 *   	- start : Pointeur sur le caractère de départ
 * 	- r_len : Taille du champ à ne pas dépasser
 *	- parent_node : Pointeur sur le noeud parent
 *	dans l'arbre de dérivation
 *
 * 	Retour:
 * 	- TRUE si le découpage est un succès. Entraîne
 * 	la création et l'attache des noeuds correspondants.
 * 	- FALSE si le découpage a échoué pour une
 * 	raison quelconque.
 *
 *==================================================
 */
int splitLikeAuthorityForm(char *start, int r_len, rulename *parent_node);


/*==================================================
 *
 * 			Fonction recoverQuery
 *
 * 	But:
 *	Tente de récupérer un champ 'query' dont le
 *	début est signalé par un délimiteur '?'.
 *
 * 	Paramètres:
 *	- start : Pointeur sur le caractère de départ
 * 	- r_len : Taille du champ à ne pas dépasser
 *	- parent_node : Pointeur sur le noeud parent
 *	dans l'arbre de dérivation
 *
 * 	Retour:
 * 	- Le nombre de caractères entre start et le
 * 	délimiteur s'il a été trouvé et que le champ
 * 	est syntaxiquement correct.
 * 	Ajoute également le noeud à l'arbre.
 * 	- NOT_FOUND sinon.
 *
 *==================================================
 */
int recoverQuery(char *start, int r_len, rulename *parent_node);


/*==================================================
 *
 * 			Fonction recoverUserinfo
 *
 * 	But:
 *	Tente de récupérer un champ 'userinfo' dont le
 *	début est signalé par un délimiteur '@'.
 *
 * 	Paramètres:
 *	- start : Pointeur sur le caractère de départ
 * 	- r_len : Taille du champ à ne pas dépasser
 *	- parent_node : Pointeur sur le noeud parent
 *	dans l'arbre de dérivation
 *
 * 	Retour:
 * 	- Le nombre de caractères du champ si le
 * 	délimiteur a été trouvé et que le champ
 * 	est syntaxiquement correct.
 * 	Ajoute également le noeud à l'arbre.
 * 	- NOT_FOUND sinon.
 *
 *==================================================
 */
int recoverUserinfo(char *start, int r_len, rulename *parent_node);


/*==================================================
 *
 * 			Fonction recoverPort
 *
 * 	But:
 *	Tente de récupérer un champ 'port' dont le
 *	début est signalé par un délimiteur '@'.
 *
 * 	Paramètres:
 *	- start : Pointeur sur le caractère de départ
 * 	- r_len : Taille du champ à ne pas dépasser
 *	- parent_node : Pointeur sur le noeud parent
 *	dans l'arbre de dérivation
 *
 * 	Retour:
 * 	- Le nombre de caractères entre start et le
 * 	délimiteur s'il a été trouvé et que le champ
 * 	est syntaxiquement correct.
 * 	Ajoute également le noeud à l'arbre.
 * 	- NOT_FOUND sinon.
 *
 *==================================================
 */
int recoverPort(char *start, int r_len, rulename *parent_node);


/*==================================================
 *
 * 			Fonction splitHost
 *
 * 	But:
 * 	Réalise le découpage et la vérification du champ
 * 	valeur d'un header "Host".
 *
 * 	Paramètres:
 *	- start : Pointeur sur le caractère de départ
 * 	- r_len : Taille du champ à ne pas dépasser
 *	- parent_node : Pointeur sur le noeud parent
 *	dans l'arbre de dérivation
 *
 * 	Retour:
 * 	- TRUE si le champ est syntaxiquement correct.
 * 	Ajoute également les noeuds correspondants à
 * 	l'arbre.
 * 	- FALSE sinon.
 *
 *==================================================
 */
int splitHost(char *start, int r_len, rulename *parent_node);


/*==================================================
 *
 * 			Fonction splitConnection
 *
 * 	But:
 * 	Réalise le découpage et la vérification du champ
 * 	valeur d'un header "Connection".
 *
 * 	Paramètres:
 *	- start : Pointeur sur le caractère de départ
 * 	- r_len : Taille du champ à ne pas dépasser
 *	- parent_node : Pointeur sur le noeud parent
 *	dans l'arbre de dérivation
 *
 * 	Retour:
 * 	- TRUE si le champ est syntaxiquement correct.
 * 	Ajoute également les noeuds correspondants à
 * 	l'arbre.
 * 	- FALSE sinon.
 *
 *==================================================
 */
int splitConnection(char *start, int r_len, rulename *parent_node);


/*==================================================
 *
 * 			Fonction splitUserAgent
 *
 * 	But:
 * 	Réalise le découpage et la vérification du champ
 * 	valeur d'un header "User-Agent".
 *
 * 	Paramètres:
 *	- start : Pointeur sur le caractère de départ
 * 	- r_len : Taille du champ à ne pas dépasser
 *	- parent_node : Pointeur sur le noeud parent
 *	dans l'arbre de dérivation
 *
 * 	Retour:
 * 	- TRUE si le champ est syntaxiquement correct.
 * 	Ajoute également les noeuds correspondants à
 * 	l'arbre.
 * 	- FALSE sinon.
 *
 *==================================================
 */
int splitUserAgent(char *start, int r_len, rulename *parent_node);


/*==================================================
 *
 * 			Fonction splitLikeProduct
 *
 * 	But:
 * 	Réalise le découpage et la vérification d'un
 * 	champ de type "product".
 *
 * 	Paramètres:
 *	- start : Pointeur sur le caractère de départ
 * 	- r_len : Taille du champ à ne pas dépasser
 *	- parent_node : Pointeur sur le noeud parent
 *	dans l'arbre de dérivation
 *
 * 	Retour:
 * 	- TRUE si le champ est syntaxiquement correct.
 * 	Ajoute également les noeuds correspondants à
 * 	l'arbre.
 * 	- FALSE sinon.
 *
 *==================================================
 */
int splitLikeProduct(char *start, int r_len, rulename *parent_node);


/*==================================================
 *
 * 			Fonction splitLikeComment
 *
 * 	But:
 * 	Réalise le découpage et la vérification d'un
 * 	champ de type "comment".
 *
 * 	Paramètres:
 *	- start : Pointeur sur le caractère de départ
 * 	- r_len : Taille du champ à ne pas dépasser
 *	- parent_node : Pointeur sur le noeud parent
 *	dans l'arbre de dérivation
 *
 * 	Retour:
 * 	- TRUE si le champ est syntaxiquement correct.
 * 	Ajoute également les noeuds correspondants à
 * 	l'arbre.
 * 	- FALSE sinon.
 *
 *==================================================
 */
int splitLikeComment(char *start, int r_len, rulename *parent_node);

#endif
