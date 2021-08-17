#include "tag.h"

/**
 * mygumbo_count_nodes - Count the number of nodes in a gumbo tree rooted at a node
 */
static int mygumbo_count_nodes(GumboNode *n)
{
	if (n->type == GUMBO_NODE_ELEMENT) {
		GumboElement *e;
		int sum;

		e = (GumboElement *)&n->v;
		sum = 0;

		if (e->children.length) {
			for (int i = 0; i < e->children.length; ++i)
				sum += mygumbo_count_nodes(e->children.data[i]);
		}
		return 1+sum;
	}
	return 0;
}

/**
 * neltchildren - Get the number of children of a gumbo element that are children
 */
static int neltchildren(GumboElement *e)
{
	GumboNode *n;
	int cnt = 0;

	for (int i = 0; i < e->children.length; ++i) {
		n = (GumboNode *)e->children.data[i];

		if (n->type == GUMBO_NODE_ELEMENT)
			++cnt;
	}
	return cnt;
}

/**
 * @curid: current node's ID
 */
static bool write_body_tags_aux(GumboNode *n, int fd, int curid)
{
	if (n->type == GUMBO_NODE_ELEMENT) {
		int i, j;
		GumboElement *e = (GumboElement *)&n->v;

		// 0th ID is for the body tag. When locs[i] evaluates to 0 the tag is appended to the body
		// element by default.
		if (curid > 0) {
			dprintf(fd, "\tloc = hipe_send(session, HIPE_OP_APPEND_TAG, 0, locs[%d], \"%s\");\n",
				curid, gumbo_normalized_tagname(e->tag));
		}

		// Set each node's parent location.
		for (i = 0, j = 0; i < e->children.length; ++i) {
			n = (GumboNode *)e->children.data[i];
			if (n->type == GUMBO_NODE_ELEMENT)
				dprintf(fd, "\tplocs[%d] = loc;\n", ++j+curid);
		}
		for (i = 0, j = 1; i < e->children.length; ++i)   {
			if (write_body_tags_aux(e->children.data[i], fd, j+curid))
				++j;
		}
		return true;
	}
	return false;
}

/**
 * write_body_tags - Write hipe append instructions for all tags
 *	rooted at the body tag (doesn't write the body tag)
 *
 * @depth: number of children descended from the body element (GumboNode body
 *	element has depth 0)
 */
static void write_body_tags(GumboNode *n, int fd)
{
	int nnodes = mygumbo_count_nodes(n);

	// Allocate variables.
	dprintf(fd, "\thipe_loc loc;\n");
	// Array of parent locations where an element at index i is the hipe_loc of the parent
	// node of node with ID i. IDs start at 1.
	dprintf(fd, "\thipe_loc plocs[%d];\n", nnodes+1);
	dprintf(fd, "\tmemset((void *)plocs, 0, %d*sizeof(hipe_loc));\n", nnodes+1);

	write_body_tags_aux(n, fd, 1);
}

/**
 * write_header_tags - Write hipe instructions for header tags
 * @h: gumbo node header tag
 */
static void write_header_tags(GumboNode *h, int fd)
{
	// TODO
	;
}

void mygumbo_write_tags(GumboNode *n, int fd)
{
	if (n->type == GUMBO_NODE_ELEMENT) {
		GumboElement *e = (GumboElement *)&n->v;

		if (e->tag == GUMBO_TAG_HTML) {
			for (int i = 0; i < e->children.length; ++i)
				mygumbo_write_tags(e->children.data[i], fd);
		} else if (e->tag == GUMBO_TAG_HEAD)
			write_header_tags(n, fd);
		else if (e->tag == GUMBO_TAG_BODY)
			write_body_tags(n, fd);
	}
}
