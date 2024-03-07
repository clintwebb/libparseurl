#include <parseurl.h>

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) 
{
	// char *url = "http://rhokz.com:8080/articles/";
	// char *url = "http://rhokz.com:8080/articles/file.html";
	// char *url = "http://rhokz.com:8080/articles/file.html?user=freddy#abc123";
	// char *url = "http://127.0.0.1";
	char *url = "https://john.doe@www.example.com:8080/forum/questions/hope.html?tag=networking&order=newest#top";


	printf("\n");
	printf("URL: %s\n", url);
	if (url_isvalid(url)) {
		char *prot = url_getprotocol(url);
		char *host = url_gethost(url);
		char *path = url_getpath(url);
		char *file = url_getfile(url);
		int port = url_getport(url);

		printf("Protocol: %s\n", prot);
		printf("Host: %s\n", host);
		printf("Path: %s\n", path);
		printf("File: %s\n", file);
		printf("Port: %d\n", port);
		printf("\n");

		if (prot) free(prot);
		if (host) free(host);
		if (path) free(path);
		if (file) free(file);
	}
	else {
		printf("INVALID\n");
	}

	return(0);
}
