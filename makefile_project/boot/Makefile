ASM_SOURCES := startup_stm32f103xe.s
OBJECTS := $(ASM_SOURCES:.s=.o)

BUILD_OBJS := $(addprefix $(OUT_DIR)/, $(OBJECTS))

.PHONY: all

all: $(BUILD_OBJS)

$(OUT_DIR)/%.o: %.s
	$(if $(Q), $(Q)$(info CC   $<), )
	$(Q)$(CC) $(ASFLAGS) -c $< -o $@