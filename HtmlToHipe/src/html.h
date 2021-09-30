/*
 * Create all HTML tags in a HTML file with hipe
 * client instructions.
 */
#ifndef HTML_H
#define HTML_H

#include <gumbo.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "str.h"
#include "events.h"
#include "wd.h"

extern struct click_event click_events[BUFSIZ];
extern int click_event_counter;

/**
 * mygumbo_write_html - Write all HTML tags in a Gumbo representation of
 *	a HTML file as hipe client send instructions.
 * @root: root node of Gumbo representation of HTML file
 * @fd: file descriptor to write hipe client send instructions to
 */
void mygumbo_write_html(GumboNode *root, int fd, char *html);

#endif
