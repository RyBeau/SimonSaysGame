/**
 * @file display.c
 * @author Ryan Beaumont
 * @date 9/10/2019
 * @brief
 * @note This module contains functions for display game info on screen
 * */
#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "font5x7_1_arrows.h"


#define PACER_RATE 500
#define MESSAGE_RATE 30
#define PLAYBACK_RATE MESSAGE_RATE / 10
#define TEXT_MULTIPLIER 2

void matrixClear(void)
{
    tinygl_clear();
    tinygl_update();

}

int makeSameHz(int wantedHz)
{
    return PACER_RATE / wantedHz;
}

void displayUpdateLoop(int n)
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

void display_text(char* text, int n)
{
    tinygl_text(text);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    displayUpdateLoop(TEXT_MULTIPLIER * n);
}



void display_sequence(char* sequence, int n)
{
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    tinygl_text(sequence);
    displayUpdateLoop(n);
}

int main (void)
{
    system_init ();
    timer_init();
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1_arrows);
    tinygl_text_speed_set(MESSAGE_RATE);

    pacer_init (PACER_RATE);
    char sequence[14] = "^ ^ ^ ^ ";
    display_sequence(sequence, 8);
    display_text("You Win! ", 9);
    display_sequence(sequence, 8);
    return 0;
}
