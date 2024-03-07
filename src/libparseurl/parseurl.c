/*

	libparseurl
	(c) 2024 Copyright Clinton Webb

	Contact:
		Clinton Webb
		webb.clint@gmail.com

	This is a small and simple library with functions that are useful in retrieving parts of information about a URL.

	It is released under GPL v2 or later license.  Details are included in the LICENSE file.

*/

#include "parseurl.h"

#include <stdio.h>
#include <stdbool.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LEN		2048

// The following entries will be used to track the progress when iterating through the URL.
#define IS_PRE			0
#define IS_PROT_CHAR	1
#define IS_PROT			2
#define IS_SLASH1		4
#define IS_SLASH2		5
#define IS_AT			6
#define IS_HOST_COLON	7
#define IS_HOST_SLASH	8
#define IS_PATH			9
#define IS_Q			10
#define IS_HASH			11


static inline int check_alpha(char ch)
{
	if ((ch >= 'A' && ch <= 'Z') ||
		(ch >= 'a' && ch <= 'z') )
	{ return true; }
	else { return false; }
}

static inline int check_num(char ch)
{
	if (ch >= '0' && ch <= '9') { return true; }
	else { return false; }
}

static inline int check_min(char ch)
{
	if ( check_alpha(ch) || check_num(ch) ||
		ch == '+' ||
		ch == '.' ||
		ch == '-')
	{ return true; }
	else { return false; }
}

static inline int check_main(char ch)
{
	if ( check_min(ch) ||
		ch == '+' ||
		ch == '.' ||
		ch == '-' ||
		ch == '!' ||
		ch == '$' ||
		ch == '&' ||
		ch == '\'' ||
		ch == '@' ||
		ch == '(' ||
		ch == ')' ||
		ch == '*' ||
		ch == ',' ||
		ch == ';' ||
		ch == '=' )
	{ return true; }
	else { return false; }
}

static inline int check_path(char ch)
{
	if ( check_main(ch) ||
		ch == '/' )
	{ return true; }
	else { return false; }
}


int url_isvalid(char *url)
{
	const int fail = false;
	const int ok = true;
	int result = ok;

	if (url == NULL) { result = fail; }
	else {
		int len = strlen(url);
		assert(len >= 0);

		// printf("len: %d\n", len);

		if (len == 0 || len > MAX_URL_LEN) { result = fail; }
		else {
			// track the progress of iterating through the url protocol.
			int pos = 0;

			// 'info' indicates what section of the protocol has completed.
			int info = IS_PRE;
			char *pre = NULL;

			int i = 0;
			char *next = url;
			while ( result == ok && i < len) {

				// printf("Checking (%d): '%c'\n", info, *next);

				switch (info) {
					case IS_PRE:
						// the first character in the protocol needs to be a Letter.
						if (check_alpha(*next)) { info = IS_PROT_CHAR; }
						else 					{ result = fail; }
						break;
					case IS_PROT_CHAR:
						if (*next == ':') 		{ info = IS_PROT; }
						else if ( !check_min(*next) ) {
							result = fail;
						}
						break;
					case IS_PROT:
						if (*next == '/') { info = IS_SLASH1; }
						else if ( check_main(*next) ) { info = IS_PATH; }
						else { result = fail; }
						break;
					case IS_SLASH1:
						if (*next == '/') { info = IS_SLASH2; }
						else { result = fail; }
						break;
					case IS_SLASH2:
						// at this point we dont know if it is HOST info, or USER info... will just keep progressing until we hit a special character.
						if (*next == '@') { info = IS_AT; }
						else if (*next == ':') { info = IS_HOST_COLON; }
						else if ( !check_main(*next) ) {
							result = fail;
						}
						break;
					case IS_AT:
						if (*next == ':') { info = IS_HOST_COLON; }
						else if ( !check_main(*next) ) {
							result = fail;
						}
						break;
					case IS_HOST_COLON:
						if (*next == '/') { info = IS_HOST_SLASH; }
						else if (*next == '#') { info = IS_HASH; }
						else if ( !check_num(*next) ) {
							result = fail;
						}
						break;
					case IS_HOST_SLASH:
						if (*next == '?') { info = IS_Q; }
						else if (*next == '#') { info = IS_HASH; }
						else if ( !check_path(*next) ) {
							result = fail;
						}
						break;
					case IS_Q:
						if (*next == '#') { info = IS_HASH; }
						else if ( !check_main(*next) ) {
							result = fail;
						}
						break;
					case IS_HASH:
						if ( !check_main(*next) ) {
							result = fail;
						}
						break;
					default:
						result = fail;
				}

				next++;
				i ++;
			}
		}
	}

	return (result);
}


