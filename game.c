#include "system.h"
#include "game_display.h"
#include "transmit.h"
#include "pacer.h"
#include "navswitch.h"


#define PACER_RATE 500

int main (void)
{
	system_init();
	navswitch_init();
    pacer_init(PACER_RATE);
    gameDisplay_init();
    transmit_init();
    
    char sequence[10] = "< > ^ . *A";
    display_text("Testing ", 8);
    while (1) {
		navswitch_update();
        if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
			display_text("Sending ", 8);
            transmitSequence(sequence, 10);
        }
        if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
			display_text("Receiving ", 10);
            char test[10] = "          ";
            receiveSequence(test, 1);
            display_sequence(test, 10);
        }
        pacer_wait();
    }
}
