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




char * url_getprotocol(char *url)
{
	assert(0);
	return(NULL);
}



int url_getport(char *url)
{
	assert(0);
	return(0);
}



