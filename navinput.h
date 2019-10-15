/*
 * Declares the functions of navinput.c
 *
 * Authors: Raymond Tamse, Ryan beaumont
 * Date: October 15 2019
 */

 #ifndef NAVSWITCH_H
 #define NAVSWITCH_H

/**
 * Takes a char* input that gets updated depending on the player's
 * input. Loops n times, where n/2 is the num. of symbols - the
 * other half is for spaces.
 * @param char* input, player sequence to be updated with input
 */
void player_input (char* input, int n);

 #endif

