SRCEXT      := c
OBJEXT      := o
HEADEREXT   := h

# directories

SRC_DIR     := src
BUILD_DIR   := build
TARGET_DIR  := ../../lib
LIB_DIR     := lib
TEST_DIR    := tests
INCLUDE_DIR := include

# compiler options

LIB_NAME    := avl

CC          := gcc
CFLAGS      := -Wall -Ofast
CDBGFLAGS   := -Wall -g -D DEBUG
DBG         := gdb -q

INCLUDE     := -I $(INCLUDE_DIR) -I $(LIB_DIR)
LIB         := -L$(LIB_DIR) -lm

LIBRARIES   := $(shell find $(LIB_DIR)/ -name "*.a")

# targets

TARGET_NAME := lib$(LIB_NAME)
TARGET      := $(TARGET_DIR)/$(TARGET_NAME).a
DBG_TARGET  := $(TARGET_DIR)/$(TARGET_NAME)-dbg.a
HDR_TARGET  := $(TARGET_DIR)/$(TARGET_NAME).$(HEADEREXT)

SOURCES     := $(shell find $(SRC_DIR)/ -name "*."$(SRCEXT))
HEADERS     := $(shell find $(INCLUDE_DIR)/ -name "*."$(HEADEREXT))
TESTSRC     := $(shell find $(TEST_DIR)/ -name "*."$(SRCEXT))

## release build

rel: mkdirp $(HDR_TARGET) $(TARGET)

OBJECTS     := $(patsubst $(SRC_DIR)/%.$(SRCEXT), $(BUILD_DIR)/%-rel.$(OBJEXT), $(shell find $(SRC_DIR)/ -name "*."$(SRCEXT)))

$(OBJECTS): $(SOURCES) $(HEADERS)
	@cd $(SRC_DIR) && $(MAKE)

$(TARGET): $(LIBRARIES) $(OBJECTS)
	ar rcs $(TARGET) $(BUILD_DIR)/*-rel.$(OBJEXT)

## debug build

dbg: mkdirp $(HDR_TARGET) $(DBG_TARGET)

DBG_OBJECTS := $(patsubst $(SRC_DIR)/%.$(SRCEXT), $(BUILD_DIR)/%-dbg.$(OBJEXT), $(shell find $(SRC_DIR)/ -name "*."$(SRCEXT)))

$(DBG_OBJECTS): $(SOURCES) $(HEADERS)
	@cd $(SRC_DIR) && $(MAKE) dbg

$(DBG_TARGET): $(LIBRARIES) $(DBG_OBJECTS)
	ar rcs $(DBG_TARGET) $(BUILD_DIR)/*-dbg.$(OBJEXT)

## make lib headers

$(HDR_TARGET): $(INCLUDE_DIR)/$(TARGET_NAME).$(HEADEREXT)
	@cp $(INCLUDE_DIR)/$(TARGET_NAME).$(HEADEREXT) $(HDR_TARGET)
	$(info make $(HDR_TARGET))

## build libraries
$(LIBRARIES):
	@cd $(LIB_DIR) && $(MAKE)

## testing / execution

test: rel $(TESTSRC)
	@$(CC) $(CFLAGS) -I $(TARGET_DIR) $(TEST_DIR)/*.$(SRCEXT) -o $(TEST_DIR)/test-rel.out -L$(TARGET_DIR) -l$(LIB_NAME) $(LIB)
	./$(TEST_DIR)/test-rel.out

testdbg: dbg $(TESTSRC)
	@$(CC) $(CDBGFLAGS) -I $(TARGET_DIR) $(DBG_OBJECTS) $(TEST_DIR)/*.$(SRCEXT) -o $(TEST_DIR)/test-dbg.out $(LIB)
	$(DBG) $(TEST_DIR)/test-dbg.out

## mkdirp

mkdirp:
	@mkdir -p $(BUILD_DIR)
	# @mkdir -p $(TARGET_DIR)

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
	@rm -rf $(TARGET)
	@rm -rf $(DBG_TARGET)
	@rm -rf $(HDR_TARGET)
