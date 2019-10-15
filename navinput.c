/*
 * Implements navswitch and processes the player's input sequence.
 *
 * @author Raymond Tamse
 * Date: October 14 2019
 */

#include "system.h"
#include "navswitch.h"
#include "game_display.h"
#include "pacer.h"


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
    display_sequence(input, n); //dont want

}


