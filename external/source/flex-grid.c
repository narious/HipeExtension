#include <hipe.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void handle_tag_src(hipe_session session, hipe_loc loc, const char * filesource, char * mime) {
		FILE* file = fopen(filesource, "r");
	if(!file) {
			printf("Could not open file: '%s' for reading.", filesource); return;}		fflush(stdout);
		fseek(file, 0, SEEK_END);size_t size = ftell(file); rewind(file);char* data = malloc(size);size_t result = fread(data, 1, size, file);
		if(result != size) {printf("Error reading file");return;}
		fflush(stdout);
		hipe_instruction instr;hipe_instruction_init(&instr);instr.opcode = HIPE_OP_SET_SRC;instr.location = loc;instr.arg[0] = data; instr.arg_length[0]=size;instr.arg[1] = mime;instr.arg_length[1]=strlen(instr.arg[1]);
		hipe_send_instruction(session, instr); free(data);
}

static void hipe_build_html_head(hipe_session session)
{
	hipe_send(session, HIPE_OP_SET_TITLE, 0, 0, 1, "Document");
	hipe_send(session, HIPE_OP_IMPORT_CSS, 0, 0, 2, "test3.css", "0");
}

static void hipe_build_html_body(hipe_session session)
{
	hipe_loc loc;
	hipe_loc plocs[45];
	loc = 0;
	memset((void *)plocs, 0, 45*sizeof(hipe_loc));
	loc = append_tag_getLoc(session, plocs[1], "h1", "");
	hipe_send(session, HIPE_OP_SET_TEXT, 0, loc, 1, "Table test");
	loc = append_tag_getLoc(session, plocs[2], "table", "");
	plocs[3] = loc;
	plocs[4] = loc;
	loc = append_tag_getLoc(session, plocs[3], "caption", "");
	hipe_send(session, HIPE_OP_SET_TEXT, 0, loc, 1, "Alien football stars");
	loc = append_tag_getLoc(session, plocs[4], "tbody", "");
	plocs[5] = loc;
	plocs[6] = loc;
	plocs[7] = loc;
	plocs[8] = loc;
	loc = append_tag_getLoc(session, plocs[5], "tr", "");
	plocs[6] = loc;
	plocs[7] = loc;
	plocs[8] = loc;
	loc = append_tag_getLoc(session, plocs[6], "th", "");
	hipe_send(session, HIPE_OP_SET_ATTRIBUTE, 0, loc, 2, "scope", "col");
	hipe_send(session, HIPE_OP_SET_TEXT, 0, loc, 1, "Player");
	loc = append_tag_getLoc(session, plocs[7], "th", "");
	hipe_send(session, HIPE_OP_SET_ATTRIBUTE, 0, loc, 2, "scope", "col");
	hipe_send(session, HIPE_OP_SET_TEXT, 0, loc, 1, "Gloobles");
	loc = append_tag_getLoc(session, plocs[8], "th", "");
	hipe_send(session, HIPE_OP_SET_ATTRIBUTE, 0, loc, 2, "scope", "col");
	hipe_send(session, HIPE_OP_SET_TEXT, 0, loc, 1, "Za'taak");
	loc = append_tag_getLoc(session, plocs[6], "tr", "");
	plocs[7] = loc;
	plocs[8] = loc;
	plocs[9] = loc;
	loc = append_tag_getLoc(session, plocs[7], "th", "");
	hipe_send(session, HIPE_OP_SET_ATTRIBUTE, 0, loc, 2, "scope", "row");
	hipe_send(session, HIPE_OP_SET_TEXT, 0, loc, 1, "TR-7");
	loc = append_tag_getLoc(session, plocs[8], "td", "");
	hipe_send(session, HIPE_OP_SET_TEXT, 0, loc, 1, "7");
	loc = append_tag_getLoc(session, plocs[9], "td", "");
	hipe_send(session, HIPE_OP_SET_TEXT, 0, loc, 1, "4,569");
	loc = append_tag_getLoc(session, plocs[7], "tr", "");
	plocs[8] = loc;
	plocs[9] = loc;
	plocs[10] = loc;
	loc = append_tag_getLoc(session, plocs[8], "th", "");
	hipe_send(session, HIPE_OP_SET_ATTRIBUTE, 0, loc, 2, "scope", "row");
	hipe_send(session, HIPE_OP_SET_TEXT, 0, loc, 1, "Khiresh Odo");
	loc = append_tag_getLoc(session, plocs[9], "td", "");
	hipe_send(session, HIPE_OP_SET_TEXT, 0, loc, 1, "7");
	loc = append_tag_getLoc(session, plocs[10], "td", "");
	hipe_send(session, HIPE_OP_SET_TEXT, 0, loc, 1, "7,223");
	loc = append_tag_getLoc(session, plocs[8], "tr", "");
	plocs[9] = loc;
	plocs[10] = loc;
	plocs[11] = loc;
	loc = append_tag_getLoc(session, plocs[9], "th", "");
	hipe_send(session, HIPE_OP_SET_ATTRIBUTE, 0, loc, 2, "scope", "row");
	hipe_send(session, HIPE_OP_SET_TEXT, 0, loc, 1, "Mia Oolong");
	loc = append_tag_getLoc(session, plocs[10], "td", "");
	hipe_send(session, HIPE_OP_SET_TEXT, 0, loc, 1, "9");
	loc = append_tag_getLoc(session, plocs[11], "td", "");
	hipe_send(session, HIPE_OP_SET_TEXT, 0, loc, 1, "6,219");
	loc = append_tag_getLoc(session, plocs[3], "br", "");
	loc = append_tag_getLoc(session, plocs[4], "h1", "");
	hipe_send(session, HIPE_OP_SET_TEXT, 0, loc, 1, "Flex box test");
	loc = append_tag_getLoc(session, plocs[5], "div", "");
	hipe_send(session, HIPE_OP_SET_STYLE, 0, loc, 2, "display"," flexbox");
	hipe_send(session, HIPE_OP_SET_STYLE, 0, loc, 2, "flex-direction"," column");
	hipe_send(session, HIPE_OP_SET_ATTRIBUTE, 0, loc, 2, "class", "flexbox");
