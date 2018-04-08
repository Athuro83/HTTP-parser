/*===================================================
 *
 * 		Module Check :
 *
 * 	Regroupe les fonctions de vérification
 * 	syntaxique des champs, utilisant comme
 * 	référence la grammaire HTTP.
 *
 *=================================================== 	
 */

#ifndef __CHECK_H__
#define __CHECK_H__

/* ==[ Prototypes ]== */


/*==================================================
 *
 * 			Fonction isPartOfList
 *
 * 	But:
 * 	Vérifie qu'un caractère appartient ou non
 * 	à une liste de caractères fournie.
 *
 * 	Paramètres:
 * 	- c : Le caractère à examiner
 * 	- list : Pointeur sur le premier caractère
 * 	de la liste dans laquelle chercher c
 * 	- list_len : Taille de la liste dans laquelle
 * 	chercher
 *
 * 	Retour:
 * 	TRUE si le caractère est présent dans list.
 * 	FALSE sinon.
 *
 *==================================================
 */
int isPartOfList(char c, const char *list, int list_len);



/*==================================================
 *
 * 			Fonction isIPv4
 *
 * 	But:
 * 	Vérifie que le champ passé en paramètres
 * 	respecte la syntaxe de la rulename HTTP
 * 	"IPv4".
 *
 * 	Paramètres:
 * 	- start : Pointeur sur le caractère de départ
 * 	- len : Taille du champ à ne pas dépasser
 *
 * 	Retour:
 * 	- TRUE si le champ fourni est syntaxiquement
 * 	correct.
 * 	- FALSE sinon.
 *
 *==================================================
 */
int isIPv4(char *start, int len);



/*==================================================
 *
 * 			Fonction isRegname
 *
 * 	But:
 * 	Vérifie que le champ passé en paramètres
 * 	respecte la syntaxe de la rulename HTTP
 * 	"regname".
 *
 * 	Paramètres:
 * 	- start : Pointeur sur le caractère de départ
 * 	- len : Taille du champ à ne pas dépasser
 *
 * 	Retour:
 * 	- TRUE si le champ fourni est syntaxiquement
 * 	correct.
 * 	- FALSE sinon.
 *
 *==================================================
 */
int isRegname(char *start, int len);



/*==================================================
 *
 * 			Fonction isScheme
 *
 * 	But:
 * 	Vérifie que le champ passé en paramètres
 * 	respecte la syntaxe de la rulename HTTP
 * 	"scheme".
 *
 * 	Paramètres:
 * 	- start : Pointeur sur le caractère de départ
 * 	- len : Taille du champ à ne pas dépasser
 *
 * 	Retour:
 * 	- TRUE si le champ fourni est syntaxiquement
 * 	correct.
 * 	- FALSE sinon.
 *
 *==================================================
 */
int isScheme(char *start, int len);



/*==================================================
 *
 * 			Fonction isToken
 *
 * 	But:
 * 	Vérifie que le champ passé en paramètres
 * 	respecte la syntaxe de la rulename HTTP
 * 	"token".
 *
 * 	Paramètres:
 * 	- start : Pointeur sur le caractère de départ
 * 	- len : Taille du champ à ne pas dépasser
 *
 * 	Retour:
 * 	- TRUE si le champ fourni est syntaxiquement
 * 	correct.
 * 	- FALSE sinon.
 *
 *==================================================
 */
int isToken(char *start, int len);



/*==================================================
 *
 * 			Fonction isHTTPVers
 *
 * 	But:
 * 	Vérifie que le champ passé en paramètres
 * 	respecte la syntaxe de la rulename HTTP
 * 	"HTTP-version".
 *
 * 	Paramètres:
 * 	- start : Pointeur sur le caractère de départ
 * 	- len : Taille du champ à ne pas dépasser
 *
 * 	Retour:
 * 	- TRUE si le champ fourni est syntaxiquement
 * 	correct.
 * 	- FALSE sinon.
 *
 *==================================================
 */
int isHTTPVers(char *start, int len);



/*==================================================
 *
 * 			Fonction isSegment
 *
 * 	But:
 * 	Vérifie que le champ passé en paramètres
 * 	respecte la syntaxe de la rulename HTTP
 * 	"segment".
 *
 * 	Paramètres:
 * 	- start : Pointeur sur le caractère de départ
 * 	- len : Taille du champ à ne pas dépasser
 *
 * 	Retour:
 * 	- TRUE si le champ fourni est syntaxiquement
 * 	correct.
 * 	- FALSE sinon.
 *
 *==================================================
 */
int isSegment(char *start, int len);



/*==================================================
 *
 * 			Fonction isQuery
 *
 * 	But:
 * 	Vérifie que le champ passé en paramètres
 * 	respecte la syntaxe de la rulename HTTP
 * 	"query".
 *
 * 	Paramètres:
 * 	- start : Pointeur sur le caractère de départ
 * 	- len : Taille du champ à ne pas dépasser
 *
 * 	Retour:
 * 	- TRUE si le champ fourni est syntaxiquement
 * 	correct.
 * 	- FALSE sinon.
 *
 *==================================================
 */
int isQuery(char* start, int len);



/*==================================================
 *
 * 			Fonction isPort
 *
 * 	But:
 * 	Vérifie que le champ passé en paramètres
 * 	respecte la syntaxe de la rulename HTTP
 * 	"port".
 *
 * 	Paramètres:
 * 	- start : Pointeur sur le caractère de départ
 * 	- len : Taille du champ à ne pas dépasser
 *
 * 	Retour:
 * 	- TRUE si le champ fourni est syntaxiquement
 * 	correct.
 * 	- FALSE sinon.
 *
 *==================================================
 */
int isPort(char *start, int len);



/*==================================================
 *
 * 			Fonction isUserinfo
 *
 * 	But:
 * 	Vérifie que le champ passé en paramètres
 * 	respecte la syntaxe de la rulename HTTP
 * 	"userinfo".
 *
 * 	Paramètres:
 * 	- start : Pointeur sur le caractère de départ
 * 	- len : Taille du champ à ne pas dépasser
 *
 * 	Retour:
 * 	- TRUE si le champ fourni est syntaxiquement
 * 	correct.
 * 	- FALSE sinon.
 *
 *==================================================
 */
int isUserinfo(char *start, int len);



/*==================================================
 *
 * 			Fonction isComment
 *
 * 	But:
 * 	Vérifie que le champ passé en paramètres
 * 	respecte la syntaxe de la rulename HTTP
 * 	"comment".
 *
 * 	Paramètres:
 * 	- start : Pointeur sur le caractère de départ
 * 	- len : Taille du champ à ne pas dépasser
 *
 * 	Retour:
 * 	- TRUE si le champ fourni est syntaxiquement
 * 	correct.
 * 	- FALSE sinon.
 *
 *==================================================
 */
int isComment(char *start, int len, rulename *parent_node);

#endif
