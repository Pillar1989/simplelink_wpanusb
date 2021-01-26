/*
 * wpanusb.c
 *
 *  Created on: Jan 15, 2021
 *      Author: baozhu
 */
#include "wpanusb.h"
#include <ti/drivers/UART2.h>
extern UART2_Handle 	 uart1_handle;
extern UART2_Handle      uart0_handle;
char  hello[63] = "\r\n";

uint8_t wpanusb_init(struct wpan_driver_context *driver){
    /* Create ring buffer to store button events */
    RingBuf_construct(&driver->rx_ringbuf, driver->rx_buf, CONFIG_WPANUSB_RINGBUF_SIZE);
    RingBuf_flush(&driver->rx_ringbuf);
    return 0;
}



void wpanusb_loop(struct wpan_driver_context *driver){
	uint8_t data;
	uint32_t          status = UART2_STATUS_SUCCESS;
	if(RingBuf_getCount(&driver->rx_ringbuf) > 1){
		RingBuf_get(&driver->rx_ringbuf, &data);
		status = UART2_write(uart1_handle, &data, 1, NULL);
		if (status != UART2_STATUS_SUCCESS) {
			/* UART2_write() failed */
			while (1);
		}

//		data = 1;
//		status = UART2_write(uart0_handle, &data, 1, NULL);
//		if (status != UART2_STATUS_SUCCESS) {
//			/* UART2_write() failed */
//			while (1);
//		}


    }
}
