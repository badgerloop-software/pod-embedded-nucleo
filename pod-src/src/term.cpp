#include "mbed.h"
#include "term.h"
#include "uart.h"
#include "mcp23017.h"
#include "boardTelem.h"

static int numCmds = 13;
extern RawSerial pc;
/* These three arrays are for the user/shell. Keep the indexing in sync and
 * they will work well */

static float (*cmds[])(void) = {
    help,
    read7VRailV,  
    read7VRailA,
    readBusV,
    readBusA,
    read5VRailV,
    read5VRailA,
    readTherm1,
    readTherm2,
    testChanSend,
    testChanRead,
    testWriteIOX,
    testReadIOX
};

static char *cmdNames[] = {
    "help",
    "read7VRailV",
    "read7VRailA",
    "readBusV",
    "readBusA",
    "read5VRailV",
    "read5VRailA",
    "readTherm1",
    "readTherm2",
    "testChanSend",
    "testChanRead",
    "testWriteIOX",
    "testReadIOX"
};

static char *cmdDescs[] = {
    "Prints a command list",
    "Reads the voltage on the 7 volt rail",
    "Reads the current on the 7 volt rail",
    "Reads the voltage on the main power bus",
    "Reads the current on the main power bus",
    "Reads the voltage on the 5 volt rail",
    "Reads the current on the 5 volt rail",
    "Reads the temperature on thermistor 1",
    "Reads the temperature on thermistor 2",
    "Sends a message across the serial channel",
    "Reads the serial channel",
    "Tests writing to every pin in the IO Expander",
    "Tests reading from every pin in the IO Expander"
};

void runDebugTerminal() {
    int cmd = waitForCmd();  // Waits for a command
    callCmd(cmd);
}

int waitForCmd() {
    char buff[100];
    int cnt = 0;
    pc.printf("Waiting for input...\n\r");
    while (cnt < 99) {
        buff[cnt] = pc.getc();
        pc.printf("%c", buff[cnt]);
        if (buff[cnt] == '\r' && cnt != 0)
            break;
        else if (buff[cnt] == '\r' && cnt == 0)
            continue;
        cnt += 1;
    }
    buff[cnt] = '\0';
    pc.printf("\n\r");
    for (int i = 0; i < numCmds; i++) {
        if (!strcmp(buff, cmdNames[i])) {
            return i;
        }
    }
    return -1;
}

void callCmd(int cmd) {
    if (cmd == -1) {
        pc.printf("Invalid Command\n\r");
    } else {
        pc.printf("Value: %f\n\r", cmds[cmd]());
    }
}
 
float help() {
    int i;
    pc.printf("Welcome to Ezra's little Mbed Oasis.\n\r");
    pc.printf("Commands:\n\r");
    for (i = 0; i < numCmds; i++) {
        pc.printf("\t%s - %s\n\r", cmdNames[i], cmdDescs[i]);
    }
    return 0;
}
