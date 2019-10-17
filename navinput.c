/*
 * Implements navswitch and processes the player's sequence sequence.
 *
 * @author Raymond Tamse, Ryan Beaumont
 * Date: October 15 2019
 */

#include "system.h"
#include "navswitch.h"
#include "pacer.h"
#include "game_display.h"

/**
 * Takes a char* sequence that gets updated depending on the player's
 * sequence. Loops current_size times, where current_size/2 is the num. of symbols - the
 * other half is for spaces.
 * @param char* sequence, player sequence to be updated with sequence
 */
void player_input(char* sequence, int current_size)
{
    int counter = 0;	
    while (counter < current_size) {
        navswitch_update();
        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            sequence[counter] = '^';
            sequence[counter + 1] = ' ';
            counter += 2;
        }

        if (navswitch_push_event_p (NAVSWITCH_EAST)) {
            sequence[counter] = '>';
            sequence[counter + 1] = ' ';
            counter += 2;
        }

        if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            sequence[counter] = '.';
            sequence[counter + 1] = ' ';
            counter += 2;
        }

        if (navswitch_push_event_p (NAVSWITCH_WEST)) {
            sequence[counter] = '<';
            sequence[counter + 1] = ' ';
            counter += 2;
        }

        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            sequence[counter] = '*';
            sequence[counter + 1] = ' ';
            counter += 2;   // dot
        }
        pacer_wait();
    }
}


