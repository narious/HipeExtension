/*
 * Create all HTML tags in a HTML file with hipe
 * client instructions.
 * TODO rename this file from tag since attributes done here as well
 */
#ifndef TAG_H
#define TAG_H

#include <gumbo.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "str.h"

/**
 * gumbo_write_tags - Write all HTML tags in a Gumbo representation of
 *	a HTML file as hipe client send instructions.
 * @root: root node of Gumbo representation of HTML file
 * @fd: file descriptor to write hipe client send instructions to
 *
 * TODO Petar implement
 */
void mygumbo_write_tags(GumboNode *root, int fd, char *html);

#endif
