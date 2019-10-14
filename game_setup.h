/*
 * Declares the functions of game_setup.c
 *
 * Authors: Raymond Tamse
 * Date: October 13 2019
 */

#ifndef GAME_SETUP_H
#define GAME_SETUP_H

#include "system.h"

/*
 * Simply prints "Simon Says" on the LED matrix.
 */
void title_msg();

/*
 * Expects to receive '*' or '!' through IR to determine
 * who the host and the player is.
 * If person receives '*', trasmit '!' - person is player.
 * If person receives '!', start game - person is host.
 * Uses transmit.c for IR communication.
 * Returns an int that tells if the player is a host.
 */
int set_player();

/*
 * Takes an integer 'win' to choose between 3 different messages
 * depending on the result of the game.
 */
void game_over(int win);

#endif
