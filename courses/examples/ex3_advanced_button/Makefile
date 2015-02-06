#-------------------------------------------------------------------------------
#		Tools
#-------------------------------------------------------------------------------

# Tool suffix when cross-compiling
CROSS_COMPILE = arm-none-eabi-

# Compilation tools
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
SIZE = $(CROSS_COMPILE)size
STRIP = $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy
GDB = $(CROSS_COMPILE)gdb
NM = $(CROSS_COMPILE)nm

RESOURCES_PATH = ../resources
RESOURCES_OPENOCD = $(RESOURCES_PATH)/openocd/atmel_sam4s_xplained.cfg
RESOURCES_GDB = $(RESOURCES_PATH)/gdb/atmel_sam4s_xplained.gdb
RESOURCES_LINKER = sam4s_xplained_LAB.ld

INCLUDES  = -I../CMSIS/CMSIS/Include
INCLUDES += -I../CMSIS/Device/ATMEL

DEVICE = __SAM4S16C__
CORE = cortex-m4

OUTPUT_PATH = build_makefile
OUTPUT_NAME = ex3_advanced_button
OUTPUT_FILE = $(OUTPUT_NAME).elf
OUTPUT_FILE_PATH = $(OUTPUT_PATH)/$(OUTPUT_FILE)

CFLAGS += -Wall -Wchar-subscripts -Wcomment -Wformat=2 -Wimplicit-int
CFLAGS += -Werror-implicit-function-declaration -Wmain -Wparentheses
CFLAGS += -Wsequence-point -Wreturn-type -Wswitch -Wtrigraphs -Wunused
CFLAGS += -Wuninitialized -Wunknown-pragmas -Wfloat-equal -Wundef
CFLAGS += -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings
CFLAGS += -Wsign-compare -Waggregate-return -Wstrict-prototypes
CFLAGS += -Wmissing-prototypes -Wmissing-declarations
CFLAGS += -Wformat -Wmissing-format-attribute -Wno-deprecated-declarations
CFLAGS += -Wpacked -Wredundant-decls -Wnested-externs -Wlong-long
CFLAGS += -Wunreachable-code -Wcast-align
# -Wmissing-noreturn -Wconversion
CFLAGS += --param max-inline-insns-single=500 -mcpu=$(CORE) -mthumb -ffunction-sections -fdata-sections
# -MMD -nostdlib
CFLAGS += -D$(DEVICE)
CFLAGS += -g3 -O0

LDFLAGS = -mcpu=$(CORE) -mthumb -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align

VPATH = .

OBJS += \
$(OUTPUT_PATH)/ex3_advanced_button.o \
$(OUTPUT_PATH)/startup_sam4s.o \
$(OUTPUT_PATH)/system_sam4s.o


all: build

build: create_build_folder $(OBJS)
	$(CC) -L. $(CFLAGS) "-T$(RESOURCES_LINKER)" "-Wl,-Map,$(OUTPUT_PATH)/$(OUTPUT_NAME).map" --specs=nano.specs --specs=nosys.specs $(LDFLAGS) -o "$(OUTPUT_FILE_PATH)" $(OBJS) -Wl,--start-group -lm -Wl,--end-group
	$(NM) $(OUTPUT_FILE_PATH) >$(OUTPUT_FILE_PATH).txt
	$(OBJCOPY) -O binary $(OUTPUT_FILE_PATH) $(OUTPUT_PATH)/$(OUTPUT_NAME).bin
	$(SIZE) -A $(OUTPUT_FILE_PATH)

create_build_folder:
	-mkdir $(OUTPUT_PATH)

clean:

flash: build
	openocd -f "$(RESOURCES_OPENOCD)" -c "program $(OUTPUT_FILE_PATH) verify reset"

debug: build
	$(GDB) -x "$(RESOURCES_GDB)" -ex "reset" -readnow -se $(OUTPUT_FILE_PATH)

$(OUTPUT_PATH)/%.o : %.c
	$(CC) $(INCLUDES) $(CFLAGS) -c -o $@ $<

.phony: create_build_folder clean

