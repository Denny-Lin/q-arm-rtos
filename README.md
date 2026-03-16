# q-arm-rtos

A high-performance, preemptive Real-Time Operating System (RTOS) designed for modern ARM architectures (AArch64/ARMv9). Developed on macOS and optimized for QEMU-based virtualization.

## Overview

q-arm-rtos is a scalable, feature-rich RTOS kernel built from scratch. This project leverages the advanced features of modern ARM processors, providing a robust foundation for embedded systems and multitasking research.

## Core Features (Achieved)

- **System Call Pipeline (SVC)**: Robust `svc #0` handling with parameter passing for `os_yield()` and `os_sleep(ms)`.
- **Dynamic Memory Allocation**: Integrated Kernel Heap with 16-byte aligned `kmalloc()` supporting AArch64 hardware requirements.
- **Task State Management**: Sophisticated scheduler supporting READY and SLEEPING states to optimize CPU utilization.
- **Kernel Printf**: Custom implementation of formatted string output for real-time debugging.
- **Preemptive Multitasking**: Priority-based scheduling with 10ms time-slicing and IRQ-driven context switches.


## Technical Specifications

- **Architecture**: ARMv8-A / ARMv9-A (AArch64)
- **CPU Support**: Cortex-A53 (RPi3 / QEMU), Cortex-A72 (RPi4)
- **Privilege Level**: Runs in Exception Level 1 (EL1)
- **Platform**: QEMU virt machine, Raspberry Pi 3, Raspberry Pi 4
- **Toolchain**: aarch64-elf-gcc (Version 15.2.0+)

## Directory Structure

- `src/arch/aarch64/`: Boot code, Exception Vectors (Macros), and Context Switching logic.
- `src/kernel/`: IRQ dispatcher, Syscall handlers, Task management, and Memory allocation.
- `include/`: Kernel APIs (`os.h`), Task structures, and hardware register definitions.

## Current Status

The kernel successfully manages two independent tasks (Task A & Task B). 
- **Task A** demonstrates cooperative multitasking using `os_sleep(1000)`.
- **Task B** utilizes the remaining CPU time through preemptive scheduling.
- **Memory** is dynamically managed via the kernel heap at boot time.

## Development Environment

Developed and tested on macOS using Homebrew toolchains.

### Prerequisites

```bash
# Install AArch64 cross-compiler and QEMU
brew install aarch64-elf-gcc
brew install qemu
```

## Compilation and Execution

### Build the Kernel
The project supports multiple platforms. Use the **BOARD** variable to specify the target.

```bash
# Default (QEMU Virt)
make BOARD=qemu_virt

# Raspberry Pi 3
make BOARD=rpi3

# Raspberry Pi 4
make BOARD=rpi4
```

### Run on QEMU
To launch the RTOS in the QEMU emulator (nographic mode):

```bash
make BOARD=qemu_virt run
```

### Exit QEMU
Since the system runs in nographic mode, use the following key combination to exit:

Press **Ctrl + A**, then release and press **X**.

### Clean Build Files
To remove object files and the kernel image:

```bash
make clean
```

---

## Copyright

Copyright (c) 2026. All Rights Reserved. Private Property.  
Unauthorized reproduction, modification, or distribution is strictly prohibited.
