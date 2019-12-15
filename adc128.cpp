#include "mbed.h"
#include "adc128.h"

extern I2C i2cbus;
extern Serial pc;

int isADCBusy(const int adc7BitAddr) {
    const int adc8BitAddr = adc7BitAddr << 1;
    
    char cmd[1];
    cmd[0] = 0x0C;
    
    if (i2cbus.write(adc8BitAddr, cmd, 1)) {
        return 1;    
    }
    
    if (i2cbus.read(adc8BitAddr, cmd, 1)) {
        return 1;    
    }
    
    /* 0x01 means its powering up, 0x02 is converting, we just generally want to know if it is free */
    return cmd[0] & 0x03; 
}

float read7VRail() {
    const int adc8BitAddr = railADC7Addr << 1;
    int i = 0x20;
    char data[2] = {0x0, 0x0};
    char telem[8][2];
    for (i = 0x20; i <= 0x27; i++) {
        char cmd[1] = {i};
        
        if (i2cbus.write(adc8BitAddr, cmd, 1)) {
            return -1;
        }
    
        if (i2cbus.read(adc8BitAddr, data, 2)) {
            return -1;
        }
    
        /* TODO remove */
        pc.printf("READ CHANNEL %#x: data[0] = %d; data[1] = %d;\n\r", i, data[0], data[1]);
        telem[i - 0x20][0] = data[0];
        telem[i - 0x20][1] = data[1];
        wait(0.05);
    }
    float out = ((float)(((0xf & telem[1][1]) << 8) | telem[1][0])) * 0.00097656 / 2;
    return out;    
}

int initADC(char *name, const int adc7BitAddr) {
    const int adc8BitAddr = adc7BitAddr << 1;
    int failCnt = 0;
    
    while(isADCBusy(adc7BitAddr)) {
        if (failCnt++ > 10) {
            return 1;   // If it is busy too long, we don't want to stop init phase    
        }
        wait(0.05);    
    }
    
    char cmd[2];
    char reg[1];
    char data[1];
    
    /* Adv Config Reg */
    reg[0] = 0x0B;
    
    if (i2cbus.write(adc8BitAddr, reg, 1)) {
        return 1;
    }
    
    if (i2cbus.read(adc8BitAddr, data, 1)) {
        return 1;
    }

    /* We always need to follow read-modify-write pattern */
    data[0] &= ~(0x07);
    data[0] |= 0x03;

    cmd[0] = reg[0];
    cmd[1] = data[0];  /* Ext ref, Mode 1 */
    
    if (i2cbus.write(adc8BitAddr, cmd, 2)) {
        return 1;
    }
    
    wait(0.1);
    
    /* Conv rate reg*/
    reg[0] = 0x07;
    
    if (i2cbus.write(adc8BitAddr, reg, 1)) {
        return 1;    
    }
    
    if (i2cbus.read(adc8BitAddr, data, 1)) {
        return 1;    
    }

    data[0] &= ~(0x01); 
    data[0] |= 0x01;    /* Cont conv */
    
    cmd[0] = reg[0];
    cmd[1] = data[0];
    
    if (i2cbus.write(adc8BitAddr, cmd, 2)) {
        return 1;
    }
   
    wait(0.1);
    
    /* Limit Regs */
/*    reg[0] = */
/*    for int*/


    /* Config Reg */
    reg[0] = 0x00;
    if (i2cbus.write(adc8BitAddr, reg, 1)) {
        return 1;
    }
    
    if (i2cbus.read(adc8BitAddr, data, 1)) {
        return 1;
    }
    wait(0.1);
    data[0] &= ~(0x09);
    data[0] |= 0x01;
    
    cmd[0] = reg[0];
    cmd[1] = data[0];

    if (i2cbus.write(adc8BitAddr, cmd, 2)) {
        return 1;
    }
    
    wait(0.1);
    
    if (i2cbus.write(adc8BitAddr, reg, 1)) {
        return 1;
    }
    
    if (i2cbus.read(adc8BitAddr, data, 1)) {
        return 1;
    }
    
    //pc.printf("CONFIG INFO DEBUG: %#x\n", data[0]);
    
    pc.printf("ADC for %s at address %#x found\n", name, adc7BitAddr); /* Should be: 0x01 */
    return 0;
}
