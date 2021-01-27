/*
 * wpanusb.h
 *
 *  Created on: Jan 15, 2021
 *      Author: baozhu
 */

#ifndef WPANUSB_H_
#define WPANUSB_H_
#include <ti/drivers/utils/RingBuf.h>
#include <ti/sysbios/knl/Queue.h>

#define CONFIG_WPANUSB_UART_BUF_LEN 8
#define CONFIG_WPANUSB_RINGBUF_SIZE 1024
#define CONFIG_WPANUSB_NET_BUF_SIZE 136


#define ADDRESS_CTRL    0x01
#define ADDRESS_WPAN    0x03
#define ADDRESS_CDC     0x05
#define ADDRESS_HW      0x41

#define HDLC_FRAME      0x7E
#define HDLC_ESC        0x7D
#define HDLC_ESC_FRAME  0x5E
#define HDLC_ESC_ESC    0x5D

#define HDLC_BUFFER_SIZE 256


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


struct hdlc_block {
	void *fifo_reserved;
	uint8_t address;
	uint8_t ctrl;
	uint8_t length;
	uint8_t buffer[HDLC_BUFFER_SIZE];
};




struct wpan_driver_context {
	uint8_t rx_buffer_len;
	uint8_t rx_buffer[HDLC_BUFFER_SIZE];
	struct hdlc_block *tx_hdlc_block;

	/* ppp data is read into this buf */
	uint8_t buf[CONFIG_WPANUSB_UART_BUF_LEN];

	/* Incoming data is routed via ring buffer */
	RingBuf_Object rx_ringbuf;
	uint8_t rx_buf[CONFIG_WPANUSB_RINGBUF_SIZE];

	uint16_t crc;

	struct set_channel channel;

	uint8_t next_escaped;

	uint8_t hdlc_send_seq;
	uint8_t hdlc_rx_send_seq;

	Queue_Handle tx_queue;
};


uint8_t wpanusb_init(struct wpan_driver_context *driver);
void wpanusb_loop(struct wpan_driver_context *driver);
void *txUartThread(void *arg0);

#define	EPERM		 1	/* Operation not permitted */
#define	ENOENT		 2	/* No such file or directory */
#define	ESRCH		 3	/* No such process */
#define	EINTR		 4	/* Interrupted system call */
#define	EIO		 5	/* I/O error */
#define	ENXIO		 6	/* No such device or address */
#define	E2BIG		 7	/* Argument list too long */
#define	ENOEXEC		 8	/* Exec format error */
#define	EBADF		 9	/* Bad file number */
#define	ECHILD		10	/* No child processes */
#define	EAGAIN		11	/* Try again */
#define	ENOMEM		12	/* Out of memory */
#define	EACCES		13	/* Permission denied */
#define	EFAULT		14	/* Bad address */
#define	ENOTBLK		15	/* Block device required */
#define	EBUSY		16	/* Device or resource busy */
#define	EEXIST		17	/* File exists */
#define	EXDEV		18	/* Cross-device link */
#define	ENODEV		19	/* No such device */
#define	ENOTDIR		20	/* Not a directory */
#define	EISDIR		21	/* Is a directory */
#define	EINVAL		22	/* Invalid argument */
#define	ENFILE		23	/* File table overflow */
#define	EMFILE		24	/* Too many open files */
#define	ENOTTY		25	/* Not a typewriter */
#define	ETXTBSY		26	/* Text file busy */
#define	EFBIG		27	/* File too large */
#define	ENOSPC		28	/* No space left on device */
#define	ESPIPE		29	/* Illegal seek */
#define	EROFS		30	/* Read-only file system */
#define	EMLINK		31	/* Too many links */
#define	EPIPE		32	/* Broken pipe */
#define	EDOM		33	/* Math argument out of domain of func */
#define	ERANGE		34	/* Math result not representable */


#endif /* WPANUSB_H_ */
