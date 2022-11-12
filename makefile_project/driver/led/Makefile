C_SOURCES := led.c

H_SOURCES := $(ROOTDIR)/driver/include

OBJECTS    := $(C_SOURCES:.c=.o)
BUILD_OBJS := $(addprefix $(OUT_DIR)/, $(OBJECTS))
INC_DIRS   += $(addprefix -I, $(H_SOURCES))

.PHONY: all

all: $(BUILD_OBJS)

$(OUT_DIR)/%.o: %.c
	$(if $(Q), $(Q)$(info CC   $<), )
	$(Q)$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@