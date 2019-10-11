#include "system.h"
#include "game_display.h"
#include "transmit.h"
#include "pacer.h"
#include "navswitch.h"

#define PACER_RATE 500

int main (void)
{
    pacer_init(PACER_RATE);
    char sequence[10] = "< > ^ . * ";
    while (1) {
        if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
            transmitSequence(sequence);
        } else {
            char* test = receiveSequence(10);
            display_sequence(test, 10);
        }
        pacer_wait();
    }
}
