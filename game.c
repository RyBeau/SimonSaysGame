#include "system.h"
#include "game_display.h"
#include "transmit.h"
#include "pacer.h"
#include "navswitch.h"
#include "navinput.h"
#include <string.h>
#include "game_setup.h"
#include "gameplay.h"


#define PACER_RATE 500


/**
 * Takes two pointers char* which point to the host sequence and
 * the player sequence.
 * Compares the two sequences, and returns 1 if the sequence matches,
 * otherwise returns 0;
 *
 * @param char* received, host's sequence to be compared
 * @param char* input, player's sequence to be compared
 */
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
    int is_turn = 0;
    while (1) {
        title_msg();
        set_player(&is_turn);

        if (is_turn) {
            display_text("Your Turn ", 10);
            player_input(sequence, 10);
            transmitSequence(sequence, 10);
            is_turn = 0;
        } else {
            receiveSequence(received, 10);
            display_sequence(received, 10);
            player_input(sequence, 10);
            if (checkSequence(received, sequence, 10)) {
                display_text("Matches ", 8);
                is_turn = 1;
            } else {
                display_text("Wrong ", 6);
            }
        }
        pacer_wait();
    }
}

