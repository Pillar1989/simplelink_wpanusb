/*
 * wpanusb.h
 *
 *  Created on: Jan 15, 2021
 *      Author: baozhu
 */

#ifndef WPANUSB_H_
#define WPANUSB_H_
#include <ti/drivers/utils/RingBuf.h>

#define CONFIG_WPANUSB_UART_BUF_LEN 8
#define CONFIG_WPANUSB_RINGBUF_SIZE 1024
#define CONFIG_WPANUSB_NET_BUF_SIZE 136

struct wpan_driver_context {
	/* ppp data is read into this buf */
	uint8_t buf[CONFIG_WPANUSB_UART_BUF_LEN];

	/* Incoming data is routed via ring buffer */
	RingBuf_Object rx_ringbuf;
	uint8_t rx_buf[CONFIG_WPANUSB_RINGBUF_SIZE];
	uint16_t crc;

};

uint8_t wpanusb_init(struct wpan_driver_context *driver);
void wpanusb_loop(struct wpan_driver_context *driver);

enum wpanusb_requests {
	RESET,
	TX,
	XMIT_ASYNC,
	ED,
	SET_CHANNEL,
	START,
	STOP,
	SET_SHORT_ADDR,
	SET_PAN_ID,
	SET_IEEE_ADDR,
	SET_TXPOWER,
	SET_CCA_MODE,
	SET_CCA_ED_LEVEL,
	SET_CSMA_PARAMS,
	SET_PROMISCUOUS_MODE,
};

struct set_channel {
	uint8_t page;
	uint8_t channel;
} __attribute__((packed));

struct set_short_addr {
	uint16_t short_addr;
} __attribute__((packed));

struct set_pan_id {
	uint16_t pan_id;
} __attribute__((packed));

struct set_ieee_addr {
	uint64_t ieee_addr;
} __attribute__((packed));


#endif /* WPANUSB_H_ */
