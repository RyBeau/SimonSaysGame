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
#define SEQ_SIZE 10


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

void receiving_check(char* received, char* sequence, int* game_playing, int* is_turn,int seq_add)
{
    if (checkSequence(received, sequence, SEQ_SIZE + seq_add)) {
        display_text("Matches ", 8);
        *is_turn = 1;
    } else {
        display_text("Wrong ", 6);
        *game_playing = 0;
        //Game Over Function
    }
}

void game_loop(int is_turn)
{
    int turns = 1;              // keeps track of turn switches
    int seq_add = 0;
    int game_playing = 1;
    char sequence[SEQ_SIZE];
    char received[SEQ_SIZE];
    while (game_playing) {
        if (is_turn) {
            display_text("Your Turn ", 10);
            player_input(sequence, SEQ_SIZE + seq_add, is_turn);
            transmitSequence(sequence, SEQ_SIZE + seq_add);
            is_turn = 0;
            ++turns;
        } else {
            receiveSequence(received, SEQ_SIZE + seq_add);
            display_sequence(received, SEQ_SIZE + seq_add);
            player_input(sequence, SEQ_SIZE + seq_add, is_turn);
            receiving_check(received, sequence, &game_playing, &is_turn, seq_add);
            ++turns;
        }
        if (turns % 3 == 0) { // if player has transmitted and received
            seq_add += 2;
        }
    }
}

int main (void)
{
    system_init();
    navswitch_init();
    pacer_init(PACER_RATE);
    gameDisplay_init();
    transmit_init();

    int is_turn;

    while (1) {
        title_msg();
        set_player(&is_turn);
        game_loop(is_turn);
    }
}

