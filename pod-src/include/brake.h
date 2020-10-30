#ifndef __BRAKE_H__
#define __BRAKE_H__

int initBraking(void);
int writePin(int, int);
int readPin(int);
uint16_t testBrakeWrite(void);
uint16_t testBrakeRead(void);
#endif
