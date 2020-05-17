#include "mbed.h"
#include <stdint.h>
#include "term.h"
#include "buart.h"
#include "mcp23017.h"
#include "boardTelem.h"
#include "comms.h"
#include "data.h"

#define NUM_COMMANDS  13 // Be sure to update this number when adding commands

static Command *commandList[NUM_COMMANDS];
int Command::nextID = 0;
Command::Command (char* n, char* d, uint16_t(*run)(void)) {
    name = n;
    desc = d;
    id = nextID++;
    cmd = *run;
    commandList[id] = this;
}

int Command::runCommand() {
    printf("Running %s\n\r", name);
   int result = (*cmd)();
    return result;
}

void runDebugTerminal() {
    printf("Badgerloop Utility & Testing Terminal\n\r");
    int cmdID = waitForCmd();  // Waits for a command
    if (cmdID == -1) {
        printf("[Error] Command Not Recognized!\n\r");
        return;
    }
    int res = commandList[cmdID]->runCommand();
    if (res < 0) { // Error handling if 
        printf("[Error] \n\r");
    }
}

int waitForCmd() {
    char buff[100];
    int cnt = 0;
    printf("Waiting for input...\n\r $");
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
    for (int i = 0; i < NUM_COMMANDS; i++) {
        if (!strcmp(buff, commandList[i]->getName())) {
            return i;
        }
    }
    return -1;
}

uint16_t help() {
    int i;
    printf("BADGERLOOP UTILITY & TESTING TOOL\n\r"); // Sometimes I think I'm five
    printf("Commands:\n\r");
    for (i = 0; i < NUM_COMMANDS; i++) {
       printf("\t%s - %s\n\r", commandList[i]->getName(), commandList[i]->getDesc());
    }
    return 0;
}
// Command Initalizers
Command helpCmd("help", "Shows a list of commands", help);
Command read7VRailVCmd("read7VRailV", "Reads the voltage on the 7 Volt rail", read7VRailV);
Command read7VRailACmd("read7VRailA", "Reads the current on the 7 volt rail", read7VRailA);
Command readBusVCmd("readBusV", "Reads the voltage on the main power bus", readBusV);
Command readBusACmd("readBusA", "Reads the current on the main power bus", readBusA);
Command read5VRailVCmd("read5VRailV", "Reads the voltage on the 5 volt rail", read5VRailV);
Command read5VRailACmd("read5VRailA", "Reads the current on the 5 volt rail", read5VRailA);
Command readTherm1Cmd("readTherm1", "Reads the temperature on thermistor 1", readTherm1);
Command readTherm2Cmd("readTherm2", "Reads the temperature on thermistor 2", readTherm2);
Command testWriteIOXcmd("testWriteIOX", "Tests writing to every pin in the IO Expander", testWriteIOX);
Command testReadIOXcmd("testReadIOX", "Tests reading from every pin in the IO Expander", testReadIOX);
Command testRecvDataCmd("testRecvData", "Dumps data recieved over serial", testRecvData);
Command dumpDataCmd("dumpData", "Dumps local master data structure", dumpData);

