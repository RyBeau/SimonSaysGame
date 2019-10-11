/*
 * Declares the functions of navinput.c
 * Currently lacks function comments.
 *
 * Authors: Raymond Tamse, Ryan Beaumont
 * Date: October 9 2019
 */

 #ifndef NAVSWITCH_H
 #define NAVSWITCH_H

/*
 * Returns either !, ", #, $, or %, which all correspond to
 * one of the four arrows and the dot, depending on the player's input
 * from the navswitch. Uses a while loop.
 */
char player_input ();

/* Takes an integer 'seq_num' to record the required amount of characters.
 * Uses a char to record a sequence of characters using the navswitch.
 * Calls 'player_input()' for the characters.
 * Returns the head of the sequence when it finishes looping
 * for 'seq_num' times. Uses a for loop.
 */
char player_sequence (int seq_num);

 #endif

