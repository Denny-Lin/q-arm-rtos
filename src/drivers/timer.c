#include "timer.h"
#include "uart.h"

void timer_init(void) {
    unsigned long freq;

    /* Get the system counter frequency (Hz) */
    asm volatile ("mrs %0, cntfrq_el0" : "=r" (freq));

    /* Set timer for 10ms interval (frequency / 100) */
    asm volatile ("msr cntp_tval_el0, %0" : : "r" (freq / 100));

    /* Enable the physical timer: Set ENABLE=1, IMASK=0 */
    asm volatile ("msr cntp_ctl_el0, %0" : : "r" (1));

    uart_puts("Generic Timer Initialized (10ms tick).\n");
}

