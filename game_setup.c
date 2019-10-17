/*
 * Handles the game matchmaking.
 * Also sets messages using game_display.c depending on the current
 * state of the game.
 *
 * Author: Raymond Tamse Jr, Ryan Beaumont
 * Date: October 15 2019
 */


#include "system.h"
#include "navswitch.h"
#include "navinput.h"
#include "game_display.h"
#include "transmit.h"
#include "ir_uart.h"
#include <string.h>



/* Simply prints "Simon Says" on the LED matrix.
 */
void title_msg()
{
    char* greeting = " SIMON SAYS ";
    display_text(greeting, strlen(greeting));
}


/**
 * Handles the matchmaking between two boards.
 * Takes an int* to determine who will start first (host).
 * Proceeds to send and receive a signal (!) when player is found.
 *
 * @param int* is_host, int to be updated to determine host
 */
void set_player(int* is_host)
{
    int player_found = 0;
    char data[1];
    char* instruction = " HOLD TO HOST ";
    while(player_found == 0) {
        display_text(instruction, strlen(instruction));
        navswitch_update();

        // Transmit
        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            transmitSequence("!", 1);
            *is_host = 1;
            player_found = 1;
        }
        // Receive
        if (ir_uart_read_ready_p ()) {
            receiveSequence(data, 1);    // receive '!'
            if (strncmp(data, "!", 1) == 0) {
                *is_host = 0;
                player_found = 1;
            }
        }
    }
}

/**
 * Called when the player makes the wrong sequence.
 * Takes the char* player sequence with its size of int n,
 * and replaces the first symbol with an '!', defined as GAMEOVER
 * in game.c
 * Sequence gets transmitted to the host for checking.
 * @param char* sequence, player sequence to be updated
 */
void lose_signal(char* sequence, int n)
{
    *sequence = '!';
    transmitSequence(sequence, n);
}

/**
 * Takes an integer 'win' to choose between 3 different messages
 * depending on the result of the game.
 * Uses display_text to display the result message.
 * @param char* sequence, needed for lose scenario
 */
void game_over(char* sequence, int win)
{
    char* end_msg = NULL;

    switch (win) {
    case 0 :
        end_msg = " Congratulations! You win! ";
        break;
    case 1 :
        lose_signal(sequence, strlen(sequence));
        *sequence = '!';
        transmitSequence(sequence, strlen(sequence));
        end_msg = " Game over! You lose! ";
        break;
        display_text(end_msg, strlen(end_msg));
    }
}

