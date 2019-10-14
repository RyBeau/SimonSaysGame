#include "system.h"
#include "game_display.h"
#include "transmit.h"
#include "pacer.h"
#include "navswitch.h"
#include "navinput.h"
#include <string.h>

#include "gameplay.h"


#define PACER_RATE 500

/**
int main (void)
{
    system_init();
    navswitch_init();
    pacer_init(PACER_RATE);
    gameDisplay_init();
    transmit_init();

    char sequence[10] = "< > ^ . *A";
    display_text("Testing ", 8);
    while (1) {
        navswitch_update();
        if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
            display_text("Sending ", 8);
            transmitSequence(sequence, 10);
        }
        if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            display_text("Receiving ", 10);
            char test[10] = "          ";
            receiveSequence(test, 1);
            display_sequence(test, 10);
        }
        pacer_wait();
    }
}
* */

/**        PATTERN MATCHING TEST - SUCCESS
int main (void)
{
    system_init();
    navswitch_init();
    pacer_init(PACER_RATE);
    gameDisplay_init();
    transmit_init();
    char test1[10];
    char test2[10];
    while(1) {
        player_input(test1, 10);            // assuming that seq_size is always even?
        player_input(test2, 10);
        if (strncmp(test1, test2, 10) == 0) {
            display_text(" Match! ", 8);
        } else {
            display_text(" Fail ", 6);
        }
    }

}
**/

/**      RANDOM SEQUENCE GENERATOR - SUCCESS
int main (void)
{
    system_init();
    navswitch_init();
    pacer_init(PACER_RATE);
    gameDisplay_init();
    transmit_init();

    char test1[10];
    while (1) {
        generate_sequence(test1, 10);
        display_sequence(test1, 10);
    }
}
*/
