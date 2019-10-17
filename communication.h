
#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "system.h"

/**
 * This transmits the sequece given in char* sequence.
 * @param char* sequence, data to be sent to the other board
 * */
void transmitSequence(char* sequence, int n);

/**
 * Receives the data sent by transmitSequence and puts it in the
 * given char* received.
 * @param char* received, char* for the received data to go into
 * */
void receiveSequence(char* received, int n);

/**
 * Intialises other modules or variables needed for the 
 * transmit module.
 **/
void communication_init(void);

#endif