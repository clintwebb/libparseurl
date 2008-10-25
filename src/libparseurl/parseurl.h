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

char * url_getprotocol(char *url);
char * url_gethost(char *url);
char * url_getpath(char *url);
char * url_getfile(char *url);
int    url_getport(char *url);

#endif
