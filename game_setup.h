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
void title_msg();

/**
 * Handles the matchmaking between two boards.
 * Takes an int* to determine who will start first (host).
 * Proceeds to send and receive a signal (!) when player is found.
 *
 * @param int* is_host, int to be updated to determine host
 */
void set_player(int* is_host);

/*
 * Takes an integer 'win' to choose between 3 different messages
 * depending on the result of the game.
 */
// void game_over(int win);

#endif
