#include "mbed.h"
#include "boardTelem.h"
#include "brake.h"
#include "pressure.h"
#include "term.h"
#include "uart.h"
#include "post.h"

I2C i2c(PB_7, PB_6);
RawSerial pc(USBTX, USBRX);

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

