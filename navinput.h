/*
 * Declares the functions of navinput.c
 *
 * Authors: Raymond Tamse
 * Date: October 14 2019
 */

 #ifndef NAVSWITCH_H
 #define NAVSWITCH_H

/* Returns '*' if a player wants to be the host
 * before the game starts.
 */
char host_input ();

/*
 * Takes a char* input that gets updated depending on the player's
 * input. Loops n times, where n/2 is the num. of symbols - the
 * other half is for spaces.
 */
void player_input (char* input, int n);

 #endif

