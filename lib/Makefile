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

## compiler options

EXEC_NAME      := scsh

CC             := gcc
CFLAGS         := -Wall -Ofast
CDBGFLAGS      := -Wall -g -fsanitize=address -D DEBUG
DBG            := gdb -q

## targets

TARGET_NAME    := $(EXEC_NAME)
TARGET         := $(TARGET_DIR)/$(TARGET_NAME)-rel
DBG_TARGET     := $(TARGET_DIR)/$(TARGET_NAME)-dbg

## go on listing your libraries below for compilation

## libdummy

$(LIB_DIR)/libdummy.a:
	@cd libdummy && $(MAKE)

$(LIB_DIR)/libdummy-dbg.a:
	@cd libdummy && $(MAKE) dbg

## libavl

$(LIB_DIR)/libavl.a:
	@cd libavl && $(MAKE)

$(LIB_DIR)/libavl-dbg.a:
	@cd libavl && $(MAKE) dbg

## cleanup

clean:
	@cd libdummy && $(MAKE) clean
	@cd libavl && $(MAKE) clean

cleaner:
	@cd libdummy && $(MAKE) cleaner
	@cd libavl && $(MAKE) cleaner
