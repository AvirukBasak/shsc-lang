SRCEXT         := c
OBJEXT         := o
HEADEREXT      := h

## directories

LIB_DIR        := lib

## compiler options

EXEC_NAME      := scsh

CC             ?= clang
CFLAGS         := -Wall -O3
CDBGFLAGS      := -Wall -g -fsanitize=address -D DEBUG
DBG            := gdb -q

## go on listing your libraries below for compilation

## libavl

$(LIB_DIR)/libavl.a:
	@cd libavl && $(MAKE)
	@cp libavl/target/libavl.a ./libavl.a

$(LIB_DIR)/libavl-dbg.a:
	@cd libavl && $(MAKE) dbg
	@cp libavl/target/libavl-dbg.a ./libavl-dbg.a

## libshsc

$(LIB_DIR)/libshsc.a:
	@cd libshsc && $(MAKE)
	@cp libshsc/target/libshsc.a ./libshsc.a

$(LIB_DIR)/libshsc-dbg.a:
	@cd libshsc && $(MAKE) dbg
	@cp libshsc/target/libshsc-dbg.a ./libshsc-dbg.a

## cleanup

clean:
	@cd libavl && $(MAKE) clean
	@cd libshsc && $(MAKE) clean

cleaner:
	@cd libavl && $(MAKE) cleaner
	@cd libshsc && $(MAKE) cleaner
	@rm -f libavl.a libavl-dbg.a
	@rm -f libshsc.a libshsc-dbg.a
