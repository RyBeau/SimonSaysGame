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
void setup_title_message(void)
{
    char* greeting = " SIMON SAYS ";
    display_text(greeting, strlen(greeting));
}

/**
 * Handles the matchmaking between two boards.
 * Takes an int* is_host_ptr to determine who will start first (host).
 * Proceeds to send and receive a signal (!) when player is found.
 *
 * @param int* is_host_ptr, int to be updated to determine host
 */
void setup_set_player(int* is_host_ptr)
{
    int player_found = 0;
    char data[1];
    char* instruction = " HOLD TO HOST ";
    while(player_found == 0) {
        display_text(instruction, strlen(instruction));
        navswitch_update();

        if (ir_uart_read_ready_p ()) {
            comm_receive_sequence(data, 1);
            if (strncmp(data, "!", 1) == 0) {
                *is_host_ptr = 0;
                player_found = 1;
            }
        }
        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            comm_transmit_sequence("!", 1);
            *is_host_ptr = 1;
            player_found = 1;
        }
    }
}


