#include "task.h"
#include "uart.h"
#include "printf.h" 
#include "os.h"

/* Pre-allocate stacks for 2 tasks (16KB each) */
uint64_t task_stack_a[2048] __attribute__((aligned(16)));
uint64_t task_stack_b[2048] __attribute__((aligned(16)));

tcb_t tcb_a;
tcb_t tcb_b;
tcb_t *current_task;

extern void cpu_switch_to(tcb_t *prev, tcb_t *next);

void task_init_context(tcb_t *tcb, uint64_t *stack_top, void (*func)(void)) {
    uint64_t *sp = (uint64_t *)((uint64_t)stack_top & ~0xF);
    sp -= 34; 

    for (int i = 0; i < 34; i++) sp[i] = 0;

    sp[32] = (uint64_t)func; /* ELR_EL1 */
    sp[33] = 0x05;           /* SPSR_EL1 (EL1h + IRQ enabled) */
    sp[30] = (uint64_t)func; /* x30 (LR) */

    tcb->sp = sp;
    
    /* --- New Initializations --- */
    tcb->state = TASK_READY;
    tcb->sleep_ticks = 0;
}



/**
 * Task A: Demonstrates System Clock and Blocking Sleep
 * 
 * 1. Fetches current system uptime via SVC ID 2.
 * 2. Prints formatted timestamp using kernel printf.
 * 3. Enters SLEEPING state via SVC ID 1, yielding CPU for 1000ms.
 */
void task_a(void) {
    while (1) {
        /* Request system uptime from kernel (Unit: ms) */
        uint64_t now = os_get_uptime();

        /* Print timestamped message */
        printf("\n[%d ms] Task A: Hello from RTOS!\n", now);

        /* Block task for 1 second (100 system ticks) */
        os_sleep(1000); 
    }
}

/**
 * Task B: Background Task
 * 
 * Demonstrates preemptive multitasking. While Task A is sleeping,
 * the scheduler gives all remaining CPU cycles to Task B.
 */
void task_b(void) {
    while (1) {
        uart_puts("B");
        for (volatile int i = 0; i < 2000000; i++);
    }
}


void os_init(void)
{
    task_init_context(&tcb_a, &task_stack_a[2048], task_a);
    task_init_context(&tcb_b, &task_stack_b[2048], task_b);

    current_task = &tcb_a;

    uart_puts("OS Tasks Initialized.\n");
}