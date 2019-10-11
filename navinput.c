/*
 * Implements navswitch and stores the player's input sequence.
 * Currently contains code copies from existing lab files.
 *
 * Authors: Raymond Tamse
 * Date: October 9 2019
 */

#include <stdio.h>
#include <string.h>
#include "system.h"
#include "navswitch.h"


#define SEQ_MAX 20


/*
 * Returns either !, ", #, $, or %, which all correspond to
 * one of the four arrows and the dot, depending on the player's input
 * from the navswitch. Uses a while loop.
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

    while(1)
    {
        navswitch_update ();
        char seq_pointer = player_sequence(5);
    }

    // Include test code here for seq_pointer?

    return 0;



}
