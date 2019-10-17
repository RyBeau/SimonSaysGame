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
#include "communication.h"
#include "ir_uart.h"
#include <string.h>



/**
 * Simply prints "Simon Says" on the LED matrix.
 */
void title_msg(void)
{
    char* greeting = " SIMON SAYS ";
    display_text(greeting, strlen(greeting));
}


/**
 * Handles the matchmaking between two boards.
 * Takes an int* is_host to determine who will start first (host).
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
        navswitch_update();

        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            transmitSequence("!", 1);
            *is_host = 1;
            player_found = 1;
        }

        if (ir_uart_read_ready_p ()) {
            receiveSequence(data, 1);
            if (strncmp(data, "!", 1) == 0) {
                *is_host = 0;
                player_found = 1;
            }
        }
        display_text(instruction, strlen(instruction));
    }
}

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
        transmitSequence(sequence, strlen(sequence));
        end_msg = " Game over! You lose! ";
        display_text(end_msg, strlen(end_msg));
        break;
    case 1 :
        end_msg = " Congratulations! You win! ";
        display_text(end_msg, strlen(end_msg));
        break;
    }
}

