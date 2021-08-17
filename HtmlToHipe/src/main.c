#include <gumbo.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include "attr.h"
#include "tag.h"

/**
 * mygumbo_write_hipe - Write gumbo output of a HTML file as hipe client send
 *	instructions to a file
 * @g: gumbo output with 
 */
void mygumbo_write_hipe(GumboOutput *g, int fd)
{
	// Write the gumbo tags first so that tags can be located in hipe when
	// writing attributes.
	mygumbo_write_tags(g->root, fd);
	mygumbo_write_attr(g->root, fd);
}

/**
 * filesz - Get the size of a file in bytes.
 */
int filesz(int fd)
{
	struct stat s;
	
	if (fstat(fd, &s) == -1)
		return -1;
	return s.st_size;
}

/**
 * falloc - Dynamically allocate the whole of a file into a C string
 *
 * Return must be freed with free.
 */
char *falloc(int fd)
{
	char *s;
	int fsz;

	flock(fd, LOCK_EX);

	fsz  = filesz(fd);
	lseek(fd, 0, SEEK_SET);
	// TODO add null term until determine whether it's needed
	s = malloc((fsz+1)*sizeof(char));  
	s[fsz] = '\0';

	flock(fd, LOCK_UN);

	return s;
}

int main(void)
{
	int fd;
	char *html;
	GumboOutput *g;

	fd = open("../data/hipe_calc.html", O_RDONLY);
	html = falloc(fd);
	close(fd);
	// TODO how does gumbo parse a string, does it stop at a null term character
	// or some other special delimiter?
	g = gumbo_parse(html);  // TODO handle errors

	mygumbo_write_hipe(g, STDOUT_FILENO);

	gumbo_destroy_output(&kGumboDefaultOptions, g);
	free(html);  // Free last since buffer is supposed to live as long as gumbo is used.
	return 0;
}
