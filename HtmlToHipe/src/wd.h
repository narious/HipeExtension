/*
 * Functions to get the working directory of the current HTML file being
 * processed since links/references to source files in this HTML file will
 * be relative to the HTML file and so need to be relative to its working
 * directory, and not the working directory of where this program is executed.
 */
#ifndef WD_H
#define WD_H

#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// The working directory of the current HTML file
// being processed.
extern char *htmlwd;

/**
 * wdinit - Initialise the working directory for a HTML filepath
 *
 * Free with wdfree.
 */
void wdinit(char *fpath);

/**
 * wdpushcat - Append a filepath to the end of the HTML working directory
 * @fpath: filepath or hyperlink or whatever else can appear in the value part
 *	of a HTML tag's src and href attributes
 *
 * Named push because the change can be reverted with wdpopcat. A next wdpushcat
 * should only be called after a call to wdpopcat. If the "filepath" argument is
 * a hyperlink or absolute then htmlwd gets set to it directly. 
 * 
 * Use variable htmlwd as the result of this function.
 */
void wdpushcat(char *fpath);
void wdpopcat(void);
void wdfree(void);

#endif
