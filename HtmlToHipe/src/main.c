#include <gumbo.h>
#include <unistd.h>
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

int main(void)
{
	// TODO how does gumbo parse a string, does it stop at a null term character
	// or some other special delimiter?
	GumboOutput *g = gumbo_parse("TODO Michael write a very simple HTML file here");

	// TODO handle error on parsing Gumbo Output
	mygumbo_write_hipe(g, STDOUT_FILENO);

	gumbo_destroy_output(&kGumboDefaultOptions, g);
	return 0;
}
