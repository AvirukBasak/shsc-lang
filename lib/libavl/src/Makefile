SRCEXT      := c
OBJEXT      := o
HEADEREXT   := h

# directories

SRC_DIR     := ../src
BUILD_DIR   := ../build
TARGET_DIR  := ../target
LIB_DIR     := ../lib
TEST_DIR    := ../tests
INCLUDE_DIR := ../include

# compiler options

LIB_NAME    := avl

CC          := gcc
CFLAGS      := -Wall -Ofast
CDBGFLAGS   := -Wall -g -D DEBUG
DBG         := gdb -q

INCLUDE     := -I $(INCLUDE_DIR) -I $(LIB_DIR)
LIB         := -L$(LIB_DIR) -lm

HEADERS     := $(shell find $(INCLUDE_DIR)/ -name "*."$(HEADEREXT))

SUB_DIRS    := $(shell find -type f -name Makefile | sed 's/Makefile//g')
SUB_DIR_DBG := $(SUB_DIRS)

## release build

OBJECTS     := $(patsubst %.$(SRCEXT), %-rel.$(OBJEXT), $(wildcard *.$(SRCEXT)))

rel: mkdirp $(OBJECTS) cpobj

%-rel.$(OBJEXT): %.$(SRCEXT) $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

## build subdirs
# $(SUB_DIRS): FORCE
# @$(MAKE) -C $@

## debug build

DBG_OBJECTS := $(patsubst %.$(SRCEXT), %-dbg.$(OBJEXT), $(wildcard *.$(SRCEXT)))

dbg: mkdirp $(DBG_OBJECTS) cpobj

%-dbg.$(OBJEXT): %.$(SRCEXT) $(HEADERS)
	$(CC) $(CDBGFLAGS) $(INCLUDE) -c -o $@ $<

## build subdirs
# $(SUB_DIR_DBG): FORCE
#     @$(MAKE) -C $@ dbg

cpobj:
	@cp *.$(OBJEXT) $(BUILD_DIR)

mkdirp:
	@mkdir -p $(BUILD_DIR)

clean:
	@rm -f *.$(OBJEXT)

cleaner: clean
	@rm -f $(BUILD_DIR)/*.$(OBJEXT)

# FORCE:
