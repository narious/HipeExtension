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

static void write_append_tag(int fd, int curid, const char *tagname)
{
	dprintf(fd, "\tloc = append_tag_getLoc(session, plocs[%d], \"%s\", \"\");\n",
		curid, tagname);
}

/**
 * get_tag_text - Get the text within a tag
 * @s: HTML file as string
 *
 * Text is considered all characters in the body of the tag that isn't
 * within an embedded tag. In the below example HTML, tag1's text is 
 * "foo helloworldbar" and tag2's text is "ignore me".
 *
 * <tag1 attr="abc">foo hello<tag2>ignore me</tag2>worldbar</tag1>
 *
 * Returned string is dynamically allocated and must be freed with free.
 * Return NULL if tag has no text.
 */
static char *get_tag_text(GumboElement *e, char *s)
{
	// Iterator, start, end and final end indices, stack, and
	// current text length, and length of substring in text.
	int i, st, en, end, stk, len, slen;
	char *text;

	i = e->start_pos.offset;
	end = e->end_pos.offset;
	stk = 0;
	len = 1;  // Start with 1 for later null term char.
	text = NULL;

	// Move to the start of the tag's body.
	// TODO currently assumes the > char doesn't appear in any attributes
	// TODO need to handle properly > appearing in text sections and not decrementing
	// the stack too much
	while (i < end && s[i++] != '>') 
		;
	st = i;

	for (; i <= end; ++i) {
		// A '<' without a space next is the start of a new tag.
		if (s[i] == '<' && s[i+1] != ' ') {
			// No stack means a section of text has just been passed.
			if (!stk) {
				// Append subtext just passed to text.
				en = i-1;
				slen = en-st+1;  // Length of subtext.
				if (slen > 0) {
					text = realloc(text, len+slen); 
					strncpy(text+(len-1), s+st, slen);
					len += slen;
				}
			}
			++stk;
		} else if (s[i] == '>') {
			st = i+1;
			--stk;
		}
	}
	if (text)
		text[len] = '\0';
	return text;
}

static void write_tag_text(GumboElement *e, int fd, char *html)
{
	char *t = get_tag_text(e, html);

	if (t) {
		dprintf(fd, "\thipe_send(session, HIPE_OP_SET_TEXT, 0, loc, 1, \"%s\");\n", t);
		free(t);
	}
}

static void write_tag_attr(GumboElement *e, int fd)
{
	GumboAttribute *a;

	for (int i = 0; i < e->attributes.length; ++i) {
		a = (GumboAttribute *)e->attributes.data[i];
		dprintf(fd, "\thipe_send(session, HIPE_OP_SET_ATTRIBUTE, 0, loc, 2, \"%s\", \"%s\");\n",
			a->name, a->value);
	}
}

/**
 * whitespace - Get whether a character is whitespace
 */
static bool whitespace(char c)
{
	return c == ' ' || c == '\t' || c == '\n';
}

/**
 * write_tag_style - Write the contents of a style tag as hipe instructions so that CSS
 *	can be set
 */
static void write_tag_style(GumboElement *e, int fd, char *s)
{
	// Iterator, start and end indices of substring (both endpoints inclusive) 
	// in html to write, and end index to go up to.
	int i, st, en, end;

	i = e->start_pos.offset;
	end = e->end_pos.offset;

	// Go to start of tag's body/text.
	while (s[i++] != '>')
		;
	while (whitespace(s[i]))
		++i;
	while (i < end) {
		// Start of CSS element/selector.
		st = i;
		while (!whitespace(s[i]))
			++i;
		en = i-1;

		dprintf(fd, "\thipe_send(session, HIPE_OP_ADD_STYLE_RULE, 0, 0, 2, \"");
		write(fd, s+st, en-st+1);
		dprintf(fd, "\", \"");

		while (s[i++] != '{')
			;
		while (whitespace(s[i]))
			++i;
		// Start of data paired with CSS element to set.
		st = i;
		for (; s[i] != '}'; ++i) {
			if (!whitespace(s[i])) 
				en = i;
		}
		write(fd, s+st, en-st+1);
		dprintf(fd, "\");\n");

		// Do this at end rather than start to try and push passed end index and break out
		// of outer while loop. Increment once before to push passed '}'.
		for (++i; whitespace(s[i]); ++i)
			;
	}
}

static void handle_body_elem(GumboElement *e, int fd, int curid, char *html)
{
	write_append_tag(fd, curid, gumbo_normalized_tagname(e->tag));
	write_tag_attr(e, fd);

	if (e->tag != GUMBO_TAG_STYLE)
		write_tag_text(e, fd, html);
	else
		write_tag_style(e, fd, html);
}

/**
 * @curid: current node's ID
 */
