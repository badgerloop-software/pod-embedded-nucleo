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

        handleIncoming();
        //harvestBoardTelem();
        //sendDataPacket();
        //runDebugTerminal();
    }
    return 0;
}

