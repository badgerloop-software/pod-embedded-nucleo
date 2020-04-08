#ifndef __BADGERLOOP_UART_H__
#define __BADGERLOOP_UART_H__

#include "mbed.h"


int initChan(void);

/* TESTS */

float testChanRead(void);
float testChanSend(void);

/*********/

class BUart {
    private:
        const int BAUD = 9600;
        const int BUFF_SIZE = 512;
        RawSerial chan;
        CircularBuffer<char, 512> rxBuff;
        void callback();

    public:
        BUart();
        int read(char *buff, int len);
        void write(char *payload);
};


#endif
