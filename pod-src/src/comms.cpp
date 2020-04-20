#include "mbed.h"
#include "buart.h"
#include "packet.h"
#include "data.h"

extern Data data;
static BUart beagle;

int initComms() {
    // Could check connection status here?
    return 0;
}

int sendDataPacket() {
    BPacket pkt(&data);
    beagle.write(&pkt);
    return 0;
}

int sendCmdPacket() {
    BPacket pkt(BPacket::ACK);
    beagle.write(&pkt);
    return 0;
}

/* TESTS */
uint16_t testRecvData() {
    char buff[34];
    uint16_t ret = (uint16_t)beagle.read(buff, 34);
    printf("DATA RECVD: %s\n\r", buff);
    return ret;
}
