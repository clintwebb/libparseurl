/*

	libparseurl
	(c) Copyright Hyper-Active Systems, Australia

	Contact:
		Clinton Webb
		webb.clint@gmail.com

	This is a small and simple library with functions that are useful in retrieving parts of information about a URL.

	It is released under GPL v2 or later license.  Details are included in the LICENSE file.

*/

#ifndef __PARSEURL_H
#define __PARSEURL_H


/*
	url_gethost

	This function will parse an input string containing a valid URL, and
	determine the host, allocating memory and returning it.  It is up to the
	caller to free the memory when it is no longer required.

	params:
		char *url   - URL that is to be parsed.

	returns:
		on success, a string containing the hostname portion of the url.
		on failure. a NULL.
		
*/
char * url_gethost(char *url);






#endif
