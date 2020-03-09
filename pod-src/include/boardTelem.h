#ifndef __BOARD_TELEM_H__
#define __BOARD_TELEM_H__

int initBoardTelem();

float readBusV();
float readBusA();
float read5VRailV();
float read5VRailA();
float read7VRailA();
float read7VRailV();

#endif
