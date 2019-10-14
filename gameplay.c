/*
 * Handles the sequence generation, commmunication,
 * main gameplay, and sequence comparison.
 *
 * Unifinished - does not have an end scenario.
 * NOT TESTED.
 *
 * Author: Raymond Tamse Jr
 * Date: October 14 2019
 */


#include "system.h"
#include "pacer.h"
#include <string.h>
# include <stdlib.h>


#define PACER_RATE 500
#define SEQ_TYPE_NUM 5
#define SEQ_START_SIZE 5

/*
 * Takes an int 'is_host' to determine whether the player should
 * call the function 'generate_sequence' to generate a random sequence.
 * Displays a countdown prompt on the LED matrix before the game begins.
 */
void begin_game(int is_host)
{
    pacer_init(PACER_RATE);

    char* countdown = "3 2 1 ";
    display_sequence(countdown, strlen(countdown));

    char* host_seq = NULL;
    char* player_seq = NULL;

    int game_start = 0;
    int score = 0;
    int seq_size = SEQ_START_SIZE;

    while (1) {

        // used to constantly check if:
        // player has sent their answer (for host), or
        // host sends sequence to answer (for player)
        if (ir_uart_read_ready_p ())
        {
            if (is_host) {
                host_seq = receiveSequence(seq_size);
            } else {
                player_seq = receiveSequence(seq_size);
            }
        }

        // if given the signal that player has finished the sequence...
        if (player_seq != NULL || !game_start) {
            sequence_comms(host_seq, player_seq);

            score += strncmp(host_seq, player_seq, seq_size);
            player_seq = NULL;
            game_start = 1;
            seq_size++;
        }
    }
}


/*
 * Handles the sequence communication between player and host.
 * If host, generated sequence is displayed (if possible ???) and
 * also transmitted to the player.
 * If player, await input (if possible ???)
 *
 * Current concern over the program working with 2 while loops?
 */
void sequence_comms(char* host_seq, char* player_seq)
{
    if (is_host && host_seq == NULL) {
        host_seq = generate_host_seq();
        display_sequence(host_seq, strlen(host_seq));
        transmitSequence(host_seq);
    } else if (player_seq == NULL) {
        player_seq = player_sequence(seq_size);
    }
}

/*
 * Generates a random sequence of chars
 * corresponding to all five navswitch inputs.
 * Returns a char* to the main game loop.
 */
char* generate_sequence(int seq_length)
{
    char* sequence = NULL;
    char* seq_symbols = "^>.<*";
    int random_num = rand() % SEQ_TYPE_NUM;
    for (int i = 0; i < seq_length; i++) {
        *(sequence + i) = *(seq_symbols + random_num) + " ";
    }
    return sequence;
}