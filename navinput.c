/*
 * Implements navswitch and stores the player's input sequence.
 * Currently contains code copies from existing lab files.
 * Makes use of game_display to display the player's input sequence.
 *
 * Authors: Raymond Tamse
 * Date: October 13 2019
 */

#include <stdio.h>
#include <string.h>
#include "system.h"
#include "navswitch.h"
#include "game_display.h"


#define SEQ_MAX 20

/* Returns '*' if a player wants to be the host
 * before the game starts.
 */
char host_input(void)
{
    char input_char = 'A';
    if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
        input_char = '*';
    }
    return input_char;
}

/*
 * Returns either !, ", #, $, or %, which all correspond to
 * one of the four arrows and the dot, depending on the player's input
 * from the navswitch.
 * Displays the character's input on the LED matrix using game_display.
 */
char player_input(void)
{
    char input_char = 'A';
    // Arrows; clockwise starting from North
    while (input_char == 'A') {
        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            input_char = '^';
        }

        if (navswitch_push_event_p (NAVSWITCH_EAST)) {
            input_char = '>';
        }

        if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            input_char = '.';
        }

        if (navswitch_push_event_p (NAVSWITCH_WEST)) {
            input_char = '<';
        }

        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            input_char = '*';    // dot
        }
    }
    display_text(&input_char, 2);
    navswitch_update();
    return input_char;
}

/* Takes an integer 'seq_num' to record the required amount of characters.
 * Uses a char to record a sequence of characters using the navswitch.
 * Calls 'player_input()' for the characters.
 * Returns the head of the sequence when it finishes looping
 * for 'seq_num' times. Uses a for loop.
 */
char player_sequence(int seq_num)
{
    char sequence[seq_num] = {""};
    // Store player's input
    for (int i = 0; i < seq_num; i++) {
        sequence[i] = player_input() + ' ';
    }
    sequence[seq_num] = '\0';
    return sequence;
}

int main(void)
{
    system_init ();
    navswitch_init ();

    return 0;



}
