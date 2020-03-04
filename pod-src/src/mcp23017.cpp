#include "mbed.h"
#include <stdbool.h>
#include "mcp23017.h"

extern RawSerial pc;

class Iox {
    private:
        const int gpioa = 0x12;
        const int gpiob = 0x13;
        const int iodira = 0x00;
        const int iodirb = 0x01;
        int addr8bit;
        I2C *i2c;

        char readAllPins(int reg) {
            char cmd[1];
            cmd[0] = reg;
            i2c->write(addr8bit, cmd, 1);
            cmd[0] = 0;
            i2c->read(addr8bit, cmd, 1);
            return cmd[0];
        }

        int getPinNum(IoxPin pin) {
            return pin > GPIOA_7 ? (int) pin - GPIOB_0 : (int) pin;
        }

    public:
        const int numPins = 16;

        Iox(I2C *i2c, int addr7bit) {
            this->i2c = i2c;
            this->addr8bit = addr7bit << 1;   
        }
        
        int reset() {
            return 0;
        }

        int setDir(IoxPin pin, IoxDir dir) {
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
        
        IoxVal read(IoxPin pin) {
            int reg = pin > GPIOA_7 ? gpiob : gpioa;
            int pinNum = getPinNum(pin);
            return ((readAllPins(reg) >> pinNum) & 1) ? HIGH : LOW;
        }

        int write(IoxPin pin, IoxVal val) {
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
};


/* TESTS */
float testIOX() {
    I2C i2c(PB_7, PB_6);
    Iox iox(&i2c, 0x20);
    for (int i = 0; i < 16; i++) {
        if (iox.setDir((IoxPin)i, DIR_OUT))
            pc.printf("ERROR SETTING DIR\n\r");
        if (iox.write((IoxPin)i, HIGH)) 
            pc.printf("ERROR WRITING PIN\n\r");
        if (iox.setDir((IoxPin)i, DIR_IN))
            pc.printf("ERROR SETTING DIR\n\r");
        pc.printf("READ FROM PIN: %d\n\r", (int)iox.read((IoxPin)i));
    }
    return 0.0;
}

