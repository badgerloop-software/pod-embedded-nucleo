#include "mbed.h"
#include "data.h"

extern Data data;

uint16_t dumpData() {
    printf("GEN BOARD TELEM:\n\r");
    printf("Raw Bus Voltage: %4u || Raw Bus Current: %4u\n\r", data.boardTelem[0], data.boardTelem[1]);
    printf("Raw 5V Voltage: %4u || Raw 5V Rail Current: %4u\n\r", data.boardTelem[2], data.boardTelem[3]);
    printf("Raw 7V Voltage: %4u || Raw 7V Rail Current: %4u\n\r", data.boardTelem[4], data.boardTelem[5]);
    printf("Raw Temperature 1: %4u || Raw Temperature 2: %4u\n\r", data.boardTelem[6], data.boardTelem[7]);
    printf("PRESSURES:\n\r");
    for (int i = 0; i < 8; i++) {
        printf("%d : %u\n\r", i, data.pressures[i]);
    }
    return 0;
}
