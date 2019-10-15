/*
 * Sets up the game by determining who the host and the player is.
 * Also sets messages using game_display.c depending on the current
 * state of the game.
 *
 * NOT TESTED.
 *
 * Author: Raymond Tamse Jr
 * Date: October 13 2019
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
    display_text("Simon Says ", 11);
}


/*
 * Expects to receive '*' or '!' through IR to determine
 * who the host and the player is.
 * If person receives '*', trasmit '!' - person is player.
 * If person receives '!', start game - person is host.
 * Uses transmit.c for IR communication.
 * Returns an int that tells if the player is a host.
 */
void set_player(int* is_host)
{
    int player_found = 0;
    char data[1];
    /* While '*' or '!' not received... */
    while(player_found == 0) {
		//Put call here
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
                player_found = 1;
            }
        }
    }
}

/*
 * Takes an integer 'win' to choose between 3 different messages
 * depending on the result of the game.
 * Uses display_text to display the result message.
 */
 /**
void game_over(int win)
{
    char* end_msg = NULL;

    switch (win) {
    case 0 :
        end_msg = "You win! ";
        break;
    case 1 :
        end_msg = "You lose! ";
        break;
    case 2 :
        end_msg = "Game Over! ";           // host msg
    }
    display_text(end_msg, strlen(end_msg);
}
*/
