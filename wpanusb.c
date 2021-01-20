/*
 * wpanusb.c
 *
 *  Created on: Jan 15, 2021
 *      Author: baozhu
 */
#include "wpanusb.h"
#include <ti/drivers/UART2.h>
extern UART2_Handle 	 uart1_handle;
char  hello[63] = "\r\n";

uint8_t wpanusb_init(struct wpan_driver_context *driver){
    /* Create ring buffer to store button events */
    RingBuf_construct(&driver->rx_ringbuf, driver->rx_buf, CONFIG_WPANUSB_RINGBUF_SIZE);


    return 0;
}



void wpanusb_loop(struct wpan_driver_context *driver){
	uint8_t data[16];
	uint32_t          status = UART2_STATUS_SUCCESS;
	if(RingBuf_getCount(&driver->rx_ringbuf) > 16){
		RingBuf_getn(&driver->rx_ringbuf, &data,16);

		status = UART2_write(uart1_handle, &data, 16, NULL);
		if (status != UART2_STATUS_SUCCESS) {
			/* UART2_write() failed */
			while (1);
		}
		status = UART2_write(uart1_handle, &hello, 2, NULL);
		if (status != UART2_STATUS_SUCCESS) {
			/* UART2_write() failed */
			while (1);
		}
    }
}
