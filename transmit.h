
#ifndef TRANSMIT_H
#define TRANSMIT_H

#include "system.h"

/**
 * This transmits the sequece given in char* sequence.
 * @param char* sequence, data to be sent to the other board
 * */
void transmitSequence(char* sequence);

/**
 * Receives the data sent by transmitSequence and puts it in the
 * given char* received.
 * @param char* received, char* for the received data to go into
 * */
void receiveSequence(char* received);

/**
 * Intialises other modules or variables needed for the 
 * transmit module.
 **/
void transmit_init(void);

#endif
