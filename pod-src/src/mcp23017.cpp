#include "mbed.h"
#include <stdbool.h>
#include "mcp23017.h"

extern RawSerial pc;

char Iox::readAllPins(int reg) {
    char cmd[1];
    cmd[0] = reg;
    i2c->write(addr8bit, cmd, 1);
    cmd[0] = 0;
    i2c->read(addr8bit, cmd, 1);
    return cmd[0];
}

int Iox::getPinNum(IoxPin pin) {
    return pin > GPIOA_7 ? (int) pin - GPIOB_0 : (int) pin;
}


Iox::Iox(I2C *i2c, int addr7bit) {
    this->i2c = i2c;
    this->addr8bit = addr7bit << 1;   
}

int Iox::getAddress7() {
    return addr8bit >> 1;
}

int Iox::ping() {
    char cmd[2];
    cmd[0] = 0x05;
    cmd[1] = 0x00;

    /* Gets Manufac. ID, not sure if we care */
    if (i2c->write(addr8bit, cmd, 2)) {
        return 1;
    }

    return 0;
}

int Iox::reset() {
    return 0;
}

int Iox::setDir(IoxPin pin, IoxDir dir) {
    int reg = pin > GPIOA_7 ? iodirb : iodira;
    char cmd[2];
    cmd[0] = reg;
    if (dir == DIR_OUT) {
        cmd[1] = readAllPins(reg) & ~(1 << getPinNum(pin));
    } else {
        cmd[1] = readAllPins(reg) | (1 << getPinNum(pin));
    }
    return i2c->write(addr8bit, cmd, 2);
}

IoxVal Iox::read(IoxPin pin) {
    int reg = pin > GPIOA_7 ? gpiob : gpioa;
    int pinNum = getPinNum(pin);
    return ((readAllPins(reg) >> pinNum) & 1) ? HIGH : LOW;
}

int Iox::write(IoxPin pin, IoxVal val) {
    char cmd[2];
    int reg = pin > GPIOA_7 ? gpiob : gpioa;
    int pinNum = getPinNum(pin);
    cmd[0] = reg;
    if (val == HIGH) {
        cmd[1] = readAllPins(reg) | (1 << pinNum);
    } else {
        cmd[1] = readAllPins(reg) & ~(1 << pinNum);
    }
    return i2c->write(addr8bit, cmd, 2);
}


/* TESTS */
float testWriteIOX() {
    I2C i2c(PB_7, PB_6);
    Iox iox(&i2c, 0x20);
    for (int i = 0; i < 16; i++) {
        if (iox.setDir((IoxPin)i, DIR_OUT))
            pc.printf("ERROR SETTING DIR\n\r");
        if (iox.write((IoxPin)i, HIGH)) 
            pc.printf("ERROR WRITING PIN\n\r");
    }
    return 0.0;
}

float testReadIOX() {
    I2C i2c(PB_7, PB_6);
    Iox iox(&i2c, 0x20);
    for (int i = 0; i < 16; i++) {
        if (iox.setDir((IoxPin)i, DIR_IN))
            pc.printf("ERROR SETTING DIR\n\r");
        pc.printf("READ FROM PIN: %d\n\r", (int)iox.read((IoxPin)i));
    }
    return 0.0;

}
