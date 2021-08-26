#include <gumbo.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include "tag.h"

void write_includes(int fd)
{
	// Print all on separate lines to make it clearer what's happening.
	dprintf(fd, "#include <hipe.h>\n");
	dprintf(fd, "#include <string.h>\n");
	dprintf(fd, "#include <stdlib.h>\n");
	dprintf(fd, "\n");
}

void write_main(int fd)
{
	dprintf(fd, "int main(void)\n");
	dprintf(fd, "{\n");
	dprintf(fd, "\thipe_session session;\n");
	dprintf(fd, "\thipe_instruction instr;\n");
	dprintf(fd, "\tsession = hipe_open_session(0, 0, 0, \"test\");\n");
	dprintf(fd, "\tif (!session)\n");
	dprintf(fd, "\t\texit(EXIT_FAILURE);\n");
	dprintf(fd, "\thipe_instruction_init(&instr);\n");
	dprintf(fd, "\thipe_build_html_head(session);\n");
	dprintf(fd, "\thipe_build_html_body(session);\n");
	dprintf(fd, "\tfor (;;) {\n");
	dprintf(fd, "\t\tif (hipe_next_instruction(session, &instr, 1) && instr.opcode == HIPE_OP_FRAME_CLOSE)\n");
	dprintf(fd, "\t\t\tbreak;\n");
	dprintf(fd, "\t}\n");
	dprintf(fd, "\thipe_close_session(session);\n");
	dprintf(fd, "\treturn 0;\n");
	dprintf(fd, "}");
}

/**
 * mygumbo_write_hipe - Write gumbo output of a HTML file as hipe client send
 *	instructions to a file
 * @g: gumbo output with 
 */
void mygumbo_write_hipe(GumboOutput *g, int fd, char *html)
{
	write_includes(fd);
	mygumbo_write_tags(g->root, fd, html);  // TODO rename
	write_main(fd);
}

/**
 * filesz - Get the size of a file in bytes.
 */
int filesz(int fd)
{
	struct stat s;
	
	if (fstat(fd, &s) == -1)
		return -1;
	return s.st_size;
}

/**
 * falloc - Dynamically allocate the whole of a file into a C string
 *
 * Return must be freed with free.
 */
char *falloc(int fd)
{
	int fsz;
	char *s;

	flock(fd, LOCK_EX);

	fsz  = filesz(fd);
	lseek(fd, 0, SEEK_SET);
	// TODO add null term until determine whether it's needed
	s = malloc((fsz+1)*sizeof(char));  
	read(fd, (void *)s, fsz);
	s[fsz] = '\0';

	flock(fd, LOCK_UN);

	return s;
}

void html_to_hipe(char *fpath)
{
	int fd;
	char *html;
	GumboOutput *g;

	fd = open(fpath, O_RDONLY);

	if (fd == -1) {
		perror(fpath);
		return;
	}

	html = falloc(fd);
	close(fd);
	// TODO how does gumbo parse a string, does it stop at a null term character
	// or some other special delimiter?
	g = gumbo_parse(html);  // TODO handle errors
	mygumbo_write_hipe(g, STDOUT_FILENO, html);

	gumbo_destroy_output(&kGumboDefaultOptions, g);
	free(html);  // Free last since buffer is supposed to live as long as gumbo is used.
}

int main(int argc, char *argv[])
{
	for (int i = 1; i < argc; ++i) 
		html_to_hipe(argv[i]);
	return 0;
}