// given a URL, return an allocated string containing the hostname.
// On failure, return a NULL.
char * url_gethost(char *url)
{
	char *host = NULL;
	int i, len, tok;
	int start, finish;

	assert(url != NULL);
	len = strlen(url);
	assert(len > 0);

	start = 0;
	finish = 0;
	tok = 0;
	for(i=0; i<len && tok<3; i++) {
		if (url[i] == '/') {
			tok++;

			if (tok == 2) {
				assert(start == 0);
				assert((i+1) < len);
				start = i + 1;
			}
		}
		else if (url[i] == ':' && tok == 2) {
			tok++;
			assert(tok == 3);
		}
		else if (tok == 2) {
			finish ++;
		}
	}

	assert(start > 0);
	assert(start < i);
	assert(finish >= 0);
	assert(finish < len);
	assert(host == NULL);

	if (finish > 0) {

		host = (char *) malloc(finish + 1);
		assert(host != NULL);
	
		strncpy(host, &url[start], finish);
		host[finish] = '\0';
	}
	
	return(host);
}


// given a URL, return an allocated string containing the full path of the URL
// (that is used during an HTTP Get request).
char * url_getpath(char *url)
{
	char *path = NULL;
	int i, len, tok;
	int start, finish;

	assert(url != NULL);
	len = strlen(url);
	assert(len > 0);

	start = 0;
	finish = 0;
	tok = 0;
	for(i=0; i<len && tok<3; i++) {
		if (url[i] == '/') {
			tok++;

			if (tok == 3) {
				assert(start == 0);
				start = i;
			}
		}
	}

	if (start == 0) {
		// No path was specified, so return nothing.
		return(NULL);
	}

	assert(tok <= 3);
	assert(start > 0);
	assert(start < i);
	assert(finish == 0);
	assert(path == NULL);

	finish = len - start;
	if (finish > 0) {

		path = (char *) malloc(finish + 1);
		assert(path != NULL);
	
		strncpy(path, &url[start], finish);
		path[finish] = '\0';
	}
	
	return(path);
}


char * url_getfile(char *url)
{
	char *file = NULL;
	int i, len, tok;
	int start, finish;

	assert(url != NULL);
	len = strlen(url);
	assert(len > 0);

	start = 0;
	finish = 0;
	tok = 0;
	for(i=0; i<len; i++) {
		if (url[i] == '/') {
			tok++;

			if (tok >= 3) {
				start = i + 1;
				finish = 0;
			}
		}
		else if (tok > 3) {
			if (url[i] == '?') { i=len; }
			else { finish ++; }
		}
	}

	assert(file == NULL);
	
	if (start > 0 && len > start && finish > 0) {
		file = (char *) malloc(finish+1);
		assert(file != NULL);
		
		strncpy(file, &url[start], finish);
		file[finish] = '\0';
	}
	
	return(file);
}



char * url_getprotocol(char *url)
{
	char *prot = NULL;
	int i, len;
	int finish;

	assert(url != NULL);
	len = strlen(url);
	assert(len > 0);

	finish = 0;
	for(i=0; i<len; i++) {
		if (url[i] == ':' || url[i] == '/') {
			assert(i > 0);
			finish = i;
			i = len;
		}
	}

	assert(prot == NULL);
	if (finish > 0) {

		prot = (char *) malloc(finish+1);
		assert(prot != NULL);
	
		strncpy(prot, url, finish);
		prot[finish] = '\0';
	}
	
	return(prot);
}



int url_getport(char *url)
{
	int port;
	int i, len, tok;

	assert(url != NULL);
	len = strlen(url);
	assert(len > 0);

	tok = 0;
	port = 0;
	for(i=0; i<len; i++) {
		if (url[i] == '/') {
			tok ++;
			if (tok > 2) {
				i = len;	// break out of the loop
			}
		}
		else if (url[i] == ':' && tok == 2) {
			tok ++;
			assert(tok == 3);
		}
		else if (tok == 3 && (url[i] >= '0' && url[i] <= '9')) {
			assert(port >= 0);
			if (port > 0) port *= 10;
			port += (url[i] - '0');
		}
	}

	assert(port >= 0);
	return(port);
}



