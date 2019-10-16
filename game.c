#include "system.h"
#include "game_display.h"
#include "transmit.h"
#include "pacer.h"
#include "navswitch.h"
#include "navinput.h"
#include <string.h>
#include <stdlib.h>
#include "game_setup.h"
#include "gameplay.h"


#define PACER_RATE 500
#define SEQ_SIZE 10
#define	GAMEOVER '!'


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

void receivingTurn(char* received, char* sequence, int* game_playing, int* is_turn,int seq_add)
{
    receiveSequence(received, SEQ_SIZE + seq_add);
    if (received[0] == GAMEOVER) {
        *game_playing = 0;
        //Call you win
    } else {
        display_sequence(received, SEQ_SIZE + seq_add);
        player_input(sequence, SEQ_SIZE + seq_add, is_turn);
        receiving_check(received, sequence, game_playing, is_turn, seq_add);
    }
}

void sendingTurn(char* sequence,int* is_turn, int seq_add)
{
    display_text("Your Turn ", 10);
    player_input(sequence, SEQ_SIZE + seq_add, *is_turn);
    transmitSequence(sequence, SEQ_SIZE + seq_add);
    *is_turn = 0;
}

void reallocCharStars(char* sequence, char* received, int seq_add)
{
	realloc(sequence, SEQ_SIZE + seq_add);
	realloc(received, SEQ_SIZE + seq_add);
}

void freeCharStars(char* sequence, char* received)
{
	free(sequence);
	free(received);
}

void game_loop(int is_turn)
{
    int turns = 1;              // keeps track of turn switches
    int seq_add = 0;
    int game_playing = 1;
    char* sequence = malloc(SEQ_SIZE);
    char* received = malloc(SEQ_SIZE);
    while (game_playing) {
        if (is_turn) {
            sendingTurn(sequence, &is_turn, seq_add);
            ++turns;
        } else {
            receivingTurn(received, sequence, &game_playing, &is_turn, seq_add);
            ++turns;
        }
        if (turns % 3 == 0) { // if player has transmitted and received
            seq_add += 2;
            reallocCharStars(sequence, received, seq_add);
        }
    }
    freeCharStars(sequence, received);
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

