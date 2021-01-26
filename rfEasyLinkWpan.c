/*
 * Copyright (c) 2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== rfEasyLinkWpan.c ========
 */
#include <stdint.h>
#include <stddef.h>

/* POSIX Header files */
#include <semaphore.h>
#include <pthread.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART2.h>
/* Driver configuration */
#include "ti_drivers_config.h"
#include "wpanusb/wpanusb.h"

static sem_t sem;
static volatile size_t numBytesRead;
static struct wpan_driver_context wpan_context_data;
UART2_Handle     uart0_handle;
UART2_Handle 	 uart1_handle;




/*
 *  ======== callbackFxn ========
 */
void callbackFxn1(UART2_Handle handle, void *buffer, size_t count,
        void *userArg, int_fast16_t status)
{
    if (status != UART2_STATUS_SUCCESS) {
        /* RX error occured in UART2_read() */
        while (1);
    }
    numBytesRead = count;
    sem_post(&sem);
}


void *uartThread(void *arg0){
    UART2_Params      uart0Params;
    UART2_Params      uart1Params;
    uint32_t          status = UART2_STATUS_SUCCESS;
    int32_t           semStatus;

    /* Create semaphore */
    semStatus = sem_init(&sem, 0, 0);

    if (semStatus != 0) {
        /* Error creating semaphore */
        while (1);
    }

    /* Create a UART in CALLBACK read mode */
    UART2_Params_init(&uart0Params);
    uart0Params.readMode = UART2_Mode_CALLBACK;
    uart0Params.readCallback = callbackFxn1;
    uart0Params.baudRate = 115200;

    UART2_Params_init(&uart1Params);
    uart1Params.readMode = UART2_Mode_NONBLOCKING;
    uart1Params.baudRate = 115200;


    uart0_handle = UART2_open(CONFIG_UART2_0, &uart0Params);
    if (uart0_handle == NULL) {
        /* UART2_open() failed */
        while (1);
    }

    uart1_handle = UART2_open(CONFIG_UART2_1, &uart1Params);
    if (uart1_handle == NULL) {
        /* UART_open() failed */
        while (1);
    }

    while(1){
        numBytesRead = 0;

        /* Pass NULL for bytesRead since it's not used in this example */
        status = UART2_read(uart0_handle, wpan_context_data.buf, CONFIG_WPANUSB_UART_BUF_LEN, NULL);
        if (status != UART2_STATUS_SUCCESS) {
            /* UART2_read() failed */
            while (1);
        }
        RingBuf_putn(&wpan_context_data.rx_ringbuf, wpan_context_data.buf,numBytesRead);
        /* Do not write until read callback executes */
        sem_wait(&sem);
    }
}
/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
//    char              input;
    uint32_t          status = UART2_STATUS_SUCCESS;


    pthread_t           thread;
    pthread_attr_t      attrs;
    struct sched_param  priParam;
    int                 retc;

    /* Initialize the attributes structure with default values */
    pthread_attr_init(&attrs);

    /* Set priority, detach state, and stack size attributes */
    priParam.sched_priority = 2;
    retc = pthread_attr_setschedparam(&attrs, &priParam);
    retc |= pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_DETACHED);
    retc |= pthread_attr_setstacksize(&attrs, 1024);
    if (retc != 0) {
        /* failed to set attributes */
        while (1) {}
    }

    if(wpanusb_init(&wpan_context_data)){
    	while(1);
    }

    retc = pthread_create(&thread, &attrs, uartThread, NULL);
    if (retc != 0) {
        /* pthread_create() failed */
        while (1) {}
    }


    /* Call driver init functions */
    GPIO_init();

    /* Configure the LED pin */
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

    /* Turn on user LED to indicate successful initialization */
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);

    /* Loop forever echoing */
    while (1) {
        wpanusb_loop(&wpan_context_data);
    }
}
