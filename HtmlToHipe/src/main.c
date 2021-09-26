#include <gumbo.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include "html.h"
#include "events.h"

// Setting a defualt source code directory, need to implment this later
char * src_tag_directory ="../data/";

void write_includes(int fd)
{
	// Print all on separate lines to make it clearer what's happening.
	dprintf(fd, "#include <hipe.h>\n");
	dprintf(fd, "#include <string.h>\n");
	dprintf(fd, "#include <stdlib.h>\n");
	dprintf(fd, "#include <stdio.h>\n");
	dprintf(fd, "#include <sys/stat.h>\n");
	dprintf(fd, "\n");
}

void write_handle_link_events(int fd) {
	dprintf(fd, "void handle_link_events(hipe_session session, hipe_instruction instr) {\n");
	// Currently only weblinks gwill work
	for (int i = 0; i < click_event_counter; i++) {
		dprintf(fd, "\tif (instr.requestor == %d) hipe_send(session, HIPE_OP_OPEN_LINK, 0, 0, 1, \"%s\");\n", click_events[i].key, click_events[i].href);
	}
	dprintf(fd, "}\n\n");
}

void write_hipe_apply_defualt_styles(int fd) {
	dprintf(fd, "void hipe_apply_defualt_styles(hipe_session session) {\n");
	dprintf(fd, "\thipe_send(session, HIPE_OP_ADD_STYLE_RULE, 0, 0, 2, \"a\", \"color:rgb(6,69,173);text-decoration:underline; text-decoration-color: rgb(6,69,173);\");\n");
	dprintf(fd, "\thipe_send(session, HIPE_OP_ADD_STYLE_RULE, 0, 0, 2, \"a:hover\", \"color:rgb(11,0,128);text-decoration:underline; text-decoration-color: rgb(11,0,128);\");\n");
	dprintf(fd, "\thipe_send(session, HIPE_OP_ADD_STYLE_RULE, 0, 0, 2, \"a:active\", \"color:rgb(11,0,128);text-decoration:underline; text-decoration-color: rgb(11,0,128);\");\n");
	dprintf(fd, "\thipe_send(session, HIPE_OP_ADD_STYLE_RULE, 0, 0, 2, \"a:visited\", \"color:rgb(11,0,128);text-decoration:underline; text-decoration-color: rgb(11,0,128);\");\n");
	dprintf(fd, "}\n\n");
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
	dprintf(fd, "\thipe_build_html_body(session);\n");
	dprintf(fd, "\thipe_build_html_head(session);\n");
	dprintf(fd, "\thipe_apply_defualt_styles(session);\n");
	dprintf(fd, "\tfor (;;) {\n");
	dprintf(fd, "\t\thipe_next_instruction(session, &instr, 1);\n");
	dprintf(fd, "\t\tif (instr.opcode == HIPE_OP_FRAME_CLOSE)\n");
	dprintf(fd, "\t\t\tbreak;\n");
	dprintf(fd, "\t\tif (instr.opcode == HIPE_OP_EVENT)\n");
	dprintf(fd, "\t\t\thandle_link_events(session, instr);\n");
	dprintf(fd, "\t}\n");
	dprintf(fd, "\thipe_close_session(session);\n");
	dprintf(fd, "\treturn 0;\n");
	dprintf(fd, "}");
}


void write_filesz_func(int fd)
{
	dprintf(fd, "int filesz(FILE *f)\n");
	dprintf(fd, "{");
	dprintf(fd, "\tstruct stat s;\n");
	dprintf(fd, "\tint fd = fileno(f);\n");
	dprintf(fd, "\tif (fstat(fd, &s) == -1)\n");
	dprintf(fd, "\t\treturn -1;\n");
	dprintf(fd, "\treturn s.st_size;\n");
	dprintf(fd, "}\n");
	dprintf(fd, "\n");
}

/**
 * Writes a function that handles src tags in the hipe cli
 */
void write_tag_src_handler(int fd) 
{
	write_filesz_func(fd);
	dprintf(fd, "void handle_tag_src(hipe_session session, hipe_loc loc, const char *filesource, char *mime)\n");
	dprintf(fd, "{\n");
	dprintf(fd, "\tchar fpath[50];\n");
	dprintf(fd, "\tFILE *f;\n");
	dprintf(fd, "\tint fsz, res;\n");
	dprintf(fd, "\tchar *s;\n");
	dprintf(fd, "\thipe_instruction instr;\n");
	dprintf(fd, "\tstrcat(fpath, \"%s\");\n", src_tag_directory);
	dprintf(fd, "\tstrcat(fpath, filesource);\n");
	dprintf(fd, "\tf = fopen(fpath, \"r\");\n");
	dprintf(fd, "\tif (!f) {\n");
	dprintf(fd, "\t\tperror(fpath);\n");  // TODO check null term on fpath?
	dprintf(fd, "\t\texit(EXIT_FAILURE);\n");
	dprintf(fd, "\t}\n");
	dprintf(fd, "\tfsz = filesz(f);\n");
	dprintf(fd, "\ts = malloc(fsz*sizeof(char));\n");
	dprintf(fd, "\tres = fread(s, sizeof(char), fsz, f);\n");
	dprintf(fd, "\tif (res == -1 || res != fsz) {\n");
	dprintf(fd, "\t\tperror(\"fread\");\n");
	dprintf(fd, "\t\texit(EXIT_FAILURE);\n");
	dprintf(fd, "\t}\n");
	dprintf(fd, "\thipe_instruction_init(&instr);\n");
	dprintf(fd, "\tinstr.opcode = HIPE_OP_SET_SRC;\n");
	dprintf(fd, "\tinstr.location = loc;\n");
	dprintf(fd, "\tinstr.arg[0] = s;\n");
	dprintf(fd, "\tinstr.arg_length[0] = fsz;\n");
	dprintf(fd, "\tinstr.arg[1] = mime;\n");
	dprintf(fd, "\tinstr.arg_length[1] = strlen(instr.arg[1]);\n");
	dprintf(fd, "\thipe_send_instruction(session, instr);\n");
	dprintf(fd, "\tfree(s);\n");
	dprintf(fd, "}\n");
	dprintf(fd, "\n");
}


/**
 * mygumbo_write_hipe - Write gumbo output of a HTML file as hipe client send
 *	instructions to a file
 * @g: gumbo output with 
 */
void mygumbo_write_hipe(GumboOutput *g, int fd, char *html)
{
	write_includes(fd);
	write_tag_src_handler(fd);
	write_hipe_apply_defualt_styles(fd);
	mygumbo_write_html(g->root, fd, html);  // TODO rename
	write_handle_link_events(fd);
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
