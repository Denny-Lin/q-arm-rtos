#include "task.h"
#include "uart.h"

/* Pre-allocate stacks for 2 tasks (16KB each, 16-byte aligned) */
uint64_t task_stack_a[2048] __attribute__((aligned(16)));
uint64_t task_stack_b[2048] __attribute__((aligned(16)));

/* Task Control Blocks (TCBs) */
tcb_t tcb_a;
tcb_t tcb_b;
tcb_t *current_task;

/* Assembly switch function prototype */
extern void cpu_switch_to(tcb_t *prev, tcb_t *next);

/* Task A Logic */
void task_a(void) {
    while (1) {
        uart_puts("Running Task A...\n");
        for (int i = 0; i < 10000000; i++); // Simple delay
        cpu_switch_to(&tcb_a, &tcb_b);    // Switch to B
    }
}

/* Task B Logic */
void task_b(void) {
    while (1) {
        uart_puts("Running Task B...\n");
        for (int i = 0; i < 10000000; i++); // Simple delay
        cpu_switch_to(&tcb_b, &tcb_a);    // Switch to A
    }
}

/* Helper to initialize task context */
void task_init_context(tcb_t *tcb, uint64_t *stack_top, void (*func)(void)) {
    uint64_t *sp = stack_top;

    // Correcting the sequence point issue
    sp--; 
    *sp = (uint64_t)sp;   /* Original SP */
    sp--;
    *sp = (uint64_t)func; /* x30 (Link Register) */
    sp--;
    *sp = 0;              /* x29 (Frame Pointer) */
    
    for (int i = 0; i < 10; i++) {
        sp--;
        *sp = 0;          /* x19 - x28 */
    }

    tcb->sp = sp;
    tcb->state = 0; 
}


void os_init(void) {
    /* Initialize Task A and B contexts */
    task_init_context(&tcb_a, &task_stack_a[2048], task_a);
    task_init_context(&tcb_b, &task_stack_b[2048], task_b);
    
    current_task = &tcb_a;
    uart_puts("OS Tasks Initialized.\n");
}

