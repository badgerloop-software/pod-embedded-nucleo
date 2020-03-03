#ifndef __BADGERLOOP_UART_H__
#define __BADGERLOOP_UART_H__

void chanInit(void);

/* TESTS */

float testChanRead(void);
float testChanSend(void);

/*********/

int chanRead(char *buff, int len);
void chanSend(char *msg);

#endif
