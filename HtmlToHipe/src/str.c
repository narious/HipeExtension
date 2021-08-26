#include "str.h"

bool whitespace(char c)
{
	return c == ' ' || c == '\t' || c == '\n';
}

bool allwhitespace(char *s)
{
	int n = strlen(s);

	for (int i = 0; i < n; ++i) {
		if (!whitespace(s[i]))
			return false;
	}
	return true;
}

bool str_contains(char *s, char c)
{
	int n = strlen(s);
	
	for (int i = 0; i < n; ++i) {
		if (s[i] == c)
			return true;
	}
	return false;
}

int str_count(char *s, char c)
{
	int cnt, n;

	cnt = 0;
	n = strlen(s);

	for (int i = 0; i < n; ++i) {
		if (s[i] == c)
			++cnt;
	}
	return cnt;
}

char *str_escape_nl(char *s)
{
	// Read, write, length, and number of newlines.
	int r, w, n, nnl; 
	char *t;

	n = strlen(s);
	nnl = str_count(s, '\n');
	t = malloc((n+nnl)*sizeof(char));

	w = 0;
	for (r = 0; r < n; ++r, ++w) {
		if (s[r] == '\n') {
			t[w++] = '\\';
			t[w] = 'n';
		} else
			t[w] =s[r];
	}
	return t;
}

char *str_rm_strconst_tab_nl(char *s)
{
	int r, w, n;
	bool instr;

	n = strlen(s);
	instr = false;
	
	w = 0;
	for (r = 0; r < n; ++r) {
		if (r > 0 && s[r] == '"' && s[r-1] != '\\') 
			instr = !instr;
		if (instr && s[r] != '\t' && s[r] != '\n') {
			s[w++] = s[r];
		} else if (!instr)
			s[w++] = s[r];
	}
	s = realloc(s, w+1);
	s[w] = '\0';
	return s;
}

/**
 * str_rm - Remove all characters in the pattern from the string
 *
 * Return the new length of the string. Doesn't add a null term char.
 */
int str_rm(char *s, char *pat)
{
	int r, w, n, m, j;
	bool fnd;  // Found.

	n = strlen(s);
	m = strlen(pat);
	fnd = false;

	w = 0;
	for (r = 0; r < n; ++r) {
		for (j = 0; j < m; ++j) {
			if (s[r] == pat[j]) {
				fnd = true;
				break;
			}
		}
		if (!fnd)
			s[w++] = s[r];
		fnd = false;
	}
	return w;
}

char *str_rm_tab_nl(char *s)
{
	int n = str_rm(s, "\t\n");
	s[n] = '\0';
	return realloc(s, n+1);
}
