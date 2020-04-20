#include "mbed.h"
#include "buart.h"
#include "packet.h"
#include "data.h"

extern Data data;

int initComms() {
    // Could check connection status here?
    return 0;
}

int sendDataPacket() {
    BPacket pkt(&data);
    printf("SENDING THIS PACKET:\n\r");
    BPacket::dump(&pkt);
    writeBeagle(&pkt);
    return 0;
}

int sendCmdPacket() {
    BPacket pkt(BPacket::ACK);
    writeBeagle(&pkt);
    return 0;
}

/* TESTS */
uint16_t testRecvData() {
    char buff[34];
    uint16_t ret = (uint16_t)readBeagle(buff, 34);
    BPacket::dump(buff, 34);
    return ret;
}
