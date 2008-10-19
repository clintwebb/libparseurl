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


// given a URL, return an allocated string containing the hostname.  On failure, return a NULL.
char * url_gethost(char *url)
{
	char *host = NULL;
	int i, j, l, t;

	assert(url != NULL);
	l = strlen(url);
	host = (char *) malloc(l - 6);
	assert(host != NULL);

	for(i=0,t=0,j=0; i<l && t<3; i++) {
		if (url[i] == '/') {
			t++;
		}
		else if (t == 2) {
			host[j] = url[i];
			j++;
		}
	}

	if (j == 0) {
		assert(host != NULL);
		free(host);
		host = NULL;
	}
	else {
		// resize the URL.  If j is 0, then we free host, and set it to NULL.
		assert(host != NULL);
		assert(t == 3 || t == 2);
		assert(j < l);
		assert(j > 0);
		host[j] = '\0';
		host = (char *) realloc(host, j+1);
		assert(host != NULL);
	}
	
	return(host);
}


