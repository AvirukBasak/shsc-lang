SRCEXT         := c
OBJEXT         := o
HEADEREXT      := h

# directories

TARGET_DIR        := ../../lib

# compiler options

LIB_NAME       := libdummy

CC             := gcc
CFLAGS         := -Wall -Ofast
CDBGFLAGS      := -Wall -g -D DEBUG
DBG            := gdb -q

all: $(TARGET_DIR)/libdummy.a

dbg: $(TARGET_DIR)/libdummy-dbg.a

$(TARGET_DIR)/libdummy.a: dummy.$(SRCEXT)
	$(CC) $(CFLAGS) -c -o dummy.$(OBJEXT) dummy.$(SRCEXT)
	ar rcs $(TARGET_DIR)/libdummy.a dummy.$(OBJEXT)

$(TARGET_DIR)/libdummy-dbg.a: dummy.$(SRCEXT)
	$(CC) $(CDBGFLAGS) -c -o dummy.$(OBJEXT) dummy.$(SRCEXT)
	ar rcs $(TARGET_DIR)/libdummy-dbg.a dummy.$(OBJEXT)

clean:
	@rm -f $(TARGET_DIR)/libdummy.a
	@rm -f dummy.o

cleaner: clean
