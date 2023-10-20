SRCEXT      := c
OBJEXT      := o
HEADEREXT   := h

# directories

SRC_DIR     := ../../src
BUILD_DIR   := ../../build
BIN_DIR     := ../../bin
LIB_DIR     := ../../lib
TEST_DIR    := ../../tests
INCLUDE_DIR := ../../include

# compiler options

LIB_NAME    := libdummy

CC          := gcc
CFLAGS      := -Wall -Ofast
CDBGFLAGS   := -Wall -g -D DEBUG
DBG         := gdb -q

all: $(LIB_DIR)/libdummy.a

$(LIB_DIR)/libdummy.a: dummy.$(SRCEXT)
	$(CC) $(CFLAGS) -c -o dummy.$(OBJEXT) dummy.$(SRCEXT)
	ar rcs $(LIB_DIR)/libdummy.a dummy.$(OBJEXT)

clean:
	@rm -f $(LIB_DIR)/libdummy.a
	@rm -f dummy.o

cleaner: clean
