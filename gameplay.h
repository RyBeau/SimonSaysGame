/*
 * Declares the functions of gameplay.c
 *
 * Authors: Raymond Tamse
 * Date: October 14 2019
 */

#ifndef GAMEPLAY_H
#define GAMEPLAY_H

/*
 * Takes an int 'is_host' to determine whether the player should
 * call the function 'generate_sequence' to generate a random sequence.
 * Displays a countdown prompt on the LED matrix before the game begins.
 */
 /**
void begin_game(int is_host);
*/

/*
 * Handles the sequence communication between player and host.
 * If host, generated sequence is displayed (if possible ???) and
 * also transmitted to the player.
 * If player, await input (if possible ???)
 *
 * Current concern over the program working with 2 while loops?
 */
 /**
void sequence_comms(char* host_seq, char* player_seq);
*/

/*
 * Generates a random sequence of chars
 * corresponding to all five navswitch inputs.
 */
void generate_sequence(char* sequence, int seq_length);

#endif
