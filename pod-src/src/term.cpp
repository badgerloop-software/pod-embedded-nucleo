#include <iostream>
#include "mbed.h"
#include <stdint.h>
#include "term.h"
#include "buart.h"
#include "mcp23017.h"
#include "boardTelem.h"
#include "comms.h"
#include "data.h"

#define CMD_SIZE = 100;

static int numCmds = 13;
static Command *commandList[13];
/* These three arrays are for the user/shell. Keep the indexing in sync and
 * they will work well */
static uint16_t (*cmds[])(void) = {
    help,
    read7VRailV,
    read7VRailA,
    readBusV,
    readBusA,
    read5VRailV,
    read5VRailA,
    readTherm1,
    readTherm2,
    testWriteIOX,
    testReadIOX,
    testRecvData,
    dumpData
};

static char *cmdNames[] = {
  /*  "help",
    "read7VRailV",
    "read7VRailA",
    "readBusV",
    "readBusA",
    "read5VRailV",
    "read5VRailA",
    "readTherm1",
    "readTherm2",
    "testWriteIOX",
    "testReadIOX",
    "testRecvData",
    "dumpData" */
};

static char *cmdDescs[] = {
 /*   "Prints a command list",
    "Reads the voltage on the 7 volt rail",
    "Reads the current on the 7 volt rail",
    "Reads the voltage on the main power bus",
    "Reads the current on the main power bus",
    "Reads the voltage on the 5 volt rail",
    "Reads the current on the 5 volt rail",
    "Reads the temperature on thermistor 1",
    "Reads the temperature on thermistor 2",
    "Tests writing to every pin in the IO Expander",
    "Tests reading from every pin in the IO Expander",
    "Dumps data received over serial",
    "Dumps local master data structure " */
};

Command::Command (string n, string d, uint16_t exec) {
    name = n;
    desc = d;
    id = nextID++;
    commandList[id] = this;
}

int Command::runCommand() {
    return this->exec();
return 1;
}
void runDebugTerminal() {
    int cmdID = waitForCmd();  // Waits for a command
    int res = commandList[cmdID].runCommand();
    if (res == 1) {
        printf("[Error] \n\r");
    }
}

int cmdInput() {
    string input;
    printf("Enter a Command: ");
    std::cin >> input;
    return 1;
}

int waitForCmd() {
    char buff[100];
    int cnt = 0;
    printf("Waiting for input...\n\r");
    while (cnt < 99) {
        buff[cnt] = getchar();
        printf("%c", buff[cnt]);
        if (buff[cnt] == '\r' && cnt != 0)
            break;
        else if (buff[cnt] == '\r' && cnt == 0)
            continue;
        cnt += 1;
    }
    buff[cnt] = '\0';
    printf("\n\r");
    for (int i = 0; i < numCmds; i++) {
        if (!strcmp(buff, cmdNames[i])) {
            return i;
        }
    }
    return -1;
}

uint16_t help() {
    int i;
    printf("BADGERLOOP UTILITY & TESTING TOOL\n\r"); // Sometimes I think I'm five
    printf("Commands:\n\r");
    for (i = 0; i < numCmds; i++) {
        printf("\t%s - %s\n\r", cmdNames[i], cmdDescs[i]);
    }
    return 0;
}
