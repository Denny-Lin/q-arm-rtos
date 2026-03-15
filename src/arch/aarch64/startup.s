.section ".text.boot"
.global _start

_start:
    /* Read CPU ID */
    mrs     x0, mpidr_el1
    and     x0, x0, #0xFF
    /* If not Core 0, go to infinite loop (sleep) */
    cbz     x0, master
hang:
    wfe
    b       hang

master:
    /* Setup stack */
    ldr     x0, =stack_top
    mov     sp, x0
    bl      main
    b       hang