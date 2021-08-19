

/*
 * Set all HTML tag attributes in a HTML file with hipe
 * client instructions.
 */
#ifndef ATTR_H
#define ATTR_H

#include <stdio.h>
#include "string.h"
#include "gumbo.h"

// Forward declarations
static void traverse_attrs(GumboNode* node, int fd);
static void hipe_build_attrs(GumboAttribute* at, const char * hipeLoc, int fd);
static const char* get_tag_name(GumboNode *node);
static const char* handle_unknown_tag(GumboStringPiece *text);
static void traverse(GumboNode* node, int fd);
/**
 * gumbo_write_attr - Write all HTML tag attributes in a Gumbo representation of
 *	a HTML file as hipe client send instructions.
 * @root: root node of Gumbo representation of HTML file
 * @fd: file descriptor to write hipe client send instructions to
 *
 * TODO Michael implement
 */

void mygumbo_write_attr(GumboNode *root, int fd);

#endif
