#ifndef __BADGERLOOP_UART_H__
#define __BADGERLOOP_UART_H__

#include "mbed.h"
#include "packet.h"
#include <cstdint>

extern int commandIncoming; //1 when a command packet is in rxBuff
extern int dataIncoming; //1 when a data packet is in rxBuff


static const int BUFF_SIZE = 512;
static CircularBuffer<char, BUFF_SIZE> rxBuff;

/* TESTS */

/* testConnection
 * Calls testChanRead and testChanSend to send an ACK command to the beagle and ensures ACKACK is received
 */
uint16_t testConnection(void);

/* testChanRead
 * reads from rxBuff and ensures ACKACK was received
 */
uint16_t  testChanRead(void);

/* testChanSend
 * sends ACK to beagle
 */
uint16_t  testChanSend(void);

/*********/

/* Nucleo <--> Beaglebone UART API */

/* beagleInit
 * Initializes UART connection by attaching an RX callback to the serial channel
 * Runs connection test
 */

int initBeagle();


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
