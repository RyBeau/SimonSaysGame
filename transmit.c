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
    ir_uart_puts(sequence);
}

/**
 * Receives the data sent by transmitSequence and puts it in the
 * given char* received.
 * @param char* received, char* for the received data to go into
 * */
void receiveSequence(char* received)
{
    int counter = 0;
    while (ir_uart_read_ready_p()) {
        received = ir_uart_getc();
        ++counter;
    }
}

/**
 * Intialises other modules or variables needed for the
 * transmit module.
 **/
void transmit_init(void)
{
    ir_uart_init();
}
