SRCEXT         := c
OBJEXT         := o
HEADEREXT      := h

## directories

LIB_DIR        := lib

## compiler options

EXEC_NAME      := scsh

CC             := gcc
CFLAGS         := -Wall -Ofast
CDBGFLAGS      := -Wall -g -fsanitize=address -D DEBUG
DBG            := gdb -q

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

## libshsc

$(LIB_DIR)/libshsc.a:
	@cd libshsc && $(MAKE)
	@cp libshsc/target/libshsc.a ./libshsc.a

$(LIB_DIR)/libshsc-dbg.a:
	@cd libshsc && $(MAKE) dbg
	@cp libshsc/target/libshsc-dbg.a ./libshsc-dbg.a

## cleanup

clean:
	@cd libdummy && $(MAKE) clean
	@cd libavl && $(MAKE) clean
	@cd libshsc && $(MAKE) clean

cleaner:
	@cd libdummy && $(MAKE) cleaner
	@cd libavl && $(MAKE) cleaner
	@cd libshsc && $(MAKE) cleaner
