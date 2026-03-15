# --- Platform Configuration ---
# Default to QEMU if no BOARD is specified
BOARD ?= qemu_virt

CROSS_COMPILE = aarch64-elf-
CC      = $(CROSS_COMPILE)gcc
LD      = $(CROSS_COMPILE)ld
QEMU    = qemu-system-aarch64

# --- Board Specific Flags ---
ifeq ($(BOARD), rpi3)
    BOARD_FLAG = -DBOARD_RPI3
    QEMU_CPU = cortex-a53
else ifeq ($(BOARD), rpi4)
    BOARD_FLAG = -DBOARD_RPI4
    QEMU_CPU = cortex-a72
else
    BOARD_FLAG = -DBOARD_QEMU_VIRT
    QEMU_CPU = cortex-a53
endif

# --- Directory Configuration ---
SRC_DIR = src
BUILD_DIR = build/$(BOARD)
INC_DIR = include

# --- Compiler flags ---
# Added $(BOARD_FLAG) to CFLAGS
CFLAGS  = -Wall -Wextra -march=armv8-a -nostdlib -nostartfiles -ffreestanding \
          -I$(INC_DIR) -g $(BOARD_FLAG)
LDFLAGS = -T linker.ld

# --- Source files ---
SRCS = arch/aarch64/startup.s \
       arch/aarch64/vectors.s \
       arch/aarch64/switch.s \
       kernel/main.c \
       kernel/irq.c \
       kernel/task.c \
       drivers/uart.c \
       drivers/timer.c \
       drivers/gic.c

# --- Object files ---
OBJS = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(SRCS))))

TARGET = $(BUILD_DIR)/q-arm-rtos.elf

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(LD) $(LDFLAGS) $(OBJS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Run on QEMU (Using the selected CPU)
run: $(TARGET)
	$(QEMU) -M virt,gic-version=2 -cpu $(QEMU_CPU) -nographic -kernel $(TARGET)

clean:
	rm -rf build/

.PHONY: all run clean