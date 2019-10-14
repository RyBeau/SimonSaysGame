/**
 * @file game_display.c
 * @author Ryan Beaumont
 * @date 9/10/2019
 * @brief Display on LED Matrix
 * @note This module contains functions for display game info on screen
 * */
#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "font5x7_1_arrows.h"


#define PACER_RATE 500 //Rate for the paced loop
#define MESSAGE_RATE 30 //Speed of message for tinygl
#define PLAYBACK_RATE MESSAGE_RATE / 10 //Message rate per second
#define TEXT_MULTIPLIER 2 //Times to replay information text

/**
 * Clears and updates the LED matrix
 * */
static void matrixClear(void)
{
    tinygl_clear();
    tinygl_update();

}

/**Converts the wantedHz to a number of loops of the PACER_RATE
 * to allow for different loop pacing.
 * @param wantedHz the desired rate for the loop to run at.
 * @return Number of loops to get the wantedHz*/
static int makeSameHz(int wantedHz)
{
    return PACER_RATE / wantedHz;
}

/**The function is the loop for dislaying the text set using tinygl_text
 * It will loop for as long as need to display n letters on the matrix.
 * Then clear the matrix after.
 * @param n The number of letters in the sequence to display*/
static void displayUpdateLoop(int n)
{
    int loopFor = n * makeSameHz(PLAYBACK_RATE);
    int counter = 0;
    while(counter <= loopFor) {
        tinygl_update();
        pacer_wait();
        counter++;
    }
    matrixClear();
}

/**Sets the text to be display on the LED matrix using tinygl.
 * This function is for displaying information text for the game, this
 * type of text is dislplayed TEXT_MULTIPLIER times and in the TINYGL_TEXT_MODE_SCROLL
 * text mode.
 * It then calls displayUpdateLoop with the argument TEXT_MULTIPLIER * n
 * @param text The char* of text to be displayed on the LED matrix
 * @param n The length of the text to be displayed on the LED matrix
 *
 * */
void display_text(char* text, int n)
{
    tinygl_text(text);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    displayUpdateLoop(TEXT_MULTIPLIER * n);
}


/**
 * This function sets the tinygl_text to the sequence of movements to
 * be done by the player. This is displayed in the TINGL_TEXT_MODE_STEP
 * Finally it calls the displayUpdateLoop with the argument n
 *
 * @param sequence The char* of moves to be dones by the player
 * @param n The number of characters in the sequence*/
void display_sequence(char* sequence, int n)
{
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    tinygl_text(sequence);
    displayUpdateLoop(n);
}

/**
 * Intialises other modules or variables needed for the
 * game_display module.
 **/
void gameDisplay_init (void)
{
    system_init ();
    tinygl_init (PACER_RATE);
    tinygl_font_set (font5x7_1_arrows);
    tinygl_text_speed_set(MESSAGE_RATE);
}
