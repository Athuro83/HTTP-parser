#ifndef __SPLIT_H__
#define __SPLIT_H__

/* == Protoypes == */

/* Donne le nb de carac entre le carac de départ et le premier ' ' rencontré */
int detectWS(char *start, int r_len);


/* Donne le nb de carac entre le carac de départ et le premier CRLF rencontré */
int detectCRLF(char *start, int r_len);


/* Donne le nb de carac entre le carac de départ et le premier ':' rencontré */
int detectColon(char *start, int r_len);


/* Donne le nb de carac entre le carac de départ et le premier '?' rencontré */
int detectInterrogationPoint(char *start, int r_len);


/* Donne le nb de carac entre le carac de départ et le premier '@' rencontré */
int detectArobase(char *start, int r_len);


/* Permet d'enlever les espaces potentiels :
 * Positionne le pointeur *start sur le carac de début de champ, et retourne le nb de carac du champ */
int removeOWS(char **start, int h_len);


/* Tente de découper la request-target selon la rulename 'asterik-form', retourne TRUE et crée le noeud si
 * on y arrive, retourne FALSE sinon */
int splitLikeAsteriskForm(char *start, int r_len, rulename *parent_node);


/* Tente de découper la request-target selon la rulename 'origin-form'.
 * Retourne TRUE et crée le noeud si on y arrive, FALSE sinon. */
int splitLikeOriginForm(char *start, int r_len, rulename *parent_node);


/* Tente de découper la request-target selon la rulename 'absolute-form'.
 * Retourne TRUE et crée le noeud si on y arrive, FALSE sinon. */
int splitLikeAbsoluteForm(char *start, int r_len, rulename *parent_node);


/* Tente de découper la request-target selon la rulename 'absolute-form'.
 * Retourne TRUE et crée le noeud si on y arrive, FALSE sinon. */
int splitLikeAuthorityForm(char *start, int r_len, rulename *parent_node);


/* Tente de récupérer un champ 'query' dont le début est signalé par un délimiteur '?'.
 * Renvoie le nombre de caractères entre le start et le délimiteur + crée le noeud associé s'il y arrive,
 * NOT_FOUND sinon */
int recoverQuery(char *start, int r_len, rulename *parent_node);

/* Tente de récupérer un champ 'query' dont le début est signalé par un délimiteur '?'.
 * Renvoie la longueur du champ récupéré + crée le noeud associé s'il y arrive,
 * NOT_FOUND sinon */
int recoverUserinfo(char *start, int r_len, rulename *parent_node);

/* Tente de récupérer un champ 'port' dont le début est signalé par un délimiteur ':'.
 * Renvoie le nombre de caractères entre le start et le délimiteur + crée le noeud associé s'il y arrive,
 * NOT_FOUND sinon */
int recoverPort(char *start, int r_len, rulename *parent_node);
#endif
