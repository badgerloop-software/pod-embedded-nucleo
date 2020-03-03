#include "mbed.h"
#include <stdbool.h>
#include "mcp23017.h"

/*I2C i2c(p28, p27);*/

/* Mbed i2c uses 8 bit addr, might need to shift */
const int addr = 0x20; // FIXME This might not be right?

const Iox iox = {.numPins = 16, .gpioa = 0x12, .gpiob = 0x13};

int ioxSetup() {
    return 0;
}

int ioxReset() {
    /* TODO */
    return 0;
}

int ioxSetDir(IoxPin pin, IoxDir dir) {
    /* TODO */
    return 0;
}

int ioxRead(IoxPin pin) {
    /* TODO */
    return 0;
}

int ioxWrite(IoxPin pin, IoxVal val) {
    /* TODO */
    return 0;
}
