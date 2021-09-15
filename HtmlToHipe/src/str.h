#ifndef STR_H
#define STR_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * whitespace - Get whether a character is whitespace
 */
bool whitespace(char c);

/**
 * allwhitespace - Get whether a string is all whitespace
 */
bool allwhitespace(const char *s);

/**
 * str_contains - Get whether a string contains a character
 */
bool str_contains(char *s, char c);

/**
 * str_escape_nl - Convert all newlines in a string to escaped newlines
 *
 * Return is dynamically allocated and should be freed with free.
 */
char *str_escape_nl(const char *s);

/**
 * str_rm_strconst_tab_nl - Remove all tabs and newlines within string constants found within the
 *	input string
 */
char *str_rm_strconst_tab_nl(char *s);

/**
 * str_rm_tab_nl - Remove all tabs and newlines within a string
 *
 * Assumes the input string is dynamically allocated and reallocates its memory. Returns the
 * result of realloc.
 */
char *str_rm_tab_nl(char *s);

/**
 * strnewcpy - Get a dynamically allocated new copy of a string
 */
char *strnewcpy(const char *src);

#endif
