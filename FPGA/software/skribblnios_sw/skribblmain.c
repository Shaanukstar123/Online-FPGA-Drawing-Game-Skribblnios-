#include "system.h"
#include "altera_up_avalon_accelerometer_spi.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"
#include <stdlib.h>
#include <stdio.h>

#include <pthread.h>

alt_u8 led;
int level;

void led_write(alt_u8 led_pattern) {
    IOWR(LED_BASE, 0, led_pattern);
}

int main() {
    alt_32 x_read;
    alt_32 y_read;
    alt_32 z_read;
    alt_up_accelerometer_spi_dev * acc_dev;
    acc_dev = alt_up_accelerometer_spi_open_dev("/dev/accelerometer_spi");
    if (acc_dev == NULL) {
    	// if return 1, check if the spi ip name is "accelerometer_spi"
        return 1;
    }

    while (1) {
    	//Obtain values
        alt_up_accelerometer_spi_read_x_axis(acc_dev, & x_read);
        alt_up_accelerometer_spi_read_y_axis(acc_dev, & y_read);
        alt_up_accelerometer_spi_read_z_axis(acc_dev, & z_read);
        alt_printf("%x %x %x\n", x_read, y_read, z_read);
    }

    return 0;
}

