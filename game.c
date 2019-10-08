#include "system.h"
#include "pio.h"

#define ROW3 LEDMAT_ROW3_PIO
#define ROW4 LEDMAT_ROW4_PIO
#define ROW5 LEDMAT_ROW5_PIO



int main (void)
{
    system_init ();

     // ROWS
    pio_config_set (ROW3, PIO_OUTPUT_HIGH);
    pio_config_set (ROW4, PIO_OUTPUT_HIGH);
    pio_config_set (ROW5, PIO_OUTPUT_HIGH);


    // columns
    pio_config_set (LEDMAT_COL3_PIO, PIO_OUTPUT_LOW);


    while (1)
    {



        pio_output_low(ROW3);
        pio_output_low(ROW4);
        pio_output_low(ROW5);


        pio_output_high(LEDMAT_COL3_PIO);

    }
}
