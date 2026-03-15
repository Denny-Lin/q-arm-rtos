#ifndef BOARD_H
#define BOARD_H

/* QEMU Virt Platform (Default) */
#ifdef BOARD_QEMU_VIRT
    #define UART0_BASE    0x09000000
    #define GIC_DIST_BASE 0x08000000
#endif

/* Raspberry Pi 3 (BCM2837) */
#ifdef BOARD_RPI3
    #define UART0_BASE    0x3F201000
    #define GPIO_BASE     0x3F200000
#endif

/* Raspberry Pi 4 (BCM2711) */
#ifdef BOARD_RPI4
    #define UART0_BASE    0xFE201000
    #define GPIO_BASE     0xFE200000
#endif

#endif
