/**
 * @file game.c
 * @author Ryan Beaumont
 * @author Raymond Tamse
 * @date 16/10/2019
 * game.c is the main module of the game. It contains functions related to
 * game logic and operation.
 * */

#include "system.h"
#include "game_display.h"
#include "transmit.h"
#include "pacer.h"
#include "navswitch.h"
#include "navinput.h"
#include "game_setup.h"
#include <string.h>
#include <stdlib.h>

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

/**
 * This function executes the two senarios that arise when comparing the
 * players inputted sequence with the sequence received from the other board.
 * If checkSequence returns true then it displays the text 'Matches' before setting
 * the value pointed to by turn to 1. Otherwise it displays the text "Wrong" and
 * sets the value pointed to by game_playing to 0.
 * @param char* received, pointer to the sequence received from the other player
 * @param char* sequence, pointer to the sequence entered by the player
 * @param int* game_playing, pointer to game_playing int from the game_loop function
 * @param int* is_turn, pointer to the is_turn int from the game loop function
 * @param int seq_add, the addition character length from round progression
 * */
void receiving_check(char* received, char* sequence, int* game_playing, int seq_add)
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

/**
 * This function is for the turn where the player must match the sequence
 * that was sent to them by the other player. If first checks to see if the
 * received sequence is signalling that they have beaten the other player.
 * If not then it displays received, then calls player_input to get input from
 * the player, and finally calls receiving_check to find out if the player successfully repeated
 * the pattern.
 * @param char* received, pointer to the sequence received from the other player
 * @param char* sequence, pointer to the sequence entered by the player
 * @param int* game_playing, pointer to game_playing int from the game_loop function
 * @param int* is_turn, pointer to the is_turn int from the game loop function
 * @param int seq_add, the addition character length from round progression
 * */

void receivingTurn(char* received, char* sequence, int* game_playing, int* is_turn,int seq_add)
{
   receiveSequence(received, SEQ_SIZE + seq_add);
   display_sequence(received, SEQ_SIZE + seq_add);
   player_input(sequence, SEQ_SIZE + seq_add, *is_turn);
   receiving_check(received, sequence, game_playing, seq_add);
*is_turn = 1;

}

/**
 * This function is for the turn where the player is setting a pattern
 * to be sent to the other player. First it indicates to the player that its
 * there turn to enter a pattern. It then calls player_input to get that pattern.
 * Finally it transmits that sequence and sets the value pointed to by is_turn
 * to 0.
 * @param char* sequence, pointer to the sequence entered by the player
 * @param int* is_turn, pointer to the is_turn int from the game loop function
 * @param int seq_add, the addition character length from round progression
 * */
void sendingTurn(char* sequence,int* is_turn, int seq_add)
{
    display_text("Your Turn ", 10);
    player_input(sequence, SEQ_SIZE + seq_add, *is_turn);
    transmitSequence(sequence, SEQ_SIZE + seq_add);
    *is_turn = 0;
}

/**
 * This function uses realloc to dynamically increase the size of the
 * char* for the sequences to be repeated by and entered by the player
 * @param char* sequence, pointer to the sequence entered by the player
 * @param char* received, pointer to the sequence received from the other player
 * @param int seq_add, the addition character length from round progression
 * */
void reallocCharStars(char* sequence, char* received, int seq_add)
{
    realloc(sequence, SEQ_SIZE + seq_add);
    realloc(received, SEQ_SIZE + seq_add);
}

/**
 * This function frees the allocated memory given to the char* sequence
 * and received.
 * @param char* sequence, pointer to the sequence entered by the player
 * @param char* received, pointer to the sequence received from the other player
 * */
void freeCharStars(char* sequence, char* received)
{
    free(sequence);
    free(received);
}

/**
 * This is the loop for the gameplay aspect. It intialises all
 * variables that are needed only during a match of the game.
 * @param int is_turn, indicates whether its this players turn to set a sequence and transmit
 * */
void game_loop(int is_turn)
{
    int turns = 1;              // keeps track of turn switches
    int seq_add = 0;
    int game_playing = 1;
    char sequence[SEQ_SIZE];
    char received[SEQ_SIZE];
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
        pacer_wait();
    }
    freeCharStars(sequence, received);
}

/**
 * This is the main loop for the game, here all sub-loops are called in
 * the correct order to allow for reqeated games without restarting the
 * UCFK. It first calls all the init functions of modules that will be
 * used throughtout the game. Next it defines is_turn which is an int that
 * holds a 0 or 1 to indicate true or false.
 * Finally it enters the infinite while loop where it plays the title message
 * then enters the setup loop, and finally enters the game loop.
 * */
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

