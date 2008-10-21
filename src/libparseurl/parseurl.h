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
	
	For example, the URL "http://rhokz.com/articles/12301/comments.html" will
	return a host of "rhokz.com".

	params:
		char *url   - URL that is to be parsed.

	returns:
		on success, a string containing the hostname portion of the url.
		on failure. a NULL.
		
*/
char * url_gethost(char *url);



/*
	url_getpath

	This function will parse an input string containing a valid URL, and
	determine the path (including filename), allocating memory and returning it.
	It is up to the caller to free the memory when it is no longer required.

	For example, the URL "http://rhokz.com/articles/12301/comments.html" will
	return a path of "/articles/12301/comments.html".

	params:
		char *url   - URL that is to be parsed.

	returns:
		on success, a string containing the path portion of the url.
		on failure. a NULL.
		
*/
char * url_getpath(char *url);




/*
	url_getprotocol

	This function will parse an input string containing a valid URL, and
	determine the protocol, allocating memory and returning it.
	It is up to the caller to free the memory when it is no longer required.

	For example, the URL "http://rhokz.com/articles/12301/comments.html" will
	return a protocol of "http".

	params:
		char *url   - URL that is to be parsed.

	returns:
		on success, a string containing the protocol portion of the url.
		on failure. a NULL.
		
*/
char * url_getprotocol(char *url);



/*
	url_getport

	This function will parse an input string containing a valid URL, and
	determine the port to use (if specified).  If no port is specified, it will
	attempt to return a port that would be specific to the protocol presented.

	For example, the URL "http://rhokz.com/articles/12301/comments.html" will
	return a port of 80, because that is the default port for the 'http' protocol.

	If the protocol is not recognised, then it will return a port of 0.

	params:
		char *url   - URL that is to be parsed.

	returns:
		on success, an integer which is the default port for the specified protocol.
		on failure. a 0.
		
*/
int url_getport(char *url);




#endif
