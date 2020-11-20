#include "mbed.h"
#include "mcp23017.h"
#include "brake.h"

extern I2C i2c;

static Iox iox(&i2c, 0x20);


/* initBraking
* Pings IOX 
* Writes solenoids high for 2 seconds and then writes low
*/
int initBraking() {
    if(iox.ping() != 0) return 1;
    for (int i = 8; i < 16; i++){
        if(writePin(i, 1) != 0) return 1;
    }
    wait_us(2000000);
    for (int i = 8; i < 16; i++){
        if(writePin(i, 0) != 0) return 1;
    }
    return 0;
}

/* writePin
* Writes high or low to a designated pin
* Pin numbers (0-7)=GPIOA_0-7 and numbers (8-15)=GPIOB_0-7
* High is 1 low is 0
*/
int writePin(int pin, int val){
    I2C i2c(PB_7, PB_6);
    Iox iox(&i2c, 0x20);

    if (iox.setDir((IoxPin)pin, DIR_OUT)){
            printf("ERROR SETTING DIR\n\r");
            return 1;
    }
    if (iox.write((IoxPin)pin, (IoxVal)val)){ 
            printf("ERROR WRITING PIN\n\r");
            return 1;
    }
    return 0;
}


/* readPin
*  reads the value of a designated pin and prints to console
*/
int readPin(int pin){
    I2C i2c(PB_7, PB_6);
    Iox iox(&i2c, 0x20);
    if (iox.setDir((IoxPin)pin, DIR_IN)){
            printf("ERROR SETTING DIR\n\r");
            return 1;
    }
    printf("READ FROM PIN: %d\n\r", (int)iox.read((IoxPin)pin));
    return 0;
}


/* testBrakWrite
* writes all B pins low then high and returns 1 if error occurs
*/
uint16_t testBrakeWrite(){
    for (int i = 8; i < 16; i++){
        if(writePin(i, 0)){
            printf("ERROR WRITING LOW TO PIN %d\n\r", i);
            return 1;
        }
        if(writePin(i, 1)){
            printf("ERROR WRITING HIGH TO PIN %d\n\r", i);
            return 1;
        }
    }
    return 0;
}
/* testBrakRead
* reads from all A pins and returns 1 if error occurs
*/
uint16_t testBrakeRead(){
    for (int i = 0; i < 8; i++){
        if(readPin(i)){
            printf("ERROR READING FROM PIN %d\n\r", i);
            return 1;
        } 
    }
    return 0;
}