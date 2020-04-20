#include "mbed.h"
#include "uart.h"


#define BUFF_SIZE 256
#define BAUD      9600

static BufferedSerial chan(PA_9, PA_10, BAUD);
static CircularBuffer<char, BUFF_SIZE> rxBuff;

/* Be careful with this, it's fickle */
static void callback() {
    if (!rxBuff.full())
        rxBuff.push(chan.getc());
}


float testChanRead() {
    int len = 100;
    char buff[len];
    int ret = 0;
    ret = chanRead(buff, len);

    printf("RECVD: %s", buff);
    return (float) ret;
}

float testChanSend() {
    char *msg = "ping\n\r";
    pc.printf("SENT: %s", msg);
    chanSend(msg);
    return 0.0;
}

/* 
 * @param buff - character buffer where last serial message is put
 * @param len  - how many chars need to be read
 * @ret   number of chars read
 */
int chanRead(char *buff, int len) {
    NVIC_DisableIRQ(USART1_IRQn);
    for (int i = 0; i < len; i++) {
        char data;
        if (rxBuff.empty()) {
            NVIC_EnableIRQ(USART1_IRQn);
            return (float)i;
        }
        rxBuff.pop(data);
        buff[i] = data;
    }
    NVIC_EnableIRQ(USART1_IRQn);
    return (float)len;
}

int initChan() {
    chan.attach(&callback);
    return 0;
}

void chanSend(char *msg) {
    chan.write("%s", msg);
}
