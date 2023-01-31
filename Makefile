SRCEXT      := c
OBJEXT      := o
HEADEREXT   := h

# directories

SRC_DIR     := src
BUILD_DIR   := build
TARGET_DIR  := target
LIB_DIR     := lib
TEST_DIR    := tests
INCLUDE_DIR := include

# compiler options

EXE_NAME    := sch

CC          := gcc
CFLAGS      := -Wall -Ofast
CDBGFLAGS   := -Wall -g -D DEBUG
DBG         := gdb -q

INCLUDE     := -I $(INCLUDE_DIR) -I $(LIB_DIR)
LIB         := -L$(LIB_DIR) -lm -lavl

LIBRARIES   := $(LIB_DIR)/libavl.a

# targets

TARGET_NAME := $(EXE_NAME)
TARGET      := $(TARGET_DIR)/$(TARGET_NAME)-rel
DBG_TARGET  := $(TARGET_DIR)/$(TARGET_NAME)-dbg

SOURCES     := $(shell find $(SRC_DIR)/ -name "*."$(SRCEXT))
HEADERS     := $(shell find $(INCLUDE_DIR)/ -name "*."$(HEADEREXT))
TESTSRC     := $(shell find $(TEST_DIR)/ -name "*."$(SRCEXT))

## release build

rel: mkdirp $(LIBRARIES) $(TARGET)

OBJECTS     := $(patsubst $(SRC_DIR)/%.$(SRCEXT), $(BUILD_DIR)/%-rel.$(OBJEXT), $(shell find $(SRC_DIR)/ -name "*."$(SRCEXT)))

$(OBJECTS): $(SOURCES) $(HEADERS)
	@cd $(SRC_DIR) && $(MAKE)

$(TARGET): $(LIBRARIES) $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(BUILD_DIR)/*-rel.$(OBJEXT) $(LIB)

## debug build

dbg: mkdirp $(DBG_TARGET)

DBG_OBJECTS := $(patsubst $(SRC_DIR)/%.$(SRCEXT), $(BUILD_DIR)/%-dbg.$(OBJEXT), $(shell find $(SRC_DIR)/ -name "*."$(SRCEXT)))

$(DBG_OBJECTS): $(SOURCES) $(HEADERS)
	@cd $(SRC_DIR) && $(MAKE) dbg

$(DBG_TARGET): $(LIBRARIES) $(DBG_OBJECTS)
	$(CC) $(CDBGFLAGS) -o $(DBG_TARGET) $(BUILD_DIR)/*-dbg.$(OBJEXT) $(LIB)

## build libraries
$(LIBRARIES):
	@cd $(LIB_DIR) && $(MAKE)

## testing / execution

run: rel $(TESTSRC)
	./$(TARGET) $(ARGS)

rundbg: dbg $(TESTSRC)
	$(DBG) $(DBG_TARGET)

## mkdirp

mkdirp:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(TARGET_DIR)

## cleanup

clean:
	@cd $(SRC_DIR) && $(MAKE) clean
	@cd $(LIB_DIR) && $(MAKE) clean
	@rm -rf $(TEST_DIR)/*.out

cleaner:
	@cd $(SRC_DIR) && $(MAKE) cleaner
	@cd $(LIB_DIR) && $(MAKE) cleaner
	@rm -rf $(TEST_DIR)/*.out
	@rm -rf $(BUILD_DIR)
	@rm -rf $(TARGET_DIR)
