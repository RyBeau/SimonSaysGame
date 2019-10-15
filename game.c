#include "system.h"
#include "game_display.h"
#include "transmit.h"
#include "pacer.h"
#include "navswitch.h"
#include "navinput.h"
#include <string.h>

#include "gameplay.h"


#define PACER_RATE 500

int checkSequence(char* received, char* input, int n)
{
    if (strncmp(received, input, n) == 0) {
        return(1);
    } else {
        return(0);
    }
}


int main (void)
{
    system_init();
    navswitch_init();
    pacer_init(PACER_RATE);
    gameDisplay_init();
    transmit_init();

    char sequence[10];
    char received[10];
    while (1) {
        if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
            player_input(sequence, 10);
            transmitSequence(sequence, 10);
        }
        if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            receiveSequence(received, 10);
            display_sequence(received, 10);
            player_input(sequence, 10);
            if (checkSequence(received, sequence, 10)) {
				display_text("Matches ", 8);
            } else {
				display_text("Wrong ", 6);
			}
            
        }
        navswitch_update();
        pacer_wait();
    }
}

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
