#ifndef __TERM_H__
#define __TERM_H__

void runDebugTerminal(Serial *pc);
int waitForCmd(Serial *pc);
float callCmd(Serial *pc, int cmd);

#endif
