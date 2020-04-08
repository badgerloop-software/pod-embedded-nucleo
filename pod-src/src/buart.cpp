#include "mbed.h"
#include "buart.h"
#include "packet.h"

void BUart::callback() {
    if (!rxBuff.full())
        rxBuff.push(chan.getc());
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
    (this->chan).printf("%s", pkt->getPayload());
}
