#ifndef __BADGERLOOP_UART_H__
#define __BADGERLOOP_UART_H__

#include "mbed.h"
#include "packet.h"

/* TESTS */

float testChanRead(void);
float testChanSend(void);

/*********/

/* Nucleo <--> Beaglebone UART API */

/* beagleInit
 * Initializes UART connection by attaching an RX callback to the serial channel
 */

void initBeagle();


/* beagleRead 
 * @param char *buff - Places read data here
 * @param int len    - Size of the buffer
 * @return int       - The number of bytes we actually read
 * 
 * Reads data from the UART connection to the beaglebone
 */

int readBeagle(char *buff, int len);


/* beagleWrite
 * @param BPacket *pkt  - data packet to send
 *
 * Writes a data packet to the UART connection to the beaglebone
 */

void writeBeagle(BPacket *pkt);

#endif
