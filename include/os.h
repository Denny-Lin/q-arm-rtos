#ifndef OS_H
#define OS_H

#include <stdint.h>

/**
 * os_yield - Voluntarily yield the CPU to the next task (Syscall ID 0)
 */
static inline void os_yield(void) {
    asm volatile (
        "mov x8, #0\n"      /* Syscall ID 0 for Yield */
        "svc #0\n"          /* Trigger Supervisor Call */
        : : : "x8"
    );
}

/**
 * os_sleep - Block the current task for specified milliseconds (Syscall ID 1)
 */
static inline void os_sleep(uint32_t ms) {
    asm volatile (
        "mov x0, %0\n"      /* ms goes to x0 */
        "mov x8, #1\n"      /* Syscall ID 1 for Sleep */
        "svc #0\n"
        : : "r"(ms) : "x0", "x8"
    );
}

#endif

static inline uint64_t os_get_uptime(void) {
    uint64_t ms;
    asm volatile (
        "mov x8, #2\n"    /* Syscall ID 2 */
        "svc #0\n"
        "mov %0, x0\n"    /* The kernel placed the result in x0 */
        : "=r"(ms)        /* Output to 'ms' variable */
        : : "x8", "x0"    /* Clobbers */
    );
    return ms;
}