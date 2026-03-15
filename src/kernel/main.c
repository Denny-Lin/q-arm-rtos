#include "uart.h"
void main(void) {
    uart_init();
    uart_puts("q-arm-rtos: System Booting...\n");
    uart_puts("AArch64 Kernel Initialized.\n");
    while (1) {}
}
