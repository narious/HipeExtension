/*
 * Set all HTML tag attributes in a HTML file with hipe
 * client instructions.
 */
#ifndef ATTR_H
#define ATTR_H

#include <gumbo.h>

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
