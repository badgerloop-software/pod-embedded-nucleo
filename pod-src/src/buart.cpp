#include "mbed.h"
#include "buart.h"
#include "packet.h"
#include "brake.h"
#include <cstdint>
#include <cstdio>
#include <cstring>


static const int BAUD = 9600;
static const int BUFF_SIZE = 512;
static int isInit = 0;

static UnbufferedSerial beagle(PA_9, PA_10, BAUD);
static CircularBuffer<char, BUFF_SIZE> rxBuff;

int commandIncoming = 0;
int dataIncoming = 0;

void callback() {
    if (!rxBuff.full()) {
        char buff[1];
        beagle.read(buff, 1);
        rxBuff.push(buff[0]);

        if(buff[0] == 'c'){
            commandIncoming = 1;
        }else if (buff[0] == 'd') {
            dataIncoming = 1;
        }
    }
}

int initBeagle() { 
    void (*fptr)() = (void (*)()) &callback;
    beagle.attach(fptr);
    isInit = 1;
    if(testConnection() != 0){
        isInit = 0;
        return 1;
    }
    
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


/* handleIncoming
 * Handles incoming data and command packets from beaglebone
 */
int handleIncoming(){
    //return 0 if no data or commands were reveived
    if(commandIncoming == 0 && dataIncoming == 0){
        return 0;
    }

    //handle command when received
    if(commandIncoming == 1){   
        //wait for full command
        if(rxBuff.size() < 3) wait_us(250000); //TODO: FIGURE OUT HOW LONG IT SHOULD TAKE TO WAIT FOR THE COMMAND
        if(rxBuff.size() <3) return 1; //ERROR: command not received
        char buff[3];
        readBeagle(buff, 3);
        BPacket cmd = BPacket::ACK;
        switch (buff[2]){
            //brake
            case 'b':{
                    printf("BRAKING\n");
                    if(brake() != 0){
                        return 1;
                    } 
                    else writeBeagle(&cmd);
                    return 0;
                }
            //unbrake
            case 'u':{
                    printf("UNBRAKING\n");
                    if(unBrake() != 0){
                        return 1;
                    }
                    else writeBeagle(&cmd);
                    return 0;
                }
            //ack
            case 'a':{
                    printf("ACK Received\n");
                    BPacket ackack = BPacket::ACKACK;
                    writeBeagle(&ackack);
                    return 0;
                }
            //ackack
            case 'k':{
                printf("ACKACK Received\n");
                return 0;
            }
            //anything else
            default:{
                printf("INVALID command received\n");
                BPacket invalid = BPacket::INVALID;
                writeBeagle(&invalid);
                return 1;
            }
        }
    }

    //TODO: handle incoming data if necessarry
    if(dataIncoming == 1){
        return 0;
    }

    return 1;
}