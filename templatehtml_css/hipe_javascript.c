#include <hipe.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

hipe_session session;

int main(int argc, char **argv) {
  session = hipe_open_session(0, 0, 0, "test");
  if (!session)
    exit(1);
  hipe_loc h1 = append_tag_getLoc(session, 0, "h1", "h1id");
  hipe_send(session, HIPE_OP_SET_TEXT, 0, h1, 1, "Hello");
  hipe_send(session, HIPE_OP_SET_TEXT, 0, h1, 1, "!this.innerHTML='new html'");
  hipe_send(session, HIPE_OP_SET_TEXT, 0, h1, 1, "!this.textContent='new content'");
  hipe_send(session, HIPE_OP_SET_TEXT, 0, h1, 1, "!this.innterText='new text'");
  hipe_send(session, HIPE_OP_SET_TEXT, 0, h1, 1, "!this.innterText='new text'");

  hipe_instruction instruction;
  hipe_instruction_init(&instruction);
  while (1) {
    if (hipe_next_instruction(session, &instruction, 0)) {
      printf("Instruction/event received\n");
      if (instruction.opcode == HIPE_OP_FRAME_CLOSE) // close button clicked.
        return 0;
    }
  }
  hipe_close_session(session);
  return 0;
}
