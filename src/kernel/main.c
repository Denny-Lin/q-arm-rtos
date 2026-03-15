#include "uart.h"
#include "timer.h"
#include "task.h"

/* Prototypes from other modules */
void gic_init(void);
void os_init(void);

/* Current task tracker (from task.c) */
extern tcb_t *current_task;

void main(void) {
    /* 1. Hardware Abstraction Layer Initialization */
    uart_init();
    uart_puts("q-arm-rtos: System Booting...\n");

    /* 2. Interrupt Controller Setup */
    gic_init();

    /* 3. System Heartbeat Setup */
    timer_init();

    /* 4. OS Kernel & Tasks Initialization */
    /* This creates Task A and Task B stacks and TCBs */
    os_init();

    /* 5. Enable Global Interrupts (Unmask DAIF) */
    /* This allows the CPU to hear the Timer Tick */
    asm volatile ("msr daifclr, #2"); 

    uart_puts("AArch64 Kernel Initialized.\n");
    uart_puts("Starting Multi-tasking...\n\n");

    /* 6. Launch the first task */
    /* We call task_a directly to start the cooperative loop */
    extern void task_a(void);
    task_a();

    /* We should never reach here in a multitasking system */
    while (1) {
        asm volatile ("wfi");
    }
}
