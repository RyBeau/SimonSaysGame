/**
 * @file game.c
 * @author Ryan Beaumont
 * @author Raymond Tamse
 * @date 16/10/2019
 * @brief game.c is the main module of the game. It contains functions related to
 * game logic and operation.
 * */

#include "system.h"
#include "navswitch.h"
#include "navinput.h"
#include "game_display.h"
#include "communication.h"
#include "pacer.h"
#include "game_setup.h"
#include <string.h>

#define PACER_RATE 500
#define MAX_SIZE 30 //Maximum sequence size
#define GAMEOVER '!' //Game over character
#define TRUE 1
#define FALSE 0

/**
 * Takes an integer 'win' to choose between 2 different messages
 * depending on the result of the game.
 * Uses display_text to display the result message.
 * @param char* sequence, needed for lose scenario
 */
void game_over(char* sequence, int win)
{
    char* end_msg = NULL;

    switch (win) {
    case 0 :
        sequence[0] = '!';
        comm_transmit_sequence(sequence, strlen(sequence));
        end_msg = " Game over! You lose! ";
        display_text(end_msg, strlen(end_msg));
        break;
    case 1 :
        end_msg = " Congratulations! You win! ";
        display_text(end_msg, strlen(end_msg));
        break;
    }
}

/**
 * Takes two pointers char* which point to the host sequence and
 * the player sequence.
 * Compares the two sequences, and returns 1 if the sequence matches,
 * otherwise returns 0;
 *
 * @param char* received, host's sequence to be compared
 * @param char* input, player's sequence to be compared
 * @return TRUE or FALSE
 */
static int game_check_sequence(char* received, char* input, int n)
{
    if (strncmp(received, input, n) == 0) {
        return(TRUE);
    } else {
        return(FALSE);
    }
}

/**
 * This function executes the two senarios that arise when comparing the
 * players inputted sequence with the sequence received from the other board.
 * If game_check_sequence returns true then it displays the text 'Matches' before setting
 * the value pointed to by is_turn_ptr to 1. Otherwise it displays the text "Wrong" and
 * sets the value pointed to by game_playing_ptr to 0.
 * @param char* received, pointer to the sequence received from the other player
 * @param char* sequence, pointer to the sequence entered by the player
 * @param int* game_playing_ptr, pointer to game_playing int from the game_loop function
 * @param int* is_turn_ptr, pointer to the is_turn int from the game loop function
 * @param int current_size, the addition character length from round progression
 * */
static void game_receiving_check(char* received, char* sequence, int* game_playing_ptr, int* is_turn_ptr, int current_size)
{
    int is_correct = game_check_sequence(received, sequence, current_size);
    if (is_correct) {
        display_text("Matches ", 8);
        *is_turn_ptr = 1;
    } else {
        display_text("Wrong ", 6);
        *game_playing_ptr = 0;
        game_over(sequence, is_correct);
    }
}

/**
 * This function checks to see if the first character of the received sequence
 * matches the defined GAMEOVER character.
 * @param char* received, the received sequence from the other player 
 * @return TRUE or FALSE
 * */
static int game_check_if_won(char* received)
{
    if (GAMEOVER == received[0]) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * This function is for the turn where the player must match the sequence
 * that was sent to them by the other player. If first checks to see if the
 * received sequence is signalling that they have beaten the other player.
 * If not then it displays received, then calls player_input to get input from
 * the player, and finally calls game_receiving_check to find out if the player successfully repeated
 * the pattern.
 * @param char* received, pointer to the sequence received from the other player
 * @param char* sequence, pointer to the sequence entered by the player
 * @param int* game_playing_ptr, pointer to game_playing_ptr int from the game_loop function
 * @param int* is_turn_ptr, pointer to the is_turn int from the game loop function
 * @param int current_size, the addition character length from round progression
 * */

static void game_receiving_turn(char* received, char* sequence, int* game_playing_ptr, int* is_turn_ptr,int current_size)
{
    comm_receive_sequence(received, current_size);
    if (!game_check_if_won(received)) {
        display_sequence(received, current_size);
        player_input(sequence, current_size);
        game_receiving_check(received, sequence, game_playing_ptr, is_turn_ptr,current_size);
    } else {
        game_over(sequence, TRUE);
        *game_playing_ptr = 0;
    }

}

/**
 * This function is for the turn where the player is setting a pattern
 * to be sent to the other player. First it indicates to the player that its
 * there turn to enter a pattern. It then calls player_input to get that pattern.
 * Finally it transmits that sequence and sets the value pointed to by is_turn_ptr
 * to 0.
 * @param char* sequence, pointer to the sequence entered by the player
 * @param int* is_turn_ptr, pointer to the is_turn int from the game loop function
 * @param int current_size, the addition character length from round progression
 * */
static void game_sending_turn(char* sequence,int* is_turn_ptr, int current_size)
{
    display_text("Your Turn ", 10);
    display_int(current_size);
    player_input(sequence,  current_size);
    comm_transmit_sequence(sequence,  current_size);
    *is_turn_ptr = 0;
}

/**
 * This is the loop for the gameplay aspect. It intialises all
 * variables that are needed only during a match of the game.
 * It then loops until one player incorrectly repeats the sequence sent to them.
 * @param int is_turn, indicates whether its this players turn to set a sequence and transmit
 * */
static void game_loop(int is_turn)
{
    int turns = 0;              // keeps track of turn switches
    int current_size = 10;
    int game_playing = 1;
    char sequence[MAX_SIZE];
    char received[MAX_SIZE];
    while (game_playing) {
        if (is_turn) {
            game_sending_turn(sequence, &is_turn, current_size);
            ++turns;
        } else {
            game_receiving_turn(received, sequence, &game_playing, &is_turn, current_size);
            ++turns;
        }
        if (turns % 2 == 0 && current_size < 30 && turns > 0) { // if player has transmitted and received
            current_size += 2;
        }
        pacer_wait();
    }
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
    game_display_init();
    communication_init();

    int is_turn;

    while (1) {
        setup_title_message();
        setup_set_player(&is_turn);
        game_loop(is_turn);
    }
}

