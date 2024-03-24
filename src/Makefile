SRCEXT         := c
OBJEXT         := o
HEADEREXT      := h

## directories

SRC_DIR        := ../src
BUILD_DIR      := ../build
TARGET_DIR     := ../target
LIB_DIR        := ../lib
TEST_DIR       := ../tests
INCLUDE_DIR    := ../include

## compiler options

EXEC_NAME      := shsc

WRN_ERR_FLAGS  := -Wall\
				  -Wno-unused-but-set-variable\
				  -Wno-unused-label\
				  -Wno-int-in-bool-context
ASAN_FLAGS	 := -fsanitize=address
ASAN_OPTIONS   := ASAN_OPTIONS=detect_leaks=1:$\
				  fast_unwind_on_malloc=0:$\
				  strict_init_order=true:$\
				  strict_string_checks=true:$\
				  check_initialization_order=true:$\
				  abort_on_error=1:$\
				  symbolize=1:$\
				  verbosity=0:$\
				  halt_on_error=0

CC             := gcc
CFLAGS         := $(WRN_ERR_FLAGS) -Ofast
CDBGFLAGS      := $(WRN_ERR_FLAGS) -g $(ASAN_FLAGS) -D DEBUG
DBG            := gdb -q

INCLUDE        := -I $(INCLUDE_DIR) -I $(LIB_DIR) -I $(SRC_DIR)
LIB            := -L$(LIB_DIR) -lm -lavl
DBG_LIB        := -L$(LIB_DIR) -lm -lavl-dbg

HEADERS        := $(shell find $(INCLUDE_DIR)/ -name "*."$(HEADEREXT))

SUB_DIRS       := $(shell find -type f -name Makefile | sed 's/Makefile//g')
SUB_DIR_DBG    := $(SUB_DIRS)

## source code headers

AST_SRC_CH     := $(shell find $(SRC_DIR)/ast/ -name "*".$(SRCEXT).$(HEADEREXT))
LEXER_SRC_CH   := $(shell find $(SRC_DIR)/lexer/ -name "*".$(SRCEXT).$(HEADEREXT))
PARSER_SRC_CH  := $(shell find $(SRC_DIR)/parser/ -name "*".$(SRCEXT).$(HEADEREXT))
RUNTIME_SRC_CH := $(shell find $(SRC_DIR)/runtime/ -name "*".$(SRCEXT).$(HEADEREXT))

## release build

OBJECTS        := $(patsubst %.$(SRCEXT), %-rel.$(OBJEXT), $(wildcard *.$(SRCEXT)))

rel: mkdirp $(OBJECTS) cpobj

ast.$(OBJEXT): ast.$(SRCEXT) $(AST_SRC_CH) $(HEADERS)
	$(CC) $(CDBGFLAGS) $(INCLUDE) -c -o ast.$(OBJEXT) ast.$(SRCEXT)

lexer-rel.$(OBJEXT): lexer.$(SRCEXT) $(LEXER_SRC_CH) $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o lexer-rel.$(OBJEXT) lexer.$(SRCEXT)

parser-rel.$(OBJEXT): parser.$(SRCEXT) $(PARSER_SRC_CH) $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o parser-rel.$(OBJEXT) parser.$(SRCEXT)

runtime.$(OBJEXT): runtime.$(SRCEXT) $(RUNTIME_SRC_CH) $(HEADERS)
	$(CC) $(CDBGFLAGS) $(INCLUDE) -c -o runtime.$(OBJEXT) runtime.$(SRCEXT)

%-rel.$(OBJEXT): %.$(SRCEXT) $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

## build subdirs
# $(SUB_DIRS): FORCE
# @$(MAKE) -C $@

## debug build

DBG_OBJECTS    := $(patsubst %.$(SRCEXT), %-dbg.$(OBJEXT), $(wildcard *.$(SRCEXT)))

dbg: mkdirp $(DBG_OBJECTS) cpobj

ast-dbg.$(OBJEXT): ast.$(SRCEXT) $(AST_SRC_CH) $(HEADERS)
	$(CC) $(CDBGFLAGS) $(INCLUDE) -c -o ast-dbg.$(OBJEXT) ast.$(SRCEXT)

lexer-dbg.$(OBJEXT): lexer.$(SRCEXT) $(LEXER_SRC_CH) $(HEADERS)
	$(CC) $(CDBGFLAGS) $(INCLUDE) -c -o lexer-dbg.$(OBJEXT) lexer.$(SRCEXT)

parser-dbg.$(OBJEXT): parser.$(SRCEXT) $(PARSER_SRC_CH) $(HEADERS)
	$(CC) $(CDBGFLAGS) $(INCLUDE) -c -o parser-dbg.$(OBJEXT) parser.$(SRCEXT)

runtime-dbg.$(OBJEXT): runtime.$(SRCEXT) $(RUNTIME_SRC_CH) $(HEADERS)
	$(CC) $(CDBGFLAGS) $(INCLUDE) -c -o runtime-dbg.$(OBJEXT) runtime.$(SRCEXT)

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

## FORCE:
