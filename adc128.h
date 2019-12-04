#ifndef __ADC128_H__
#define __ADC128_H__

const int railADC7Addr = 0x1f;
const int presADC7Addr = 0x1d;

int initADC(char *name, const int addr);
int isADCBusy(const int addr);
int read7VRail(void);

#endif