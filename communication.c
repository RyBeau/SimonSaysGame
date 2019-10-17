/**
 * @author Ryan Beaumont
 * @date 11/10/2019
 * @brief Transmit to other Player
 * @note This module transmits game information to the other player.
 * */
#include "system.h"
#include "ir_uart.h"

/**
 * This transmits the sequece given in char* sequence.
 * @param char* sequence, data to be sent to the other board
 * */
void transmitSequence(char* sequence, int n)
{
    int counter = 0;
    while (counter < n || !ir_uart_write_finished_p ()) {
        if (ir_uart_write_ready_p ()) {
            ir_uart_putc(sequence[counter]);
            counter += 1;
        }
    }
}

/**
 * Receives the data sent by transmitSequence and puts it in the
 * given char* received.
 * @param char* received, char* for the received data to go into
 * */
void receiveSequence(char* received, int n)
{
    int counter = 0;
    while (counter < n) {
        if (ir_uart_read_ready_p()) {
            received[counter] = ir_uart_getc();
            counter += 1;
        }
    }
}

/**
 * Intialises other modules or variables needed for the
 * transmit module.
 **/
void communication_init(void)
{
    ir_uart_init();
}
