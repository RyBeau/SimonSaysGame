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
void setup_title_message(void);

/**
 * Handles the matchmaking between two boards.
 * Takes an int* is_host to determine who will start first (host).
 * Proceeds to send and receive a signal (!) when player is found.
 *
 * @param int* is_host, int to be updated to determine host
 */
void setup_set_player(int* is_host);

#endif
