#ifndef __PRESSURE_H__
#define __PRESSURE_H__

typedef enum PresChan {
    LINE_1
} PresChan;

int initPressureTelem();
int readPressure(PresChan chan);

#endif
