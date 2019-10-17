/*
 * Declares the functions of navinput.c
 *
 * Authors: Raymond Tamse, Ryan beaumont
 * Date: October 15 2019
 */

 #ifndef NAVINPUT_H
 #define NAVINPUT_H

#include "system.h"

/**
 * Takes a char* sequence that gets updated depending on the player's
 * sequence. Loops n times, where n/2 is the num. of symbols - the
 * other half is for spaces.
 * @param char* sequence, player sequence to be updated with sequence
 */
void player_input(char* sequence, int current_size);

 #endif

