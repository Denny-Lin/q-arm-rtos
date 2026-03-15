markdown
# q-arm-rtos

A high-performance, preemptive Real-Time Operating System (RTOS) designed for modern ARM architectures (AArch64/ARMv9). Developed on macOS and optimized for QEMU-based virtualization.

## Overview

q-arm-rtos is a scalable, feature-rich RTOS kernel built from scratch. This project leverages the advanced features of modern ARM processors, providing a robust foundation for embedded systems and virtualization research.

## Technical Specifications

- Architecture: ARMv8-A / ARMv9-A (AArch64)
- CPU: Cortex-A53 (QEMU Emulated)
- Platform: QEMU virt machine
- Toolchain: aarch64-elf-gcc (Installed via Homebrew)

## Directory Structure

- src/arch/aarch64/: Boot code and architecture-specific logic.
- src/drivers/: Peripheral drivers (UART, Timer, GIC).
- src/kernel/: Kernel entry and core scheduling logic.
- include/: Header files and hardware abstractions.

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
To compile the source code and generate the ELF kernel image:

```bash
make
```

### Run on QEMU
To launch the RTOS in the QEMU emulator (nographic mode):

```bash
make run
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