#include "mbed.h"
#include "boardTelem.h"
#include "brake.h"
#include "pressure.h"
#include "term.h"
#include "buart.h"
#include "post.h"
#include "data.h"
#include "comms.h"
#include <cstdio>

I2C i2c(PB_7, PB_6);
Data data = {.boardTelem={0,0,0,0,0,0,0,0}, .pressures={0,0,0,0,0,0,0,0}};

int main() {
    int ledVal = 0;
    int ticks = 0;
    
    Post();
    while(1) {
        // if(commandIncoming == 1){
        //     //printf("Command incoming. rxBuff size : %d\n", rxBuff.size());
        //     if (rxBuff.size() >= 3){
        //         printf("reading buff\n");
        //         char buff[3];
        //         readBeagle(buff, 3);
        //         BPacket cmd = BPacket::ACK;
        //         switch (buff[2]){
        //             case 'b':{
        //                     if(brake() != 0); //TODO: Signal error
        //                     else writeBeagle(&cmd);

        //                     //for test REMOVE
        //                     wait_us(2000000);
        //                     char read[3];
        //                     readBeagle(read, 3);
        //                     printf("Read %s \n", read);
        //                     break;
        //                 }
        //             case 'u':{
        //                     if(unBrake() != 0); //TODO: Signal error
        //                     else writeBeagle(&cmd);
        //                     break;
        //                 }
        //             case 'a':{
        //                     BPacket ackack = BPacket::ACKACK;
        //                     writeBeagle(&ackack);
        //                     break;
        //                 }
        //             case 'k':{
        //                 break;
        //             }
        //             default:{
        //                 BPacket invalid = BPacket::INVALID;
        //                 writeBeagle(&invalid);
        //             }

        //         }
        //     }
        // }


        // //TODO: Handle incoming data packets if we even need to
        // if(dataIncoming == 1){
        //     continue;
        // }

        harvestBoardTelem();
        sendDataPacket();
        runDebugTerminal();
    }
    return 0;
}

