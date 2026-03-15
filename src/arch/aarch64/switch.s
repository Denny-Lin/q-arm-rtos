// src/arch/aarch64/switch.s
// Context Switch logic for AArch64 RTOS

.global cpu_switch_to

// void cpu_switch_to(tcb_t *prev, tcb_t *next);
// x0 = struct tcb_t *prev (Current Task)
// x1 = struct tcb_t *next (Next Task)

cpu_switch_to:
    /* 1. Save current task's context */
    /* Store Callee-saved registers to current stack */
    mov     x8, sp
    stp     x19, x20, [sp, #-16]!
    stp     x21, x22, [sp, #-16]!
    stp     x23, x24, [sp, #-16]!
    stp     x25, x26, [sp, #-16]!
    stp     x27, x28, [sp, #-16]!
    stp     x29, x30, [sp, #-16]!
    str     x8, [sp, #-16]!      /* Save original SP */

    /* Save current SP to prev->sp (x0 is the address of tcb_t) */
    mov     x8, sp
    str     x8, [x0]

    /* 2. Restore next task's context */
    /* Load new SP from next->sp (x1 is the address of tcb_t) */
    ldr     x8, [x1]
    mov     sp, x8

    /* Restore registers from the new stack */
    ldr     x8, [sp], #16        /* Restore saved SP */
    ldp     x29, x30, [sp], #16
    ldp     x27, x28, [sp], #16
    ldp     x25, x26, [sp], #16
    ldp     x23, x24, [sp], #16
    ldp     x21, x22, [sp], #16
    ldp     x19, x20, [sp], #16
    
    /* Return to the next task's saved PC (x30/LR) */
    ret

