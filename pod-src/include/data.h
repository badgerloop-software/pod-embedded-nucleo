#ifndef __BLOOP_DATA_H__
#define __BLOOP_DATA_H__

#include <stdint.h>

#define BUS_V 0
#define BUS_A 1
#define V5_RAIL_V 2
#define V5_RAIL_A 3
#define V7_RAIL_V 4
#define V7_RAIL_A 5
#define THERM_1 6
#define THERM_2 7


/* Data reloaded */
typedef struct Data {
    uint16_t boardTelem[8];
    uint16_t pressures[8];
} Data;

/*extern Data data;*/

#endif
