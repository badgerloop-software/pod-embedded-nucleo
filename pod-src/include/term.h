#ifndef __TERM_H__
#define __TERM_H__

class Command {
    std::string name;
    std::string desc;
    int id;
    static int nextID;
    public:
    Command(string name, string desc, uint16_t exec);
    int runCommand();
    string getName() { return name;}
    string getDesc() { return desc;}
    int getID() { return id;}
  //  uint16_t(*exec)(void);
};

void runDebugTerminal();
int waitForCmd();
uint16_t help();

#endif
