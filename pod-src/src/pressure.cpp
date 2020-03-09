#include "mbed.h"
#include "adc128.h"
#include "pressure.h"

#define SCALAR (0.0)

extern I2C i2c;

static Adc adc(&i2c, presADC7Addr);

int initPressureTelem(){ 
    return adc.init();
}

int readPressure(PresChan chan) {
    switch (chan) {
        /* TODO: Add an option for each thing in the enum */ 
        default:
            return 0;
    }
}
