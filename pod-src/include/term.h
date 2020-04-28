#ifndef __TERM_H__
#define __TERM_H__

class Command {
    char* name;
    char* desc;
    int id;
    uint16_t (*exec)(void);
    public:
    Command(char* name, char* desc, uint16_t(*exec)(void));
    int runCommand();
    char* getName() { return name;}
    char* getDesc() { return desc;}
    int getID() { return id;}
    static int nextID;
    //uint16_t(*exec)(void);
};

void runDebugTerminal();
int waitForCmd();
uint16_t help();

#endif
