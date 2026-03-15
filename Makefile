CROSS_COMPILE = aarch64-elf-
CC      = $(CROSS_COMPILE)gcc
LD      = $(CROSS_COMPILE)ld
QEMU    = qemu-system-aarch64

CFLAGS  = -Wall -Wextra -march=armv8-a -nostdlib -nostartfiles -ffreestanding -Iinclude -g
LDFLAGS = -T linker.ld

# Updated Paths
SRCS = src/arch/aarch64/startup.s \
       src/kernel/main.c \
       src/drivers/uart.c

# Automatically generate object file list in the same folders
OBJS = $(SRCS:.s=.o)
OBJS := $(OBJS:.c=.o)

TARGET = q-arm-rtos.elf

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(TARGET)

# Rule for assembly files
%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for C files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	$(QEMU) -M virt -cpu cortex-a53 -nographic -kernel $(TARGET)

clean:
	rm -f $(OBJS) *.elf

.PHONY: all run clean