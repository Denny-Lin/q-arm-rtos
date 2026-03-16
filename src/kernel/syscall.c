#include "printf.h"
#include "task.h"
#include "uart.h"

extern tcb_t tcb_a, tcb_b, *current_task;
extern volatile uint64_t system_ticks; 

/**
 * syscall_handler - C dispatcher for SVC exceptions
 * @id: Syscall ID from x8
 * @arg0: First argument from x0
 */
void syscall_handler(unsigned long id, unsigned long arg0) {
    switch (id) {
        case 0: /* os_yield */
            /* Simply toggle current_task to the other one */
            current_task = (current_task == &tcb_a) ? &tcb_b : &tcb_a;
            break;

        case 1: /* os_sleep */
            {
                unsigned int ms = (unsigned int)arg0;
                current_task->sleep_ticks = ms / 10;
                current_task->state = TASK_SLEEPING;
                /* Context switch since current task is now blocked */
                current_task = (current_task == &tcb_a) ? &tcb_b : &tcb_a;
                printf("\n[SVC] Task Sleep: %d ms\n", ms);
            }
            break;

        case 2: /* os_get_uptime (New!) */
            {
                /* 1 tick = 10ms */
                uint64_t uptime_ms = system_ticks * 10;
                
                /* 
                 * Return value must be placed in the saved x0 slot.
                 * In your kernel_entry, x0 is at [sp, #0].
                 */
                uint64_t *saved_x0 = (uint64_t *)current_task->sp;
                *saved_x0 = uptime_ms; 
            }
            break;

        default:
            printf("\n[SVC] Unknown ID: %d\n", (int)id);
            break;
    }
}

