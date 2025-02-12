CC      ?= gcc
CFLAGS  += -std=c99 -Wall -Wextra -pedantic -O3
CFLAGS  += -D_POSIX_C_SOURCE=200809L
LDFLAGS ?=
LDLIBS  ?=

TARGET    := mls
SRC_DIR   := src
BUILD_DIR := build
BIN_DIR   := bin

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

EXECUTABLE := $(BIN_DIR)/$(TARGET)

.PHONY: all clean release debug directories

all: release

release: CFLAGS += -O3 -DNDEBUG
release: $(EXECUTABLE)

debug: CFLAGS += -g -O0 -fsanitize=undefined -fsanitize=address
debug: LDFLAGS += -fsanitize=undefined -fsanitize=address
debug: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS) | $(BIN_DIR)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c -o $@ $<

$(BUILD_DIR) $(BIN_DIR):
	@mkdir -p $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

-include $(DEPS)

help:
	@echo "Available targets:"
	@echo "  all/release:  Optimized build (default)"
	@echo "  debug:        Debug build with sanitizers"
	@echo "  clean:        Remove all build artifacts"
	@echo "  help:         Show this help message"

.DEFAULT_GOAL := all