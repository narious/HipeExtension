#include <hipe.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void handle_tag_src(hipe_session session, hipe_loc loc, const char * filesource, char * mime) {
	char filefullpath[50];
	strcat(filefullpath, "../data/");
	strcat(filefullpath, filesource);
	FILE* file = fopen(filefullpath, "r");
	if(!file) {
			printf("Could not open file: '%s' for reading.(probably wrong path?)", filefullpath); return;}		fflush(stdout);
	fseek(file, 0, SEEK_END);size_t size = ftell(file); rewind(file);char* data = malloc(size);size_t result = fread(data, 1, size, file);
	if(result != size) {printf("Error reading file");return;}
		fflush(stdout);
	hipe_instruction instr;hipe_instruction_init(&instr);instr.opcode = HIPE_OP_SET_SRC;instr.location = loc;instr.arg[0] = data; instr.arg_length[0]=size;instr.arg[1] = mime;instr.arg_length[1]=strlen(instr.arg[1]);
	hipe_send_instruction(session, instr); free(data);
}

static void hipe_build_html_head(hipe_session session)
{
	char cwd[150];
	getcwd(cwd, 150);
	printf("currentfilepath: %s\n", cwd);
	strcat(cwd,"/../data/square.css");
	hipe_send(session, HIPE_OP_SET_TITLE, 0, 0, 1, "Document");
	hipe_send(session, HIPE_OP_IMPORT_CSS, 0, 0, 2, cwd, "0");
}

static void hipe_build_html_body(hipe_session session)
{
	hipe_loc loc;
	hipe_loc plocs[5];
	loc = 0;
	memset((void *)plocs, 0, 5*sizeof(hipe_loc));
	loc = append_tag_getLoc(session, plocs[1], "h1", "");
	hipe_send(session, HIPE_OP_SET_TEXT, 0, loc, 1, "Hello World");
	loc = append_tag_getLoc(session, plocs[2], "div", "");
	hipe_send(session, HIPE_OP_SET_ATTRIBUTE, 0, loc, 2, "id", "important-box");
	loc = append_tag_getLoc(session, plocs[3], "script", "");
	hipe_send(session, HIPE_OP_SET_ATTRIBUTE, 0, loc, 2, "src", "main.js");
	loc = append_tag_getLoc(session, plocs[4], "style", "");
	hipe_send(session, HIPE_OP_ADD_STYLE_RULE, 0, 0, 2, "body", "background-color: aqua;");
}

int main(void)
{
	hipe_session session;
	hipe_instruction instr;
	session = hipe_open_session(0, 0, 0, "test");
	if (!session)
		exit(EXIT_FAILURE);
	hipe_instruction_init(&instr);
	hipe_build_html_body(session);
	hipe_build_html_head(session);
	for (;;) {
		if (hipe_next_instruction(session, &instr, 1) && instr.opcode == HIPE_OP_FRAME_CLOSE)
			break;
	}
	hipe_close_session(session);
	return 0;
}