/*
 * Implements navswitch and stores the player's input sequence.
 * Host input is received through IR transmission (temp.?).
 * Uses tinygl to display the player's input (temp.?).
 * Currently contains code copies from existing lab files.
 *
 * No implementation of being able to distribute the player sequence
 * elsewhere other than here.
 *
 * Authors: Raymond Tamse, Ryan Beaumont
 * Date: October 9 2019
 */

#include <string.h>
#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font5x7_2_arrows.h"


// might get marked for plagiarism?
#define PACER_RATE 500
#define MESSAGE_RATE 10

#define SEQ_MAX 20
#define PLAYER_TURN 0

/*
 * Takes a char type variable and displays one of the four arrows
 * or the dot corresponding to the specific character given.
 * Result is displayed on the LED matrix using tinygl.
 */
void display_character (char character)
{
    char buffer[2];

    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

/*
 * Returns either !, ", #, $, or %, which all correspond to
 * one of the four arrows and the dot, depending on the player's input
 * from the navswitch. Uses a while loop.
 */
char player_input ()
{
    input_char = '';
    // Arrows; clockwise starting from North
    while (input_char == '') {
        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            input_char = '!';
        }

        if (navswitch_push_event_p (NAVSWITCH_EAST)) {
            input_char = '"';
        }

        if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            input_char = '#';
        }

        if (navswitch_push_event_p (NAVSWITCH_WEST)) {
            input_char = '$';
        }

        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            input_char = '%';    // dot
        }
    }
    return input_char;
}

/* Takes an integer 'seq_num' to record the required amount of characters.
 * Uses a char* to record a sequence of characters using the navswitch.
 * Calls 'player_input()' for the characters.
 * Returns the head of the sequence when it finishes looping
 * for 'seq_num' times. Uses a for loop.
 */
char* player_sequence(int seq_num)
{
    char* player_sequence;
    // Store player's input
    for (int i = 0; i < seq_num; i++) {
        char character = player_input();
        *(player_sequence + i) = character;
        display_character (character);
    }
    *(player_sequence + seq_num) = '\0';
    return player_sequence;
}

int main(void)
{
    char* local_sequence[SEQ_MAX];
    char host_sequence[SEQ_MAX] = {0};

    system_init ();

    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_2_arrows);
    tinygl_text_speed_set (MESSAGE_RATE);

    navswitch_init ();

    pacer_init (PACER_RATE);

    while(1)
    {
        pacer_wait ();
        tinygl_update ();

        navswitch_update ();


        if (PLAYER_TURN) {

            char* seq_pointer = player_sequence(0);
            // 0 must be replaced by another number
            // must be tested from a different file that determines
            // number of sequences from host


            // Copies the player sequence into a local array of type char*.
            strncpy(local_sequence, seq_pointer, SEQ_MAX * (sizeof char));
            /*
            if player's turn is over
            PLAYER_TURN = 0;
            */
        }

    }
    return 0;



}
