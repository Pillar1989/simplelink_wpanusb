/*
 * wpanusb.c
 *
 *  Created on: Jan 15, 2021
 *      Author: baozhu
 */
#include "wpanusb.h"
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/drivers/UART2.h>
#include "stdarg.h"
#include <string.h>

extern UART2_Handle 	 uart1_handle;
extern UART2_Handle      uart0_handle;

void wpanusb_printf(const char *fmt, ...) // custom printf() function
{
    va_list argp;
    va_start(argp, fmt);
    uint32_t          status = UART2_STATUS_SUCCESS;
    char string[100];
    if(0 < vsprintf(string,fmt,argp)) // build string
    {
		status = UART2_write(uart1_handle, (uint8_t*)string, strlen(string), NULL);
		if (status != UART2_STATUS_SUCCESS) {
			/* UART2_write() failed */
			while (1);
		}
		status = UART2_write(uart1_handle, "\r\n", 2, NULL);
		if (status != UART2_STATUS_SUCCESS) {
			/* UART2_write() failed */
			while (1);
		}
    }
    va_end(argp);
}
#define LOG_ERR wpanusb_printf
#define LOG_WRN wpanusb_printf
#define LOG_DBG wpanusb_printf


uint16_t crc16_ccitt(uint16_t seed, const uint8_t *src, size_t len)
{
	for (; len > 0; len--) {
		uint8_t e, f;

		e = seed ^ *src++;
		f = e ^ (e << 4);
		seed = (seed >> 8) ^ (f << 8) ^ (f << 3) ^ (f >> 4);
	}

	return seed;
}

uint8_t wpanusb_init(struct wpan_driver_context *driver){
    /* Create ring buffer to store button events */
    RingBuf_construct(&driver->rx_ringbuf, driver->rx_buf, CONFIG_WPANUSB_RINGBUF_SIZE);
    RingBuf_flush(&driver->rx_ringbuf);
    return 0;
}

static void wpan_process_ctrl_frame(struct wpan_driver_context *wpan)
{
	int ret = 0;
	// uint8_t *buf = wpan->rx_buffer;
	uint8_t cmd = wpan->rx_buffer[3];
	// //uint16_t value = (buf[4] << 8) | buf[5];
	// uint16_t index = (buf[7] << 8) | buf[6];
	// uint16_t length = (buf[9] << 8) | buf[8];

	switch (cmd) {
	case RESET:
		LOG_DBG("Reset device");
		break;
	case TX:
//		ret = tx(wpan);
		LOG_DBG("TX");
		break;
	case START:
//		ret = start(wpan);
		LOG_DBG("START");
		break;
	case STOP:
//		ret = stop(wpan);
		LOG_DBG("STOP");
		break;
	case SET_CHANNEL:
//		ret = set_channel(wpan);
		LOG_DBG("SET_CHANNEL");
		break;
	case SET_IEEE_ADDR:
//		ret = set_ieee_addr(wpan);
		LOG_DBG("SET_IEEE_ADDR");
		break;
	case SET_SHORT_ADDR:
//		ret = set_short_addr(wpan);
		LOG_DBG("SET_SHORT_ADDR");
		break;
	case SET_PAN_ID:
//		ret = set_pan_id(wpan);
		LOG_DBG("SET_PAN_ID");
		break;
	default:
		LOG_ERR("%x: Not handled for now", cmd);
		break;
	}

	if (ret != 0) {
		LOG_ERR("Command 0x%02x failed: (%d)", cmd, ret);
	}
}




static void wpan_process_frame(struct wpan_driver_context *wpan)
{
	if(wpan->rx_buffer[0] == 0xEE) {
		//LOG_HEXDUMP_ERR(wpan->rx_buffer, 8, "HDLC ERROR");
		LOG_ERR("HDLC ERROR");
	}
	else if (wpan->rx_buffer_len > 3 && wpan->crc == 0xf0b8) {
		uint8_t address = wpan->rx_buffer[0];
		uint8_t ctrl = wpan->rx_buffer[1];

		if ((ctrl & 1) == 0) {
			wpan->hdlc_rx_send_seq = (ctrl >> 5) & 0x07;
			//k_sem_give(&hdlc_sem);
		} else if (address == ADDRESS_CTRL && wpan->rx_buffer_len > 9) {
			wpan_process_ctrl_frame(wpan);
		} else if (address == ADDRESS_CDC) {
			LOG_WRN("Ignore CDC Frame");
		} else {
			LOG_ERR("Dropped HDLC addr:%x ctrl:%x", address, ctrl);
//			LOG_HEXDUMP_DBG(wpan->rx_buffer, wpan->rx_buffer_len, "rx_buffer");
		}
	} else {
		LOG_ERR("Dropped HDLC crc:%04x len:%d", wpan->crc, wpan->rx_buffer_len);
	}

	wpan->crc = 0xffff;
	wpan->rx_buffer_len = 0;
}

static int wpan_save_byte(struct wpan_driver_context *wpan, uint8_t byte)
{
	if (wpan->rx_buffer_len >= HDLC_BUFFER_SIZE) {
		LOG_ERR("HDLC RX Buffer Overflow");
		wpan->crc = 0xffff;
		wpan->rx_buffer_len = 0;
	}

	wpan->rx_buffer[wpan->rx_buffer_len++] = byte;

	return 0;
}

static void wpan_input_byte(struct wpan_driver_context *wpan, uint8_t byte)
{
	if(byte == HDLC_FRAME) {
		if (wpan->rx_buffer_len) {
			wpan_process_frame(wpan);
		}
	} else {
		if(byte == HDLC_ESC) {
			wpan->next_escaped = true;
		} else {
			if(wpan->next_escaped) {
				byte ^= 0x20;
				wpan->next_escaped = false;
			}
			wpan->crc = crc16_ccitt(wpan->crc, &byte, 1);
			wpan_save_byte(wpan, byte);
		}
	}
}

static int wpan_consume_ringbuf(struct wpan_driver_context *wpan)
{
	uint8_t data[100];
	size_t len, tmp;
	int ret;

	len = RingBuf_getn(&wpan->rx_ringbuf, data,
				 CONFIG_WPANUSB_RINGBUF_SIZE);
	if (len == 0) {
		return 0;
	}

	tmp = len;
	do {
		wpan_input_byte(wpan, data[len - tmp]);
	} while (--tmp);

//	ret = ring_buf_get_finish(&wpan->rx_ringbuf, len);
//	if (ret < 0) {
//		LOG_ERR("Cannot flush ring buffer (%d)", ret);
//	}
	return -EAGAIN;
}

void wpanusb_loop(struct wpan_driver_context *wpan){
	if(RingBuf_getCount(&wpan->rx_ringbuf) > 1){
		wpan_consume_ringbuf(wpan);

//		status = UART2_write(uart1_handle, &data, 1, NULL);
//		if (status != UART2_STATUS_SUCCESS) {
//			/* UART2_write() failed */
//			while (1);
//		}

//		data = 1;
//		status = UART2_write(uart0_handle, &data, 1, NULL);
//		if (status != UART2_STATUS_SUCCESS) {
//			/* UART2_write() failed */
//			while (1);
//		}


    }else
    	Task_sleep(10000 / Clock_tickPeriod);
}
