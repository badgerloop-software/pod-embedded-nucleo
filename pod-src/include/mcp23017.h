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
    GPIOB_7,
} IoxPin;

typedef enum IoxVal {
    LOW,
    HIGH
} IoxVal;

typedef enum IoxDir {
    DIR_OUT,
    DIR_IN
} IoxDir;

typedef struct Iox {
    const int numPins;
    const int gpioa;
    const int gpiob;
} Iox;

/* API */
int ioxSetup();
int ioxReset();
int ioxSetDir(IoxPin pin, IoxDir dir);
int ioxRead(IoxPin pin);
int ioxWrite(IoxPin pin, IoxVal val);

#endif
