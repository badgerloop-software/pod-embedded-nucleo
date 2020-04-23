#include "mbed.h"
#include "mcp23017.h"
#include "brake.h"

extern I2C i2c;

static Iox iox(&i2c, 0x20);

int initBraking() {
    return iox.ping();
}
