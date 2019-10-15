/*
 * Declares the functions of gameplay.c
 *
 * Authors: Raymond Tamse
 * Date: October 15 2019
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

/**
 * Takes two pointers char* which point to the host sequence and
 * the player sequence.
 * Compares the two sequences, and returns 1 if the sequence matches,
 * otherwise returns 0;
 *
 * @param char* received, host's sequence to be compared
 * @param char* input, player's sequence to be compared
 */
int checkSequence(char* received, char* input, int n);

/**
 * Generates a random sequence of chars
 * corresponding to all five navswitch inputs.
 *
 * @param char* sequence, sequence to be updated with random symbols
 */
void generate_sequence(char* sequence, int seq_length);

#endif