static bool write_body_tags_aux(GumboNode *n, int fd, int curid, char *html)
{
	if (n->type == GUMBO_NODE_ELEMENT) {
		int i, j;
		GumboElement *e = (GumboElement *)&n->v;

		// 0th ID is for the body tag which doesn't need to have anything done
		// since it's where all tags reside by default.
		if (curid > 0) 
			handle_body_elem(e, fd, curid, html);

		/*fprintf(stderr, "===,sc=%c,ec=%c\n", html[e->start_pos.offset], html[e->end_pos.offset]);*/
		/*fprintf(stderr, "line=%d,col=%d,offt=%d\n", e->start_pos.line, e->start_pos.column, */
			/*e->start_pos.offset);*/
		/*fprintf(stderr, "line=%d,col=%d,offt=%d\n", e->end_pos.line, e->end_pos.column, */
			/*e->end_pos.offset);*/
		/*fprintf(stderr, "===\n");*/
		/*write(STDERR_FILENO, html+e->start_pos.offset, e->end_pos.offset-e->start_pos.offset);*/
		

		// Set each node's parent location.
		for (i = 0, j = 0; i < e->children.length; ++i) {
			n = (GumboNode *)e->children.data[i];
			if (n->type == GUMBO_NODE_ELEMENT)
				dprintf(fd, "\tplocs[%d] = loc;\n", ++j+curid);
		}
		for (i = 0, j = 1; i < e->children.length; ++i) {
			if (write_body_tags_aux(e->children.data[i], fd, j+curid, html))
				++j;
		}
		return true;
	}
	return false;
}

/**
 * write_body_tags - Write hipe append instructions for all tags
 *	rooted at the body tag (doesn't write the body tag)
 */
static void write_body_tags(GumboNode *n, int fd, char *html)
{
	int nnodes = mygumbo_count_nodes(n);

	dprintf(fd, "static void hipe_build_html_body(hipe_session session)\n");
	dprintf(fd, "{\n");
	// Allocate variables.
	dprintf(fd, "\thipe_loc loc;\n");
	// Array of parent locations where an element at index i is the hipe_loc of the parent
	// node of node with ID i.
	dprintf(fd, "\thipe_loc plocs[%d];\n", nnodes);
	dprintf(fd, "\tloc = 0;\n");
	write_body_tags_aux(n, fd, 0, html);
	dprintf(fd, "}\n");
	dprintf(fd, "\n");
}

static void handle_head_tag_title(GumboElement *e, int fd, char *html)
{
	char *s = get_tag_text(e, html);

	if (s) {
		dprintf(fd, "\thipe_send(session, HIPE_OP_SET_TITLE, 0, 0, 1, \"%s\");\n", s);
		free(s);
	}
}

static void handle_head_tag_link(GumboElement *e, int fd)
{
	GumboAttribute *a;

	for (int i = 0; i < e->attributes.length; ++i) {
		a = (GumboAttribute *)e->attributes.data[i];

		if (strcmp(a->name, "rel") == 0 && strcmp(a->value, "stylesheet") == 0)
			dprintf(fd, "\t// TODO waiting for Dana to implement head link rel stylesheet\n");
	}
}

static void handle_head_elem(GumboElement *e, int fd, char *html)
{
	switch (e->tag) {
		case GUMBO_TAG_LINK:	handle_head_tag_link(e, fd); break;
		case GUMBO_TAG_TITLE:	handle_head_tag_title(e, fd, html); break;
		default: break;
	}
}


static void write_header_tags_aux(GumboNode *n, int fd, char *html)
{
	if (n->type == GUMBO_NODE_ELEMENT) {
		GumboElement *e = (GumboElement *)&n->v;

		handle_head_elem(e, fd, html);

		for (int i = 0; i < e->children.length; ++i) 
			write_header_tags_aux(e->children.data[i], fd, html);
	}
}

/**
 * write_header_tags - Write hipe instructions for header tags
 * @h: gumbo node header tag
 */
static void write_header_tags(GumboNode *n, int fd, char *html)
{
	dprintf(fd, "static void hipe_build_html_head(hipe_session session)\n");
	dprintf(fd, "{\n");
	write_header_tags_aux(n, fd, html);
	dprintf(fd, "}\n");
	dprintf(fd, "\n");
}

void mygumbo_write_tags(GumboNode *n, int fd, char *html)
{
	if (n->type == GUMBO_NODE_ELEMENT) {
		GumboElement *e = (GumboElement *)&n->v;

		if (e->tag == GUMBO_TAG_HTML) {
			for (int i = 0; i < e->children.length; ++i)
				mygumbo_write_tags(e->children.data[i], fd, html);
		} else if (e->tag == GUMBO_TAG_HEAD)
			write_header_tags(n, fd, html);
		else if (e->tag == GUMBO_TAG_BODY)
			write_body_tags(n, fd, html);
	}
}
