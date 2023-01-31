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

LIB_NAME    := mylib

CC          := gcc
CFLAGS      := -Wall -Ofast
CDBGFLAGS   := -Wall -g -D DEBUG
DBG         := gdb -q

INCLUDE     := -I $(INCLUDE_DIR) -I $(LIB_DIR)
LIB         := -L$(LIB_DIR) -lm

## go on listing your libraries below for compilation

all:
	@cd libdummy && $(MAKE)

clean:
	@cd libdummy && $(MAKE) clean

cleaner:
	@cd libdummy && $(MAKE) cleaner
