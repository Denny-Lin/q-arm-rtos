# q-arm-rtos

A high-performance, preemptive Real-Time Operating System (RTOS) designed for modern ARM architectures (AArch64/ARMv9). Developed on macOS and optimized for QEMU-based virtualization.

## Overview

**q-arm-rtos** is a scalable, feature-rich RTOS kernel built from scratch. Unlike "mini" or educational kernels, this project aims to leverage the advanced features of modern ARM processors, providing a robust foundation for embedded systems and virtualization research.

### Key Features (Roadmap)
- **Architecture**: Native support for **ARMv8-A / ARMv9-A (AArch64)**.
- **Scheduler**: Priority-based preemptive multitasking with time-slicing.
- **Memory Management**: Advanced MMU configuration and heap management.
- **Interrupts**: Full integration with **GIC (Generic Interrupt Controller)**.
- **Hardware Platform**: Optimized for the **QEMU `virt` machine**.

## Development Environment

Developed and tested on **macOS** using Homebrew toolchains.

### Prerequisites
```bash
# Install ARM toolchain and QEMU
brew install --cask gcc-arm-embedded
brew install qemu
