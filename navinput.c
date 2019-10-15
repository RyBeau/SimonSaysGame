/*
 * Implements navswitch and processes the player's input sequence.
 *
 * @author Raymond Tamse
 * Date: October 14 2019
 */

#include "system.h"
#include "navswitch.h"
#include "pacer.h"


/*
 * Takes a char* input that gets updated depending on the player's
 * input. Loops n times, where n/2 is the num. of symbols - the
 * other half is for spaces.
 */
void player_input(char* input, int n)
{
    int counter = 0;
    while (counter < n) {
		navswitch_update();
        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            input[counter] = '^';
            input[counter + 1] = ' ';
            counter += 2;
        }

        if (navswitch_push_event_p (NAVSWITCH_EAST)) {
            input[counter] = '>';
            input[counter + 1] = ' ';
            counter += 2;
        }

        if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            input[counter] = '.';
            input[counter + 1] = ' ';
            counter += 2;
        }

        if (navswitch_push_event_p (NAVSWITCH_WEST)) {
            input[counter] = '<';
            input[counter + 1] = ' ';
            counter += 2;
        }

        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            input[counter] = '*';
            input[counter + 1] = ' ';
            counter += 2;   // dot
        }
        pacer_wait();
    }
}


