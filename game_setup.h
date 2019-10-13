/*
 * Declares the functions of game_setup.c
 * Currently lacks function comments.
 *
 * Authors: Raymond Tamse, Ryan Beaumont
 * Date: October 9 2019
 */

#include "system.h"

/* Simply prints "Simon Says" on the LED matrix.
 */
void title_msg();

/*
 * Expects to receive '*' or '!' through IR to determine
 * who the host and the player is.
 * If person receives '*', trasmit '!' - person is player.
 * If person receives '!', start game - person is host.
 * Uses transmit.c for IR communication.
 */
void set_player();

/*
 * Takes an integer 'win' to choose between 3 different messages
 * depending on the result of the game.
 * Uses display_text to display the result message.
 */
void game_over(int win);
