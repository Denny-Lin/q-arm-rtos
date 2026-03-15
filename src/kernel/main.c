#include "uart.h"
#include "timer.h"

void main(void) {
    uart_init();
    uart_puts("q-arm-rtos: System Booting...\n");

    /* Initialize Heartbeat */
    timer_init();

    uart_puts("AArch64 Kernel Initialized.\n");

    while (1) {
        /* Scheduler loop */
    }
}