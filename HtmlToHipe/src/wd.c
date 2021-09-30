#include "wd.h"

// Length of string "http://"
#define HTTP_LEN 7

char *tmpwd = NULL;
char *htmlwd = NULL;
int rootlen;  // Length of filepath rooted at init time.

/**
 * fpath_rm_last - Remove the last directory/file from a filepath
 * 
 * Assumes there is a last diectory/file to remove from the path. Sets rootlen.
 * Example: foo/bar.txt becomes foo/
 */
void fpath_rm_last(char *fpath)
{
	int n = strlen(fpath);

	for (int i = n-1; i >= 0; --i) {
		if (fpath[i] == '/') {
			fpath[i+1] = '\0';
			rootlen = i+1;
			break;
		}
	}
}

void wdinit(char *fpath)
{
	htmlwd = malloc(PATH_MAX*sizeof(char));
	
	// Assumes the input filepath isn't null and has at least 1 character.
	if (fpath[0] == '/') {
		htmlwd[0] = '\0';
		strcat(htmlwd, fpath);  // Filepath is already absolute.
	} else
		htmlwd = realpath(fpath, htmlwd);  // Get an absolute filepath of len PATH_MAX.
	fpath_rm_last(htmlwd);
}

void wdpushcat(char *fpath)
{
	bool http;
	int n = strlen(fpath);

	if (n >= HTTP_LEN) {
		if (strncmp(fpath, "http://", HTTP_LEN) == 0)
			http = true;
		else if (n >= HTTP_LEN+1 && strncmp(fpath, "https://", HTTP_LEN+1) == 0) 
			http = true;
		else
			http = false;
	} else 
		http = false;
	if (fpath[0] == '/' || http) {
		// Path is already absolute or http (link) so don't need to use workaround.
		tmpwd = htmlwd;
		htmlwd = fpath;
	} else  
		strncat(htmlwd, fpath, PATH_MAX);
}

void wdpopcat(void)
{
	if (tmpwd) {
		htmlwd = tmpwd;
		tmpwd = NULL;
	} else
		htmlwd[rootlen] = '\0';
}

void wdfree(void)
{
	if (htmlwd)
		free(htmlwd);
}
