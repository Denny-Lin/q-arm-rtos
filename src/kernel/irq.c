/*
 * ARM Interrupt Pipeline & Scheduler Implementation
 *
 * Hardware Interrupt Flow:
 *
 * [Hardware] ARM Generic Timer (Physical Timer)  --> src/drivers/timer.c
 *        ↓
 * [Hardware] GIC (Generic Interrupt Controller)  --> src/drivers/gic.c
 *        ↓
 * [CPU] CPU IRQ Exception                        --> ARM AArch64 Hardware
 *        ↓
 * [Arch] Exception Vector Table (VBAR_EL1)       --> src/arch/aarch64/vectors.s
 *        ↓
 * [Arch] handle_irq (Assembly Context Saving)    --> src/arch/aarch64/vectors.s
 *        ↓
 * [Kernel] irq_handler() (C-level Dispatcher)    --> src/kernel/irq.c
 *        ↓
 * [Sched] Task Switching (Scheduler)             --> src/arch/aarch64/switch.s
 *
 * In this RTOS:
 * - Physical Timer interrupt ID = 30 (PPI)
 * - Time Slice = 10ms
 */
 
#include "uart.h"
#include "timer.h"
#include "board.h"
#include "task.h"

/* GIC CPU Interface Registers */
#define GICC_IAR  ((volatile unsigned int *)(GIC_CPU_BASE + 0x00C))
#define GICC_EOIR ((volatile unsigned int *)(GIC_CPU_BASE + 0x010))

/* External definitions from task management */
extern volatile uint64_t system_ticks = 0; 

extern tcb_t tcb_a;
extern tcb_t tcb_b;
extern tcb_t *current_task;
extern void cpu_switch_to(tcb_t *prev, tcb_t *next);

void irq_handler(void) {
    unsigned int irq_id = *GICC_IAR;

    if (irq_id == 30) {
        /* 1. Global uptime counter (1 tick = 10ms) */
        system_ticks++; 

        /* 2. Reset the hardware timer for the next heartbeat */
        timer_init();
        uart_puts("|");

        /* 3. Handle Task Sleep Timers: Decrement ticks and wake up if expired */
        if (tcb_a.state == TASK_SLEEPING) {
            if (tcb_a.sleep_ticks > 0) {
                tcb_a.sleep_ticks--;
            }
            if (tcb_a.sleep_ticks == 0) {
                tcb_a.state = TASK_READY; /* Wake up! */
            }
        }

        if (tcb_b.state == TASK_SLEEPING) {
            if (tcb_b.sleep_ticks > 0) {
                tcb_b.sleep_ticks--;
            }
            if (tcb_b.sleep_ticks == 0) {
                tcb_b.state = TASK_READY;
            }
        }

        /* 4. Smart Scheduler: Only switch to the NEXT task if it is READY */
        tcb_t *next_task = (current_task == &tcb_a) ? &tcb_b : &tcb_a;

        if (next_task->state == TASK_READY) {
            current_task = next_task;
        } 
        /* 
         * If the next task is still sleeping, we stay on the current_task 
         * UNLESS the current_task itself is also sleeping (Idle Case).
         */
        else if (current_task->state != TASK_READY) {
            /* Both tasks are sleeping, stay on current_task until someone wakes up */
        }
    }

    /* 5. Acknowledge the interrupt in GIC */
    *GICC_EOIR = irq_id;
}
