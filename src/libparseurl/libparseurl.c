
#include "parseurl.h"

// given a URL, return an allocated string containing the hostname. 
char * p2_gethostfromurl(char *url)
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


