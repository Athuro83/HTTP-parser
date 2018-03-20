#ifndef __SPLIT_H__
#define __SPLIT_H__

/* == Protoypes == */


/* Découpe le message HTTP en :
 * 	- start-line
 * 	- des headers (de 0 à n)
 * 	- un body (éventuellement)
 * Arrêt à la fin du message
 */
int splitHTTPMessage(char *start, int len);


/* Découpe la première ligne (start-line ou request-line) en :
 * 	- method
 * 	- request-target
 * 	- HTTP-version
 * Arrêt sur CRLF
 */
int splitStartLine(char *start, int len);


int splitRequestTarget(char *start, int len);


/* Donne le nb de carac entre le carac de départ et le premier ' ' rencontré */
int detectWS(char *start);


/* Donne le nb de carac entre le carac de départ et le premier CRLF rencontré */
int detectCRLF(char *start);
#endif
