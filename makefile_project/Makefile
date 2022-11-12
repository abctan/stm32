########################################################################################################################## 
##########################################################################################################################

######################################
# target
######################################
TARGET := Example_Project
######################################
# building variables
######################################
# debug build
DEBUG := 1
# optimization
OPT := -O3
# print little=@ more=
Q = @
export Q
#######################################
ROOTDIR := $(shell pwd)
#######################################
# Build path
BUILD_DIR := build
######################################
# source
######################################
HAL_VERSION := STM32Cube_FW_F1_V1.8.0
export HAL_VERSION
# C subdir
SUB_DIRS :=     \
	app			\
	boot		\
	driver/cube \
	driver/sys  \
	driver/led

# common include path
INC_DIRS := \
	include \
	driver/cube/$(HAL_VERSION)/Drivers/STM32F1xx_HAL_Driver/Inc \
	driver/cube/$(HAL_VERSION)/Drivers/CMSIS/Device/ST/STM32F1xx/Include \
	driver/cube/$(HAL_VERSION)/Drivers/CMSIS/Include

# AS includes
AS_INCLUDES :=
INC_DIRS    := $(addprefix -I$(ROOTDIR)/, $(INC_DIRS))
OUT_DIR     := $(addprefix $(ROOTDIR)/, $(BUILD_DIR))

export AS_INCLUDES INC_DIRS OUT_DIR
#######################################
# gcc compiler
#######################################
CROSS_COMPILE := arm-none-eabi-

CC      	= $(CROSS_COMPILE)gcc
LD      	= $(CROSS_COMPILE)ld
AR      	= $(CROSS_COMPILE)ar
NM      	= $(CROSS_COMPILE)nm
SZ			= $(CROSS_COMPILE)size
OBJCOPY     = $(CROSS_COMPILE)objcopy
OBJDUMP     = $(CROSS_COMPILE)objdump
READELF     = $(CROSS_COMPILE)readelf
STRIP       = $(CROSS_COMPILE)strip

HEX := $(OBJCOPY) -O ihex
BIN := $(OBJCOPY) -O binary -S

MAKE := make

export CC LD AR NM OBJCOPY OBJDUMP READELF STRIP MAKE ROOTDIR
#######################################
# CFLAGS start
#######################################
# cpu
CPU := -mcpu=cortex-m3
# fpu
FPU :=
# float-abi
FLOAT-ABI :=
# mcu
MCU := $(CPU) -mthumb $(FPU) $(FLOAT-ABI)
# macros for gcc
# AS defines
AS_DEFS := 
# C defines
C_DEFS :=  \
	-DUSE_HAL_DRIVER \
	-DSTM32F103xE

# compile gcc flags
ASFLAGS := $(MCU) $(AS_DEFS) $(OPT) -Wall -fdata-sections -ffunction-sections
CFLAGS  := $(MCU) $(C_DEFS) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g3 -gdwarf-2
endif

export ASFLAGS CFLAGS
#######################################
# CFLAGS end
#######################################

#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT := boot/STM32F103XE_FLASH.ld

# libraries
LIBS    := -lc -lm -lnosys
LIBDIR  :=
LDFLAGS := $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections


#######################################
# build the application
#######################################
.PHONY: all clean $(SUB_DIRS)

all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin
	$(Q)$(SZ) $(BUILD_DIR)/$(TARGET).elf

$(BUILD_DIR)/$(TARGET).elf: $(BUILD_DIR) $(SUB_DIRS)
	$(if $(Q), $(Q)$(info LD   $@), )
	$(Q)$(CC) $(wildcard $(BUILD_DIR)/*.o) $(LDFLAGS) -o $@

# make subdir
$(SUB_DIRS):
	$(Q)$(MAKE) -C $@ all

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf
	$(if $(Q), $(Q)$(info HEX  $@), )
	$(Q)$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf
	$(if $(Q), $(Q)$(info BIN  $@), )
	$(Q)$(BIN) $< $@

# create obj path
$(BUILD_DIR):
	mkdir -p $@
#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)/*
#######################################

########################################################################################################################## 
##########################################################################################################################