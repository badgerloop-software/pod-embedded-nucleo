#include "mbed.h"
#include "adc128.h"
#include "term.h"

static int numCmds = 1;
static float (*cmds[])(void) = {
                       read7VRail  
                       };

void runDebugTerminal(Serial *pc) {
    int cmd = waitForCmd(pc);  // Waits for a command
    callCmd(pc, cmd);
}


int waitForCmd(Serial *pc) {
    char buff[100];
    int cnt = 0;
    (*pc).printf("Waiting for input...\n\r");
    while (cnt < 99) {
        buff[cnt] = (*pc).getc();
        (*pc).printf("%c", buff[cnt]);
        if (buff[cnt++] == '\r')
            break;
    }
    buff[cnt - 1] = '\0';
    if (!strcmp(buff, "read")) {
        return 0;
    }
    return -1;
}

float callCmd(Serial *pc, int cmd) {
    if (cmd == -1) {
        (*pc).printf("Invalid Command\n\r");
        return -1.0;
    }
    (*pc).printf("Value: %f\n\r", cmds[cmd]());
    return 1.0;
}
