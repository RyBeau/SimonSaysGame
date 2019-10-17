/*
 * Declares the functions of game_setup.c
 *
 * Authors: Raymond Tamse, Ryan Beaumont
 * Date: October 15 2019
 */

#ifndef GAME_SETUP_H
#define GAME_SETUP_H

#include "system.h"

/**
 * Simply prints "Simon Says" on the LED matrix.
 */
void title_msg(void);

/**
 * Handles the matchmaking between two boards.
 * Takes an int* to determine who will start first (host).
 * Proceeds to send and receive a signal (!) when player is found.
 *
 * @param int* is_host, int to be updated to determine host
 */
void set_player(int* is_host);

/**
 * Called when the player makes the wrong sequence.
 * Takes the char* player sequence with its size of int n,
 * and replaces the first symbol with an '!', defined as GAMEOVER
 * in game.c
 * Sequence gets transmitted to the host for checking.
 * @param char* sequence, player sequence to be updated
 */
void lose_signal(char* sequence, int n);

/**
 * Takes an integer 'win' to choose between 3 different messages
 * depending on the result of the game.
 * Uses display_text to display the result message.
 * @param char* sequence, needed for lose scenario
 */
void game_over(char* sequence, int win);

#endif
