#include "mbed.h"
#include "uart.h"


#define BUFF_SIZE 256
#define BAUD      9600

static RawSerial chan(PA_9, PA_10, BAUD);
extern RawSerial pc;
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
    memset(buff, 0, len); 
    ret = chanRead(buff, len);

    pc.printf("RECVD: %s", buff);
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

void chanInit() {
    chan.attach(&callback);
}

void chanSend(char *msg) {
    chan.printf("%s", msg);
}
