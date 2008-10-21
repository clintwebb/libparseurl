#include <parseurl.h>

#include <stdio.h>

int main(int argc, char **argv) 
{
	char *url = "http://rhokz.com/articles/file.html";
	
	char *host = url_gethost(url);
	char *path = url_getpath(url);

	printf("\n");
	printf("URL: %s\n", url);
	printf("Host: %s\n", host);
	printf("Path: %s\n", path);
	printf("\n");

	return(0);
}
