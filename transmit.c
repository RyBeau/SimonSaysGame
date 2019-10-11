/**
 * @author Ryan Beaumont
 * @date 11/10/2019
 * @brief Transmit to other Player
 * @note This module transmits game information to the other player.
 * */
#include "system.h"
#include "ir_uart.h"

void transmitSequence(char* sequence)
{
    ir_uart_puts(sequence);
}

char* receiveSequence(int n)
{
    char* received[n];
    for(int i = 0; i < n; i++) {
        received[i] = ir_uart_getc();
    }
    return received;
}

void transmit_init(){
    ir_uart_init();
}
