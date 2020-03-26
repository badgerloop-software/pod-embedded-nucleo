#include "mbed.h"
#include <math.h>
#include "adc128.h"
#include "boardTelem.h"
#define SCALAR (1.6) //(0.00097656/2) 

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
    float ret = adc.readChannel(chan) * SCALAR;
    return ret;
}

float read5VRailV() {
    AdcChan chan = CHAN_2;
    float ret = adc.readChannel(chan) * SCALAR;
    return ret;
    
}

float read5VRailA() {
    AdcChan chan = CHAN_3;
    float ret = adc.readChannel(chan) * SCALAR;
    return ret;
}

float read7VRailV() {
    AdcChan chan = CHAN_4;
    float ret = adc.readChannel(chan) * SCALAR;
    return ret;
}

float read7VRailA() {
    AdcChan chan = CHAN_5;
    float ret = adc.readChannel(chan) * SCALAR;
    return ret;
}

float readTherm1() {
    AdcChan chan = CHAN_6;
    float ret = adc.readChannel(chan);
    ret = 1 / ((log(ret/4700) / 3500) + 0.04);
    return ret;
}

float readTherm2() {
    AdcChan chan = CHAN_7;
    float ret = adc.readChannel(chan);
    ret = 1 / ((log(ret/4700) / 3500) + 0.04);
    return ret;
}
