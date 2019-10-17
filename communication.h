/**
 * @author Ryan Beaumont
 * @author Raymond Tamse
 * @date 11/10/2019
 * @brief Header file for communication.c, definitions of function for
 * interboard communication of sequences.
 * */

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "system.h"

/**
 * This transmits the sequece given in char* sequence.
 * @param char* sequence, data to be sent to the other board
 * */
void comm_transmit_sequence(char* sequence, int n);

/**
 * Receives the data sent by comm_transmit_sequence and puts it in the
 * given char* received.
 * @param char* received, char* for the received data to go into
 * */
void comm_receive_sequence(char* received, int n);

/**
 * Intialises other modules or variables needed for the 
 * transmit module.
 **/
void communication_init(void);

#endif
