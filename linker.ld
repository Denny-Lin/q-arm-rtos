ENTRY(_start)
SECTIONS
{
    . = 0x40000000;
    .text : { KEEP(*(.text.boot)) *(.text) }
    .rodata : { *(.rodata) }
    .data : { *(.data) }
    .bss : {
        . = ALIGN(16);
        __bss_start = .;
        *(.bss)
        __bss_end = .;
    }
    . = ALIGN(16);
    . += 0x4000;
    stack_top = .;
}
