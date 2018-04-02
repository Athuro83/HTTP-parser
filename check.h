#ifndef __CHECK_H__
#define __CHECK_H__

/* ==[ Prototypes ]== */

int isPartOfList(char c, const char *list, int list_len);


int isIPv4(char *start, int len);


int isRegname(char *start, int len);


int isScheme(char *start, int len);


int isMethod(char *start, int len);


int isHTTPVers(char *start, int len);


int isSegment(char *start, int len);


int isQuery(char* start, int len);


int isPort(char *start, int len);


int isUserinfo(char *start, int len);

#endif
