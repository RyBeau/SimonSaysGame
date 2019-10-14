
#ifndef GAME_DISPLAY_H
#define GAME_DISPLAY_H

#include "system.h"

/**Sets the text to be display on the LED matrix using tinygl.
 * This function is for displaying information text for the game, this
 * type of text is dislplayed TEXT_MULTIPLIER times and in the TINYGL_TEXT_MODE_SCROLL
 * text mode.
 * It then calls displayUpdateLoop with the argument TEXT_MULTIPLIER * n
 * @param text The char* of text to be displayed on the LED matrix
 * @param n The length of the text to be displayed on the LED matrix
 *
 * */
void display_text(char* text, int n);


/**
 * This function sets the tinygl_text to the sequence of movements to
 * be done by the player. This is displayed in the TINGL_TEXT_MODE_STEP
 * Finally it calls the displayUpdateLoop with the argument n
 *
 * @param sequence The char* of moves to be dones by the player
 * @param n The number of characters in the sequence*/
void display_sequence(char* sequence, int n);


void gameDisplay_init(void);
#endif
