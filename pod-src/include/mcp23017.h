#ifndef __MCP23017_H__
#define __MCP23017_H__
/* Useful Constants*/

typedef enum IoxPin {
    GPIOA_0,
    GPIOA_1,
    GPIOA_2,
    GPIOA_3,
    GPIOA_4,
    GPIOA_5,
    GPIOA_6,
    GPIOA_7,
    GPIOB_0,
    GPIOB_1,
    GPIOB_2,
    GPIOB_3,
    GPIOB_4,
    GPIOB_5,
    GPIOB_6,
    GPIOB_7
} IoxPin;

typedef enum IoxVal {
    LOW,
    HIGH
} IoxVal;

typedef enum IoxDir {
    DIR_OUT,
    DIR_IN
} IoxDir;

class Iox {
    private:
        char readAllPins(int reg); 
        int getPinNum(IoxPin pin);
        const int gpioa = 0x12;
        const int gpiob = 0x13;
        const int iodira = 0x00;
        const int iodirb = 0x01;
        int addr8bit;
        I2C *i2c;
    public:
        const int numPins = 16;
        Iox(I2C *i2c, int addr7bit);
        int getAddress7(void);
        int ping(void);
        int reset(void);
        int setDir(IoxPin pin, IoxDir dir);
        IoxVal read(IoxPin pin);
        int write(IoxPin pin, IoxVal val);
};


/* API */
/*int ioxSetup();*/
/*int ioxReset();*/
/*int ioxSetDir(IoxPin pin, IoxDir dir);*/
/*int ioxRead(IoxPin pin);*/
/*int ioxWrite(IoxPin pin, IoxVal val);*/
float testWriteIOX();
float testReadIOX();
#endif
