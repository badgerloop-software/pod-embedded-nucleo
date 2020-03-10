#include "mbed.h"
#include "adc128.h"
#include "boardTelem.h"
#define SCALAR (0.00097656/2) 

extern I2C i2c;

static Adc adc(&i2c, railADC7Addr);

int initBoardTelem() {
    return adc.init();
}

float readBusV() {
    AdcChan chan = CHAN_0;
}

float readBusA() {
    AdcChan chan = CHAN_1;
    if (adc.isBusy()) {
        return -1;
    }
    
    float ret = adc.readChannel(chan) * SCALAR;
    return ret;
}

float read5VRailV() {
    AdcChan chan = CHAN_2;
    if (adc.isBusy()) {
        return -1;
    }
    
    float ret = adc.readChannel(chan) * SCALAR;
    return ret;
    
}

float read5VRailA() {
    AdcChan chan = CHAN_3;

    if (adc.isBusy()) {
        return -1;
    }
    
    float ret = adc.readChannel(chan) * SCALAR;
    return ret;
}

float read7VRailV() {
    AdcChan chan = CHAN_4;
    if (adc.isBusy()) {
        return -1;
    }
    float ret = adc.readChannel(chan) * SCALAR;
    return ret;
}

float read7VRailA() {
    AdcChan chan = CHAN_5;
    if (adc.isBusy()) {
        return -1;
    }
    
    float ret = adc.readChannel(chan) * SCALAR;
    return ret;
}

float readTherm1() {
    AdcChan chan = CHAN_6;
    if (adc.isBusy()) {
        return -1;
    }

    float ret = adc.readChannel(chan) * SCALAR;
    return ret;
}

float readTherm2() {
    AdcChan chan = CHAN_7;
    if (adc.isBusy()) {
        return -1;
    }
    
    float ret = adc.readChannel(chan) * SCALAR;
    return ret;
}
