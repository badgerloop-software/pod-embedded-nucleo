#include "mbed.h"
#include "buart.h"
#include "packet.h"

void BUart::callback() {
    if (!rxBuff.full()) {
        char buff[1];
        chan.read(buff, 1);
        rxBuff.push(buff[0]);
    }
}

BUart::BUart() : chan(PA_9, PA_10, BAUD) {
    void (*fptr)() = (void (*)())(&BUart::callback);
    (this->chan).attach(fptr);
}

int BUart::read(char *buff, int len) {
    NVIC_DisableIRQ(USART1_IRQn);
    for (int i = 0; i < len; i++) {
        char data;
        if ((this->rxBuff).empty()) {
            NVIC_EnableIRQ(USART1_IRQn);
            return i;
        }
        (this->rxBuff).pop(data);
        buff[i] = data;
    }
    NVIC_EnableIRQ(USART1_IRQn);
    return len;
}

void BUart::write(BPacket *pkt) {
    (this->chan).write(pkt->getPayload(), pkt->getSize());
}
