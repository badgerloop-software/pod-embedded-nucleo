#include "mbed.h"
#include "adc128.h"
#include "mcp23017.h"
#include "boardTelem.h"
#include "term.h"
#include "uart.h"

DigitalOut myled(LED1);
I2C i2c(PB_7, PB_6);
RawSerial pc(USBTX, USBRX);
Iox brakeIOX(&i2c, 0x20);

int blink(int ledVal);

int main() {
    int ledVal = 0;
    int ticks = 0;
    
    wait(0.1);
    
    initBoardTelem();
    chanInit();
    if (!brakeIOX.ping()) 
        pc.printf("Braking IOX found at address %x\n\r", brakeIOX.getAddress7());
    else {
        pc.printf("Braking IOX Not Found\n\r");    
    }
    while(1) {
        runDebugTerminal();
	ledVal = blink(ledVal);
        wait(0.1);
    }
}


int blink(int ledVal) {
    myled = ledVal;
    return !ledVal;
}
