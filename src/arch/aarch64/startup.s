.section ".text.boot"
.global _start

_start:
    /* Check processor ID: only core 0 proceeds */
    mrs     x0, mpidr_el1
    and     x0, x0, #0xFF
    cbz     x0, master
hang:
    wfe
    b       hang

master:
    /* Setup stack pointer */
    ldr     x0, =stack_top
    mov     sp, x0

    /* Clear BSS (optional but recommended) */
    /* Jump to C main */
    bl      main
    b       hang
