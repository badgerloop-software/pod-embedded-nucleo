#include "mbed.h"
#include "boardTelem.h"
#include "brake.h"
#include "pressure.h"
#include "term.h"
#include "uart.h"
#include "post.h"

I2C i2c(PB_7, PB_6);
BufferedSerial pc(USBTX, USBRX);

/* Allows you to print to your console with Mbed6 */
FileHandle *mbed::mbed_override_console(int fd)
{
    return &pc;
}


int main() {
    int ledVal = 0;
    int ticks = 0;
    
    Post(); 
    while(1) {
        runDebugTerminal();
    }
}

