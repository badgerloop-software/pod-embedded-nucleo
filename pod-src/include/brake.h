#ifndef __BRAKE_H__
#define __BRAKE_H__



/* initBraking
* Pings IOX 
* Writes solenoids high for 2 seconds and then writes low
*/
int initBraking(void);



/* writePin
* Writes high or low to a designated pin
* Pin numbers (0-7)=GPIOA_0-7 and numbers (8-15)=GPIOB_0-7
* High is 1 low is 0
*/
int writePin(int, int);

/* readPin
*  reads the value of a designated pin and prints to console
*/
int readPin(int);

/* brake
* writes solenoid pins high to engage brakes
* returns 1 if error
*/
int brake();

/* unbrake
* writes solenoid pins low to release brakes
* returns 1 if error
*/
int unBrake();

/* testBrakWrite
* writes all B pins low then high and returns 1 if error occurs
*/
uint16_t testBrakeWrite(void);

/* testBrakRead
* reads from all A pins and returns 1 if error occurs
*/
uint16_t testBrakeRead(void);


#endif