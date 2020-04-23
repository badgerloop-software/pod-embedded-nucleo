#include "mbed.h"
#include <math.h>
#include "adc128.h"
#include "boardTelem.h"
#include "data.h"
#include <stdint.h>

#define SCALAR (1.6) //(0.00097656/2) 

extern I2C i2c;
extern Data data;

static Adc adc(&i2c, railADC7Addr);

int initBoardTelem() {
    return adc.init();
}

void harvestBoardTelem() {
    data.boardTelem[BUS_V]      = readBusV();
    data.boardTelem[BUS_A]      = readBusA();
    data.boardTelem[V5_RAIL_V]  = read5VRailV();
    data.boardTelem[V5_RAIL_A]  = read5VRailA();
    data.boardTelem[V7_RAIL_V]  = read7VRailV();
    data.boardTelem[V7_RAIL_A]  = read7VRailA();
    data.boardTelem[THERM_1]    = readTherm1();
    data.boardTelem[THERM_2]    = readTherm2();
}

uint16_t readBusV() {
    return adc.readChannel(CHAN_0);
}

uint16_t readBusA() {
/*    uint16_t ret = adc.readChannel(chan);// * SCALAR;*/
    return adc.readChannel(CHAN_1);
}

uint16_t read5VRailV() {
/*    AdcChan chan = CHAN_2;*/
/*    uint16_t ret = adc.readChannel(chan) * SCALAR;*/
    return adc.readChannel(CHAN_2);
    
}

uint16_t read5VRailA() {
/*    AdcChan chan = CHAN_3;*/
/*    uint16_t ret = adc.readChannel(chan) * SCALAR;*/
    return adc.readChannel(CHAN_3);
}

uint16_t read7VRailV() {
/*    AdcChan chan = CHAN_4;*/
/*    uint16_t ret = adc.readChannel(chan) * SCALAR;*/
    return adc.readChannel(CHAN_4);
}

uint16_t read7VRailA() {
/*    AdcChan chan = CHAN_5;*/
/*    uint16_t ret = adc.readChannel(chan) * SCALAR;*/
    return adc.readChannel(CHAN_5);
}

uint16_t readTherm1() {
/*    AdcChan chan = CHAN_6;*/
/*    uint16_t ret = adc.readChannel(chan);*/
/*    ret = 1 / ((log(ret/4700) / 3500) + 0.04);*/
    return adc.readChannel(CHAN_6);
}

uint16_t readTherm2() {
/*    AdcChan chan = CHAN_7;*/
/*    uint16_t ret = adc.readChannel(chan);*/
/*    ret = 1 / ((log(ret/4700) / 3500) + 0.04);*/
    return adc.readChannel(CHAN_7);
}
