/*

	libparseurl
	(c) Copyright Hyper-Active Systems, Australia

	Contact:
		Clinton Webb
		webb.clint@gmail.com

	This is a small and simple library with functions that are useful in retrieving parts of information about a URL.

	It is released under GPL v2 or later license.  Details are included in the LICENSE file.

*/



#include "parseurl.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>


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



