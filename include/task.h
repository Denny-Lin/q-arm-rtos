#ifndef TASK_H
#define TASK_H

#include <stdint.h>

/* Task Control Block (TCB) - The identity of a task */
typedef struct {
    uint64_t *sp;       /* Current Stack Pointer (Where registers are saved) */
    uint32_t state;     /* 0: Ready, 1: Running */
} tcb_t;

/* We'll start with 2 simple tasks */
void task_create(void (*task_func)(void));
void scheduler(void);

#endif

