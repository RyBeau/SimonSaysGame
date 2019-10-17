/**
 * @file game_display.c
 * @author Ryan Beaumont
 * @author Raymond Tamse
 * @date 9/10/2019
 * @brief Display on LED Matrix
 * @note This module contains functions for displaying game infomation on screen
 * */
#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "font5x7_1_arrows.h"
#include <stdlib.h>


#define PACER_RATE 500 //Rate for the paced loop
#define MESSAGE_RATE 30 //Speed of message for tinygl
#define PLAYBACK_RATE MESSAGE_RATE / 10 //Message rate per second
#define TEXT_MULTIPLIER 2 //Times to replay information text

/**
 * Clears and updates the LED matrix
 * */
static void display_matrix_clear(void)
{
    tinygl_clear();
    tinygl_update();

}

/**Converts the wanted_rate to a number of loops of the PACER_RATE
 * to calculate the number of loops to display text at a given
 * playback rate.
 * @param wanted_rate the desired rate for the loop to run at.
 * @return Number of loops to get the wanted_rate*/
static int display_get_loops(int wanted_rate)
{
    return PACER_RATE / wanted_rate;
}

/**The function is the loop for dislaying the text set using tinygl_text
 * It will loop for as long as need to display n letters on the matrix.
 * Then clear the matrix after.
 * @param n The number of letters in the sequence to display*/
static void display_update_loop(int n)
{
    int loop_for = n * display_get_loops(PLAYBACK_RATE);
    int counter = 0;
    while(counter <= loop_for) {
        tinygl_update();
        pacer_wait();
        counter++;
    }
    display_matrix_clear();
}

/**
 * This function is for displaying information text for the game, this
 * type of text is dislplayed TEXT_MULTIPLIER times and in the TINYGL_TEXT_MODE_SCROLL
 * text mode.
 * It then calls display_update_loop with the argument TEXT_MULTIPLIER * n
 * @param text The char* of text to be displayed on the LED matrix
 * @param n The length of the text to be displayed on the LED matrix
 *
 * */
void display_text(char* text, int n)
{
    tinygl_text(text);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    display_update_loop(TEXT_MULTIPLIER * n);
}


/**
 * This function sets the tinygl_text to the sequence of movements to
 * be done by the player. This is displayed in the TINGL_TEXT_MODE_STEP
 * Finally it calls the display_update_loop with the argument n
 *
 * @param sequence The char* of moves to be dones by the player
 * @param n The number of characters in the sequence*/
void display_sequence(char* sequence, int n)
{
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    tinygl_text(sequence);
    display_update_loop(n);
}

/**
 * Displays a given integer on the LED Matrix by converting using itoa()
 * it to a char* that can be sent to display_sequence
 * 
 * @param int int_to_display, the integer to be displayed
 * */
void display_int(int int_to_display)
{
	int length = 2;
	int base = 10;
	char char_of_int[length];
	itoa(int_to_display, char_of_int, base);
	display_sequence(char_of_int, length);
}

/**
 * Intialises other modules or variables needed for the
 * game_display module.
 **/
void game_display_init (void)
{
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1_arrows);
    tinygl_text_speed_set(MESSAGE_RATE);
}
