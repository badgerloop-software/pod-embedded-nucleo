#include "mbed.h"
#include "buart.h"
#include "packet.h"


static const int BAUD = 9600;
static const int BUFF_SIZE = 512;
static int isInit = 0;

static UnbufferedSerial beagle(PA_9, PA_10, BAUD);
static CircularBuffer<char, BUFF_SIZE> rxBuff;

void callback() {
    if (!rxBuff.full()) {
        char buff[1];
        beagle.read(buff, 1);
        rxBuff.push(buff[0]);
    }
}

void initBeagle() { 
    void (*fptr)() = (void (*)()) &callback;
    beagle.attach(fptr);
    isInit = 1;
}

int readBeagle(char *buff, int len) {
    if (!isInit) return -1;
    NVIC_DisableIRQ(USART1_IRQn);
    for (int i = 0; i < len; i++) {
        char data;
        if (rxBuff.empty()) {
            NVIC_EnableIRQ(USART1_IRQn);
            return i;
        }
        rxBuff.pop(data);
        buff[i] = data;
    }
    NVIC_EnableIRQ(USART1_IRQn);
    return len;
}

void writeBeagle(BPacket *pkt) {
    if (!isInit) return;
    beagle.write(pkt->getPayload(), pkt->getSize());
}
