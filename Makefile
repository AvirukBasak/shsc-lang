SRCEXT         := c
OBJEXT         := o
HEADEREXT      := h

## directories

SRC_DIR        := src
BUILD_DIR      := build
TARGET_DIR     := target
LIB_DIR        := lib
TEST_DIR       := tests
INCLUDE_DIR    := include

REQ_DIRS       := $(BUILD_DIR) $(TARGET_DIR)

## compiler options

EXEC_NAME      := shsc

CC             := gcc
CFLAGS         := -Wall -Wno-unused-label -Ofast
CDBGFLAGS      := -Wall -Wno-unused-label -g -fsanitize=address -D DEBUG
DBG            := gdb -q

INCLUDE        := -I $(INCLUDE_DIR) -I $(LIB_DIR) -I $(SRC_DIR)
LIB            := -L$(LIB_DIR) -lm -lavl
DBG_LIB        := -L$(LIB_DIR) -lm -lavl-dbg

LIBRARIES      := $(LIB_DIR)/libavl.a
DBG_LIBRARIES  := $(LIB_DIR)/libavl-dbg.a

## targets
# Detect the operating system
ifeq ($(OS),Windows_NT)
	EXE_EXTENSION := .exe
else
	EXE_EXTENSION :=
endif

TARGET_NAME    := $(EXEC_NAME)
TARGET         := $(TARGET_DIR)/$(TARGET_NAME)-rel$(EXE_EXTENSION)
DBG_TARGET     := $(TARGET_DIR)/$(TARGET_NAME)-dbg$(EXE_EXTENSION)

SOURCES        := $(shell find $(SRC_DIR)/ -name "*."$(SRCEXT)) $(shell find $(SRC_DIR)/ -name "*".$(SRCEXT).$(HEADEREXT))
HEADERS        := $(shell find $(INCLUDE_DIR)/ -name "*."$(HEADEREXT))
TESTSRC        := $(shell find $(TEST_DIR)/ -name "*."$(SRCEXT))

PARSER         := $(INCLUDE_DIR)/parser.yy.h $(SRC_DIR)/parser.yy.c

## release build

rel: $(TARGET)

OBJECTS        := $(patsubst $(SRC_DIR)/%.$(SRCEXT), $(BUILD_DIR)/%-rel.$(OBJEXT), $(shell find $(SRC_DIR)/ -name "*."$(SRCEXT)))

$(OBJECTS): $(SOURCES) $(HEADERS) $(PARSER)
	@cd $(SRC_DIR) && $(MAKE)

## target for executable
$(TARGET): $(REQ_DIRS) $(LIBRARIES) $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(BUILD_DIR)/*-rel.$(OBJEXT) $(LIB)

# Get the first 27 characters of the PREFIX environment variable
PREFIX_SUBSTRING := $(shell echo $${PREFIX} | cut -c 1-27)

install: $(TARGET)
	cp $(TARGET) $(PREFIX_SUBSTRING)/usr/bin/$(EXEC_NAME)$(EXE_EXTENSION)

## debug build

dbg: $(DBG_TARGET)

DBG_OBJECTS    := $(patsubst $(SRC_DIR)/%.$(SRCEXT), $(BUILD_DIR)/%-dbg.$(OBJEXT), $(shell find $(SRC_DIR)/ -name "*."$(SRCEXT)))

$(DBG_OBJECTS): $(SOURCES) $(HEADERS) $(PARSER)
	@cd $(SRC_DIR) && $(MAKE) dbg

## parser source
$(PARSER): $(SRC_DIR)/parser.y
	bison --defines=$(INCLUDE_DIR)/parser.yy.h -o $(SRC_DIR)/parser.yy.c $(SRC_DIR)/parser.y

## target for debug executable
$(DBG_TARGET): $(REQ_DIRS) $(DBG_LIBRARIES) $(DBG_OBJECTS)
	$(CC) $(CDBGFLAGS) -o $(DBG_TARGET) $(BUILD_DIR)/*-dbg.$(OBJEXT) $(DBG_LIB)

## build libraries
$(LIBRARIES):
	@cd $(LIB_DIR) && $(MAKE) $(LIBRARIES)

$(DBG_LIBRARIES):
	@cd $(LIB_DIR) && $(MAKE) $(DBG_LIBRARIES)

## running executable

run: $(TARGET) $(TESTSRC)
	./$(TARGET) $(ARGS)

run-sanitize: $(DBG_TARGET) $(TESTSRC)
	@ASAN_OPTIONS=detect_leaks=1 ./$(DBG_TARGET) $(ARGS)

run-dbg: $(DBG_TARGET) $(TESTSRC)
	$(DBG) $(DBG_TARGET)

## $(REQ_DIRS)

$(BUILD_DIR):
	@mkdir -p $(TARGET_DIR)

$(TARGET_DIR):
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
	@rm -rf $(TARGET)
	@rm -rf $(DBG_TARGET)
	@rm -rf $(HDR_TARGET)
	@rm -rf $(TARGET_DIR)
	@rm -f $(SRC_DIR)/parser.yy.c
	@rm -f $(INCLUDE_DIR)/parser.yy.h
