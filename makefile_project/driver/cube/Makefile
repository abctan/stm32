C_SOURCES := \
	stm32f1xx_hal_tim.c \
	stm32f1xx_hal_tim_ex.c \
	stm32f1xx_hal_uart.c \
	stm32f1xx_hal.c \
	stm32f1xx_hal_i2c.c \
	stm32f1xx_hal_rcc.c \
	stm32f1xx_hal_rcc_ex.c \
	stm32f1xx_hal_flash.c \
	stm32f1xx_hal_flash_ex.c \
	stm32f1xx_hal_gpio.c \
	stm32f1xx_hal_dma.c \
	stm32f1xx_hal_pwr.c \
	stm32f1xx_hal_cortex.c

H_SOURCES := \
	$(ROOTDIR)/include \
	$(HAL_VERSION)/Drivers/STM32F1xx_HAL_Driver/Inc \
	$(HAL_VERSION)/Drivers/CMSIS/Device/ST/STM32F1xx/Include \
	$(HAL_VERSION)/Drivers/CMSIS/Include

VPATH      := $(HAL_VERSION)/Drivers/STM32F1xx_HAL_Driver/Src
OBJECTS    := $(C_SOURCES:.c=.o)
BUILD_OBJS := $(addprefix $(OUT_DIR)/, $(OBJECTS))
CFLAGS     += $(addprefix -I, $(H_SOURCES))

.PHONY: all

all: $(BUILD_OBJS)

$(OUT_DIR)/%.o: %.c
	$(if $(Q), $(Q)$(info CC   $<), )
	$(Q)$(CC) $(CFLAGS) -c $< -o $@