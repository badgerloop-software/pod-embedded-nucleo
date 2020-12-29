#include "mbed.h"
#include "buart.h"
#include "packet.h"
#include <cstdint>
#include <cstring>


static const int BAUD = 9600;
static int isInit = 0;


static UnbufferedSerial beagle(PA_9, PA_10, BAUD);

int commandIncoming = 0;
int dataIncoming = 0;


void callback() {
    if (!rxBuff.full()) {
        char buff[1];
        beagle.read(buff, 1);
        rxBuff.push(buff[0]);
        
        char checkBuff;
        rxBuff.peek(checkBuff);
        if(checkBuff == 'c') commandIncoming = 1;
        if(checkBuff == 'd') dataIncoming = 1;
    }
}

int initBeagle() { 
    void (*fptr)() = (void (*)()) &callback;
    beagle.attach(fptr);
    
    if(testConnection() != 0){
        isInit = 0;
        return 1;
    }
    isInit = 1;
    return 0;
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
    if (isInit != 1) return;
    beagle.write(pkt->getPayload(), pkt->getSize());   
}
/* testChanRead
 * reads from rxBuff and ensures ACKACK was received
 */
uint16_t  testChanRead(){
    char buff[3];
    readBeagle(buff, 3);
    printf("read: %s\n", buff);
    if(buff[2] != 'k') return 1;
    return 0;
}

/* testChanSend
 * sends ACK to beagle
 */
uint16_t  testChanSend(){
    BPacket ack = BPacket(BPacket::ACK);
    writeBeagle(&ack);
    
    return 0;
}
/* testConnection
 * Calls testChanRead and testChanSend to send an ACK command to the beagle and ensures ACKACK is received
 */
uint16_t testConnection(){
    if(testChanSend() != 0) return 1;
    while(rxBuff.size() < 3){
        continue;
    }
    if(testChanRead() != 0) return 1;
    return 0;
}

