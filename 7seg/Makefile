TARGET      = 7seg
TARGET_DIR  = target
SRC_DIR     = src
STARTUP_DIR = startup
LINKER_DIR  = linker
LPC8XX      = ../lpc8xx
CMSIS       = $(LPC8XX)/cmsis
STARTUP     = $(LPC8XX)/startup

TARGET_ELF  = $(TARGET_DIR)/$(TARGET).elf
TARGET_HEX  = $(TARGET_DIR)/$(TARGET).hex
TARGET_BIN  = $(TARGET_DIR)/$(TARGET).bin

CSRCS    = $(SRC_DIR)/main.c
CSRCS   += $(STARTUP)/gcc_startup_lpc8xx.c
LNKSRC   = $(LINKER_DIR)/lpc810.ld

USB      = /dev/ttyUSB0

CROSS    = arm-none-eabi-
GCC      = $(CROSS)gcc
OBJCOPY  = ${CROSS}objcopy

LPC21ISP = lpc21isp

MKDIR    = mkdir

CFLGS    = -g -O2 -Wall
CFLGS   += -T $(LNKSRC)
CFLGS   += -mthumb -mcpu=cortex-m0plus -MD
CFLGS   += -Wl,--gc-sections
CFLGS   += -I $(CMSIS)

all: $(TARGET_ELF)

$(TARGET_ELF): $(CSRCS)
	$(MKDIR) -p $(TARGET_DIR)
	$(GCC) $(CFLGS) $^ -o $@
	$(OBJCOPY) -O ihex $(TARGET_ELF) $(TARGET_HEX)
	$(OBJCOPY) -O binary $(TARGET_ELF) $(TARGET_BIN)

version:
	$(GCC) --version

burn:
	$(LPC21ISP) $(TARGET_HEX) -term $(USB) 115200 12000

clean:
	rm -rf $(TARGET_DIR)
