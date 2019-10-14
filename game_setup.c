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
#include "navinput.h"
#include "game_display.h"



/* Simply prints "Simon Says" on the LED matrix.
 */
void title_msg()
{
    display_text("Simon Says ");
}


/*
 * Expects to receive '*' or '!' through IR to determine
 * who the host and the player is.
 * If person receives '*', trasmit '!' - person is player.
 * If person receives '!', start game - person is host.
 * Uses transmit.c for IR communication.
 * Returns an int that tells if the player is a host.
 */
int set_player()
{
    transmit_init();

    int is_host = 0;

    char* player_found = NULL;

    /* While '*' or '!' not received... */
    while(player_found == NULL) {
        // Transmit
        if (host_input == '*')
        {
            transmitSequence(&host_input);
        }

        // Receive
        if (ir_uart_read_ready_p ())
        {
            player_found = receiveSequence(1);    // receive '!'
        }
    }

    if (*player_found == "!") {
        is_host = 1;
    }

    // does the transmit line need to be in a while loop?
    if (*player_found == "*") {
        char* inform_host = "!";
        transmitSequence(inform_host);
    }

    return is_host;          // at this point program calls begin_game
}

/*
 * Takes an integer 'win' to choose between 3 different messages
 * depending on the result of the game.
 * Uses display_text to display the result message.
 */
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
