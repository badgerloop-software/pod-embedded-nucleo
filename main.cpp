#include "mbed.h"
#include "adc128.h"
const int brakeIOX7Addr = 0x20;

DigitalOut myled(LED1);
I2C i2cbus(I2C_SDA, I2C_SCL);
Serial pc(USBTX, USBRX);

int initIOX(char *name, const int addr);
int blink(int ledVal);

int main() {
    int ledVal = 0;
    int ticks = 0;
    
    wait(0.1);
    
    initADC("Rails and Temps", railADC7Addr);
    initADC("Pressures", presADC7Addr);
    if (initIOX("Braking Solenoids", brakeIOX7Addr)) 
        pc.printf("IOX Failed: Did you check the reset pin?\n");    
    while(1) {
        if (ticks++ == 10) {
            pc.printf("7 Volt Rail: %d\n", read7VRail());
            ticks = 0;
        }
        ledVal = blink(ledVal);
        wait(0.1);
    }
}

int initIOX(char *name, const int iox7BitAddr) {
    const int iox8BitAddr = iox7BitAddr << 1;
    
    char cmd[2];
    cmd[0] = 0x05;
    cmd[1] = 0x00;
    
    if (i2cbus.write(iox8BitAddr, cmd, 2)) {
        return 1;    
    }
    
    // Doesn't prove much, just that read/write didn't fail
    pc.printf("IOX for %s at address %#x Found: manufacturer ID = %#x\n", name, iox7BitAddr, cmd[0]);    /* Should be: 0x01 */
    return 0;    
}

int blink(int ledVal) {
    myled = ledVal;
    return !ledVal;
}
