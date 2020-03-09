#include "mbed.h"
#include "boardTelem.h"
#include "brake.h"
#include "pressure.h"
#include "term.h"
#include "uart.h"

I2C i2c(PB_7, PB_6);
RawSerial pc(USBTX, USBRX);

static void Post() {
    pc.printf("========= Badgerloop Mbed Initilization Sequence =========\n\r");
    if (!initBoardTelem()) {
        pc.printf("Onboard telemetry online\n\r");
    } else {
        pc.printf("[WARN] Failed to initialize on board telemetry\n\r");
    }

    if (!initPressureTelem()) {
        pc.printf("Presssure telemetry online\n\r");
    } else {
        pc.printf("[WARN] Failed to initialize pressure telemetry\n\r");
    }

    if (!initBraking()) 
        pc.printf("Brake control online\n\r");
    else {
        pc.printf("[WARN] Failed to initialize braking IO Expander\n\r");    
    }
    
    chanInit();
    pc.printf("========= Badgerloop Mbed Initilization Complete =========\n\r");
}

int main() {
    int ledVal = 0;
    int ticks = 0;
    
    wait(0.1);
    Post(); 
    while(1) {
        runDebugTerminal();
        wait(0.1);
    }
}

