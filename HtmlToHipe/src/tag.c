#include "tag.h"

// TODO rm this (just using for debugging)
int depth = 0;

void mygumbo_write_tags_aux(GumboNode *n, int fd)
{
	if (n->type == GUMBO_NODE_ELEMENT) {
		GumboElement *e = (GumboElement *)&n->v;

		// TODO do something with element
		for (int i = 0; i < depth; ++i)
			printf("  ");
		printf("tag=%d\n", e->tag);

		// Recurse on children elements.
		for (int i = 0; i < e->children.length; ++i)  {
			++depth;
			mygumbo_write_tags_aux(e->children.data[i], fd);
			--depth;
		}
	}
}

void mygumbo_write_tags(GumboNode *root, int fd)
{
	// Wrapping just so doesn't have name root in param.
	mygumbo_write_tags_aux(root, fd);
}
