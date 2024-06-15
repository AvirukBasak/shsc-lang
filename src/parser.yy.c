/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser.y"


#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast/api.h"
#include "errcodes.h"
#include "globals.h"
#include "io.h"
#include "lexer.h"
#include "parser.h"

FILE *yyin = NULL;


#line 90 "src/parser.yy.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.yy.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "<eof>"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOKEN_BANG = 3,                 /* "!"  */
  YYSYMBOL_TOKEN_LOGICAL_UNEQUAL = 4,      /* "!="  */
  YYSYMBOL_TOKEN_LOGICAL_UNIDENTICAL = 5,  /* "!=="  */
  YYSYMBOL_TOKEN_DQUOTE = 6,               /* TOKEN_DQUOTE  */
  YYSYMBOL_7_ = 7,                         /* '"'  */
  YYSYMBOL_TOKEN_DOLLAR = 8,               /* "$"  */
  YYSYMBOL_TOKEN_PERCENT = 9,              /* "%"  */
  YYSYMBOL_TOKEN_MODULO_ASSIGN = 10,       /* "%="  */
  YYSYMBOL_TOKEN_AMPERSAND = 11,           /* "&"  */
  YYSYMBOL_TOKEN_LOGICAL_AND = 12,         /* "&&"  */
  YYSYMBOL_TOKEN_LOGICAL_AND_ASSIGN = 13,  /* "&&="  */
  YYSYMBOL_TOKEN_BITWISE_AND_ASSIGN = 14,  /* "&="  */
  YYSYMBOL_TOKEN_SQUOTE = 15,              /* "'"  */
  YYSYMBOL_TOKEN_LBRACE_PAREN = 16,        /* "("  */
  YYSYMBOL_TOKEN_RBRACE_PAREN = 17,        /* ")"  */
  YYSYMBOL_TOKEN_ASTERIX = 18,             /* "*"  */
  YYSYMBOL_TOKEN_EXPONENT = 19,            /* "**"  */
  YYSYMBOL_TOKEN_EXPONENT_ASSIGN = 20,     /* "**="  */
  YYSYMBOL_TOKEN_MULTIPLY_ASSIGN = 21,     /* "*="  */
  YYSYMBOL_TOKEN_PLUS = 22,                /* "+"  */
  YYSYMBOL_TOKEN_INCREMENT = 23,           /* "++"  */
  YYSYMBOL_TOKEN_ADD_ASSIGN = 24,          /* "+="  */
  YYSYMBOL_TOKEN_COMMA = 25,               /* ","  */
  YYSYMBOL_TOKEN_MINUS = 26,               /* "-"  */
  YYSYMBOL_TOKEN_DECREMENT = 27,           /* "--"  */
  YYSYMBOL_TOKEN_SUBSTRACT_ASSIGN = 28,    /* "-="  */
  YYSYMBOL_TOKEN_SARROW = 29,              /* "->"  */
  YYSYMBOL_TOKEN_DOT = 30,                 /* "."  */
  YYSYMBOL_TOKEN_ELIPSIS = 31,             /* "..."  */
  YYSYMBOL_TOKEN_FSLASH = 32,              /* "/"  */
  YYSYMBOL_TOKEN_FLOOR_DIVIDE = 33,        /* "//"  */
  YYSYMBOL_TOKEN_FLOOR_DIVIDE_ASSIGN = 34, /* "//="  */
  YYSYMBOL_TOKEN_DIVIDE_ASSIGN = 35,       /* "/="  */
  YYSYMBOL_TOKEN_COLON = 36,               /* ":"  */
  YYSYMBOL_TOKEN_DCOLON = 37,              /* "::"  */
  YYSYMBOL_TOKEN_SEMICOLON = 38,           /* ";"  */
  YYSYMBOL_TOKEN_LBRACE_ANGULAR = 39,      /* "<"  */
  YYSYMBOL_TOKEN_BITWISE_LSHIFT = 40,      /* "<<"  */
  YYSYMBOL_TOKEN_BITWISE_LSHIFT_ASSIGN = 41, /* "<<="  */
  YYSYMBOL_TOKEN_LOGICAL_LESSER_EQUAL = 42, /* "<="  */
  YYSYMBOL_TOKEN_ASSIGN = 43,              /* "="  */
  YYSYMBOL_TOKEN_LOGICAL_EQUAL = 44,       /* "=="  */
  YYSYMBOL_TOKEN_LOGICAL_IDENTICAL = 45,   /* "==="  */
  YYSYMBOL_TOKEN_DARROW = 46,              /* "=>"  */
  YYSYMBOL_TOKEN_RBRACE_ANGULAR = 47,      /* ">"  */
  YYSYMBOL_TOKEN_LOGICAL_GREATER_EQUAL = 48, /* ">="  */
  YYSYMBOL_TOKEN_BITWISE_RSHIFT = 49,      /* ">>"  */
  YYSYMBOL_TOKEN_BITWISE_RSHIFT_ASSIGN = 50, /* ">>="  */
  YYSYMBOL_TOKEN_ARITH_RSHIFT = 51,        /* ">>>"  */
  YYSYMBOL_TOKEN_ARITH_RSHIFT_ASSIGN = 52, /* ">>>="  */
  YYSYMBOL_TOKEN_QUESTION = 53,            /* "?"  */
  YYSYMBOL_TOKEN_AT = 54,                  /* "@"  */
  YYSYMBOL_TOKEN_LBRACE_SQUARE = 55,       /* "["  */
  YYSYMBOL_TOKEN_BSLASH = 56,              /* "\\"  */
  YYSYMBOL_TOKEN_RBRACE_SQUARE = 57,       /* "]"  */
  YYSYMBOL_TOKEN_CARET = 58,               /* "^"  */
  YYSYMBOL_TOKEN_BITWISE_XOR_ASSIGN = 59,  /* "^="  */
  YYSYMBOL_TOKEN_BACKTICK = 60,            /* "`"  */
  YYSYMBOL_TOKEN_LBRACE_CURLY = 61,        /* "{"  */
  YYSYMBOL_TOKEN_PIPE = 62,                /* "|"  */
  YYSYMBOL_TOKEN_BITWISE_OR_ASSIGN = 63,   /* "|="  */
  YYSYMBOL_TOKEN_PIPEOUT = 64,             /* "|>"  */
  YYSYMBOL_TOKEN_LOGICAL_OR = 65,          /* "||"  */
  YYSYMBOL_TOKEN_LOGICAL_OR_ASSIGN = 66,   /* "||="  */
  YYSYMBOL_TOKEN_RBRACE_CURLY = 67,        /* "}"  */
  YYSYMBOL_TOKEN_TILDE = 68,               /* "~"  */
  YYSYMBOL_TOKOP_NOP = 69,                 /* TOKOP_NOP  */
  YYSYMBOL_TOKOP_FNCALL = 70,              /* TOKOP_FNCALL  */
  YYSYMBOL_TOKOP_INDEXING = 71,            /* TOKOP_INDEXING  */
  YYSYMBOL_TOKOP_TERNARY_COND = 72,        /* TOKOP_TERNARY_COND  */
  YYSYMBOL_TOKOP_FNARGS_INDEXING = 73,     /* TOKOP_FNARGS_INDEXING  */
  YYSYMBOL_TOKOP_ASSIGN_CONST = 74,        /* TOKOP_ASSIGN_CONST  */
  YYSYMBOL_TOKOP_ASSIGN_WEAK = 75,         /* TOKOP_ASSIGN_WEAK  */
  YYSYMBOL_TOKOP_ASSIGN_CONST_WEAK = 76,   /* TOKOP_ASSIGN_CONST_WEAK  */
  YYSYMBOL_TOKEN_NEWLINE = 77,             /* "\n"  */
  YYSYMBOL_TOKEN_KWD_MODULE = 78,          /* "module"  */
  YYSYMBOL_TOKEN_KWD_PROC = 79,            /* "proc"  */
  YYSYMBOL_TOKEN_KWD_START = 80,           /* "start"  */
  YYSYMBOL_TOKEN_KWD_END = 81,             /* "end"  */
  YYSYMBOL_TOKEN_KWD_BLOCK = 82,           /* "block"  */
  YYSYMBOL_TOKEN_KWD_IF = 83,              /* "if"  */
  YYSYMBOL_TOKEN_KWD_THEN = 84,            /* "then"  */
  YYSYMBOL_TOKEN_KWD_ELIF = 85,            /* "elif"  */
  YYSYMBOL_TOKEN_KWD_ELSE = 86,            /* "else"  */
  YYSYMBOL_TOKEN_KWD_WHILE = 87,           /* "while"  */
  YYSYMBOL_TOKEN_KWD_BREAK = 88,           /* "break"  */
  YYSYMBOL_TOKEN_KWD_CONTINUE = 89,        /* "continue"  */
  YYSYMBOL_TOKEN_KWD_FOR = 90,             /* "for"  */
  YYSYMBOL_TOKEN_KWD_FROM = 91,            /* "from"  */
  YYSYMBOL_TOKEN_KWD_TO = 92,              /* "to"  */
  YYSYMBOL_TOKEN_KWD_BY = 93,              /* "by"  */
  YYSYMBOL_TOKEN_KWD_IN = 94,              /* "in"  */
  YYSYMBOL_TOKEN_KWD_DO = 95,              /* "do"  */
  YYSYMBOL_TOKEN_KWD_VAR = 96,             /* "var"  */
  YYSYMBOL_TOKEN_KWD_CONST = 97,           /* "const"  */
  YYSYMBOL_TOKEN_KWD_PASS = 98,            /* "pass"  */
  YYSYMBOL_TOKEN_KWD_RETURN = 99,          /* "return"  */
  YYSYMBOL_TOKEN_KWD_WEAK = 100,           /* "weak"  */
  YYSYMBOL_TOKEN_INVALID = 101,            /* "<invalid>"  */
  YYSYMBOL_TOKEN_BOOL_LITERAL = 102,       /* "<boollit>"  */
  YYSYMBOL_TOKEN_CHAR_LITERAL = 103,       /* "<charlit>"  */
  YYSYMBOL_TOKEN_BINFLOAT_LITERAL = 104,   /* "<binfloattlit>"  */
  YYSYMBOL_TOKEN_OCTFLOAT_LITERAL = 105,   /* "<octfloattlit>"  */
  YYSYMBOL_TOKEN_DECFLOAT_LITERAL = 106,   /* "<decfloattlit>"  */
  YYSYMBOL_TOKEN_HEXFLOAT_LITERAL = 107,   /* "<hexfloattlit>"  */
  YYSYMBOL_TOKEN_BININT_LITERAL = 108,     /* "<binintlit>"  */
  YYSYMBOL_TOKEN_OCTINT_LITERAL = 109,     /* "<octintlit>"  */
  YYSYMBOL_TOKEN_DECINT_LITERAL = 110,     /* "<decintlit>"  */
  YYSYMBOL_TOKEN_HEXINT_LITERAL = 111,     /* "<hexintlit>"  */
  YYSYMBOL_TOKEN_STR_LITERAL = 112,        /* "<strlit>"  */
  YYSYMBOL_TOKEN_INTERP_STR_LITERAL = 113, /* "<interpstrlit>"  */
  YYSYMBOL_TOKEN_IDENTIFIER = 114,         /* "<identifier>"  */
  YYSYMBOL_YYACCEPT = 115,                 /* $accept  */
  YYSYMBOL_nws = 116,                      /* nws  */
  YYSYMBOL_nwp = 117,                      /* nwp  */
  YYSYMBOL_trm = 118,                      /* trm  */
  YYSYMBOL_module = 119,                   /* module  */
  YYSYMBOL_120_1 = 120,                    /* $@1  */
  YYSYMBOL_121_2 = 121,                    /* $@2  */
  YYSYMBOL_program = 122,                  /* program  */
  YYSYMBOL_procedure = 123,                /* procedure  */
  YYSYMBOL_fnargs_list = 124,              /* fnargs_list  */
  YYSYMBOL_statements = 125,               /* statements  */
  YYSYMBOL_statement = 126,                /* statement  */
  YYSYMBOL_assignment = 127,               /* assignment  */
  YYSYMBOL_compound_statement = 128,       /* compound_statement  */
  YYSYMBOL_if_block = 129,                 /* if_block  */
  YYSYMBOL_else_block = 130,               /* else_block  */
  YYSYMBOL_while_block = 131,              /* while_block  */
  YYSYMBOL_for_block = 132,                /* for_block  */
  YYSYMBOL_block = 133,                    /* block  */
  YYSYMBOL_condition = 134,                /* condition  */
  YYSYMBOL_expression = 135,               /* expression  */
  YYSYMBOL_assignment_expression = 136,    /* assignment_expression  */
  YYSYMBOL_conditional_expression = 137,   /* conditional_expression  */
  YYSYMBOL_logical_or_expression = 138,    /* logical_or_expression  */
  YYSYMBOL_logical_and_expression = 139,   /* logical_and_expression  */
  YYSYMBOL_bitwise_or_expression = 140,    /* bitwise_or_expression  */
  YYSYMBOL_bitwise_xor_expression = 141,   /* bitwise_xor_expression  */
  YYSYMBOL_bitwise_and_expression = 142,   /* bitwise_and_expression  */
  YYSYMBOL_equality_expression = 143,      /* equality_expression  */
  YYSYMBOL_relational_expression = 144,    /* relational_expression  */
  YYSYMBOL_shift_expression = 145,         /* shift_expression  */
  YYSYMBOL_additive_expression = 146,      /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 147, /* multiplicative_expression  */
  YYSYMBOL_unary_expression = 148,         /* unary_expression  */
  YYSYMBOL_postfix_expression = 149,       /* postfix_expression  */
  YYSYMBOL_primary_expression = 150,       /* primary_expression  */
  YYSYMBOL_comma_list = 151,               /* comma_list  */
  YYSYMBOL_assoc_list = 152,               /* assoc_list  */
  YYSYMBOL_literal = 153,                  /* literal  */
  YYSYMBOL_string_literal = 154,           /* string_literal  */
  YYSYMBOL_list_literal = 155,             /* list_literal  */
  YYSYMBOL_map_literal = 156,              /* map_literal  */
  YYSYMBOL_identifier = 157                /* identifier  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1138

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  115
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  164
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  339

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   368


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     7,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   241,   241,   242,   247,   248,   253,   254,   255,   256,
     261,   261,   262,   262,   267,   268,   273,   276,   279,   285,
     286,   287,   291,   292,   296,   297,   298,   299,   300,   301,
     302,   306,   307,   308,   309,   310,   311,   315,   316,   317,
     318,   322,   323,   327,   328,   329,   330,   331,   335,   339,
     340,   341,   342,   346,   350,   354,   358,   359,   360,   361,
     362,   363,   364,   365,   366,   367,   368,   369,   370,   371,
     372,   373,   374,   375,   376,   377,   378,   382,   383,   387,
     388,   392,   393,   397,   398,   402,   403,   407,   408,   412,
     413,   414,   418,   419,   420,   421,   422,   426,   427,   428,
     429,   433,   434,   435,   439,   440,   441,   442,   443,   444,
     448,   449,   450,   451,   452,   453,   454,   458,   459,   460,
     463,   464,   465,   466,   470,   473,   474,   475,   479,   482,
     488,   489,   490,   494,   495,   496,   500,   501,   502,   503,
     507,   511,   515,   529,   543,   560,   561,   562,   563,   564,
     565,   566,   567,   568,   569,   570,   571,   572,   576,   577,
     581,   582,   586,   587,   591
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"<eof>\"", "error", "\"invalid token\"", "\"!\"", "\"!=\"", "\"!==\"",
  "TOKEN_DQUOTE", "'\"'", "\"$\"", "\"%\"", "\"%=\"", "\"&\"", "\"&&\"",
  "\"&&=\"", "\"&=\"", "\"'\"", "\"(\"", "\")\"", "\"*\"", "\"**\"",
  "\"**=\"", "\"*=\"", "\"+\"", "\"++\"", "\"+=\"", "\",\"", "\"-\"",
  "\"--\"", "\"-=\"", "\"->\"", "\".\"", "\"...\"", "\"/\"", "\"//\"",
  "\"//=\"", "\"/=\"", "\":\"", "\"::\"", "\";\"", "\"<\"", "\"<<\"",
  "\"<<=\"", "\"<=\"", "\"=\"", "\"==\"", "\"===\"", "\"=>\"", "\">\"",
  "\">=\"", "\">>\"", "\">>=\"", "\">>>\"", "\">>>=\"", "\"?\"", "\"@\"",
  "\"[\"", "\"\\\\\"", "\"]\"", "\"^\"", "\"^=\"", "\"`\"", "\"{\"",
  "\"|\"", "\"|=\"", "\"|>\"", "\"||\"", "\"||=\"", "\"}\"", "\"~\"",
  "TOKOP_NOP", "TOKOP_FNCALL", "TOKOP_INDEXING", "TOKOP_TERNARY_COND",
  "TOKOP_FNARGS_INDEXING", "TOKOP_ASSIGN_CONST", "TOKOP_ASSIGN_WEAK",
  "TOKOP_ASSIGN_CONST_WEAK", "\"\\n\"", "\"module\"", "\"proc\"",
  "\"start\"", "\"end\"", "\"block\"", "\"if\"", "\"then\"", "\"elif\"",
  "\"else\"", "\"while\"", "\"break\"", "\"continue\"", "\"for\"",
  "\"from\"", "\"to\"", "\"by\"", "\"in\"", "\"do\"", "\"var\"",
  "\"const\"", "\"pass\"", "\"return\"", "\"weak\"", "\"<invalid>\"",
  "\"<boollit>\"", "\"<charlit>\"", "\"<binfloattlit>\"",
  "\"<octfloattlit>\"", "\"<decfloattlit>\"", "\"<hexfloattlit>\"",
  "\"<binintlit>\"", "\"<octintlit>\"", "\"<decintlit>\"",
  "\"<hexintlit>\"", "\"<strlit>\"", "\"<interpstrlit>\"",
  "\"<identifier>\"", "$accept", "nws", "nwp", "trm", "module", "$@1",
  "$@2", "program", "procedure", "fnargs_list", "statements", "statement",
  "assignment", "compound_statement", "if_block", "else_block",
  "while_block", "for_block", "block", "condition", "expression",
  "assignment_expression", "conditional_expression",
  "logical_or_expression", "logical_and_expression",
  "bitwise_or_expression", "bitwise_xor_expression",
  "bitwise_and_expression", "equality_expression", "relational_expression",
  "shift_expression", "additive_expression", "multiplicative_expression",
  "unary_expression", "postfix_expression", "primary_expression",
  "comma_list", "assoc_list", "literal", "string_literal", "list_literal",
  "map_literal", "identifier", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-289)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -65,   -91,    55,  -289,  -289,   -29,  -289,   -10,  -289,  -289,
     -26,   -91,  -289,  -289,  -289,  -289,    16,   -10,   -14,   -13,
     -13,    63,    97,  -289,   321,   321,   -13,  -289,    11,   967,
      -5,   967,   967,   967,   967,   967,    42,    41,   967,  -289,
     -13,   967,   967,   -29,   -29,   -91,   -91,   -29,   449,  -289,
    -289,  -289,  -289,  -289,  -289,  -289,  -289,  -289,  -289,  -289,
    -289,    44,   433,   -29,   -29,  -289,  -289,  -289,  -289,  -289,
    -289,    58,    73,   116,    84,    90,   138,     3,    76,     9,
     125,    88,   135,  1072,  -289,  -289,  -289,  -289,  -289,  -289,
      86,   321,   -55,  -289,  -289,   103,   967,   967,  -289,  -289,
     140,  -289,  -289,  -289,  -289,  -289,   694,  -289,    -2,  -289,
     321,    92,    58,    75,   -26,   -26,   -20,   131,   -26,   -26,
     -29,   -29,  -289,   -26,   -26,   967,   967,   967,   967,   967,
     967,   967,   967,   967,   967,   967,   967,   967,   967,   967,
     967,   967,   967,   967,   967,   967,   967,   967,   967,   967,
     165,   967,   967,  -289,   967,  -289,   967,   -91,   967,   967,
     -91,   -91,   967,   561,   967,   967,   967,   967,   967,   967,
     -29,   102,  -289,   190,   151,  -289,   189,   158,   -91,   149,
     181,   182,   142,   -13,   -13,   -91,   967,   967,   582,   -26,
     -26,   133,   116,    84,    90,   138,     3,    76,    76,     9,
       9,     9,     9,   125,   125,   125,    88,    88,  -289,  -289,
    -289,  -289,    10,  -289,  -289,  -289,  -289,   694,  -289,  -289,
    -289,  -289,  -289,  -289,  -289,  -289,  -289,  -289,   711,   823,
    -289,  -289,  -289,   164,  -289,  -289,  -289,   -26,   -29,  -289,
    -289,  -289,    11,  -289,   167,  -289,   967,   967,  -289,   321,
     321,   134,   141,   132,   839,   951,  -289,   967,   213,   967,
    -289,   967,  -289,  -289,   -26,   694,   196,   209,   211,    46,
     156,   967,   967,   -13,   967,  -289,   967,  -289,  -289,  -289,
    -289,  -289,  -289,   967,  -289,    11,  -289,    11,  -289,   967,
       7,  -289,  -289,   143,   -62,   321,  -289,  -289,   214,    -2,
      -2,   157,   967,   321,   -13,   967,   -13,   159,  -289,    11,
    -289,  -289,   -13,   161,   169,   321,   153,   321,  -289,    -2,
     321,   -13,  -289,   170,   -13,   171,  -289,    80,   321,  -289,
     321,  -289,  -289,  -289,    83,   172,  -289,  -289,  -289
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      10,     0,     0,    14,   164,     0,     1,    11,     7,     9,
      12,     0,    15,     6,     8,    14,     0,    13,     0,     0,
       0,     0,     2,     4,    22,    22,     0,     2,    19,     0,
       0,     0,     0,     0,     0,     0,     2,     2,     0,     5,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   158,
     159,     0,    22,     0,     0,    37,    38,    39,    40,    36,
      55,    56,    77,    79,    81,    83,    85,    87,    89,    92,
      97,   101,   104,   110,   117,   130,   155,   156,   157,   131,
       0,    22,    20,     3,   113,   110,     0,     0,   123,   124,
       0,   111,   115,   112,   116,   160,     0,   162,     0,   114,
      22,     0,    54,     0,    25,    26,     0,     0,    24,    28,
       0,     0,    23,    29,    30,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     0,     0,   125,     0,   126,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    21,     0,     0,   132,     2,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    27,
      16,     0,    80,    82,    84,    86,    88,    91,    90,    93,
      95,    94,    96,    99,   100,    98,   102,   103,   107,   105,
     106,   109,   108,    74,    63,    66,   118,     0,    75,    72,
      70,    71,   127,    76,    73,   129,   128,    68,     0,     0,
      57,    69,    67,     0,    65,    64,    62,    17,     0,   122,
     121,     2,   133,   161,     0,   163,     0,     0,    53,    22,
      22,     0,     0,     0,     0,     0,    31,     0,     0,     0,
      58,     0,    59,   120,    18,   134,     0,     2,     2,     0,
       0,     0,     0,     0,     0,    32,     0,    33,    78,   119,
      60,    61,   135,     0,     2,   136,     2,   139,    41,     0,
       0,    42,    48,     0,     0,    22,    34,    35,     2,   137,
     140,     0,     0,    22,     0,     0,     0,     0,     2,   142,
     138,   141,     0,     0,     0,    22,     0,    22,    51,   143,
      22,     0,    43,     0,     0,     0,   144,     0,    22,    52,
      22,    49,    46,    47,     0,     0,    44,    45,    50
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -289,   -21,   -12,    -7,  -289,  -289,  -289,   239,  -289,   163,
     -24,  -289,  -289,  -289,  -289,  -288,  -289,  -289,  -289,   -40,
      56,   -86,   -22,  -289,   130,   137,   129,   139,   128,   -15,
      45,    74,     4,    -8,    60,  -289,  -213,  -265,  -289,   -90,
    -289,  -289,    -1
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    28,    24,    10,     2,     3,    15,     7,    12,    21,
      61,    62,    63,    64,    65,   291,    66,    67,    68,   111,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,   177,   179,    85,    86,
      87,    88,    89
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       5,    90,   113,    20,   258,   185,    92,   131,    25,     8,
      16,    96,    13,     1,    91,   106,   108,    22,   180,   112,
     112,    94,    93,     4,   101,   102,   103,   104,   110,    99,
     109,   305,    18,   306,   310,   311,   114,   115,   122,   333,
     118,   119,   144,   145,   116,   117,   337,   132,     9,   137,
      97,    14,   282,   178,   326,     6,   123,   124,   138,     4,
     139,   213,   214,   215,    23,   218,   219,   171,   220,    11,
     221,   186,   223,   224,   187,    93,   227,   230,   231,   232,
      26,   234,   235,   236,    23,   191,   182,   100,    93,    95,
     302,    22,    95,    95,    95,    95,    19,   142,    95,   105,
       4,    95,    95,   112,   120,    98,   143,   181,   107,     4,
      59,    60,     4,   189,   190,   133,   197,   198,   134,   150,
     144,   145,    27,   135,   136,   121,   153,   288,   127,   217,
     155,   289,   290,   157,   208,   209,   210,   211,   126,   160,
     161,   125,   260,   262,   206,   207,   128,   140,   129,   130,
     212,   141,   173,   174,   146,   242,   222,   175,   166,   225,
     226,   332,   176,   237,   336,   289,   290,   170,   289,   290,
     184,   249,   250,   280,   188,   281,   183,   244,   199,   200,
     201,   202,   216,   238,   251,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,   239,   240,   180,
     180,   203,   204,   205,   241,   243,   245,   246,   247,   257,
     265,   263,   233,   248,   266,   269,   270,   273,   271,   180,
     279,   264,   283,   272,   284,   278,   286,   292,   304,   308,
     318,   312,   252,   253,   256,   321,   285,   287,   324,   301,
     322,   329,   331,   338,    17,   172,   192,   194,   196,     0,
       0,   295,   313,   299,   193,   300,     0,   112,   195,     0,
       0,   307,     0,   176,     0,     0,     0,   309,   303,   314,
     112,     0,     0,     0,     0,     0,     0,   319,     0,     0,
       0,   323,   315,   325,   317,     0,   327,     0,   181,   181,
     320,     0,   267,   268,   334,     0,   335,     0,     0,   328,
     275,   277,   330,     0,     0,     0,     0,    95,   181,     0,
       0,   176,     0,     0,    29,     0,     0,   293,   294,    30,
     296,     0,   297,     0,     0,     0,     0,    31,     0,   298,
       0,     0,     0,    32,    33,     0,     0,    34,    35,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   316,    95,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    36,     0,     0,     0,
       0,     0,    37,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,     0,     0,    39,     0,
       0,     0,     0,    40,    41,     0,     0,     0,    42,    43,
      44,    45,     0,     0,     0,     0,     0,    46,     0,    47,
      48,     0,     0,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,     4,    29,     0,     0,     0,
       0,    30,     0,     0,     0,     0,     0,     0,     0,    31,
       0,     0,    29,     0,     0,    32,    33,    30,     0,    34,
      35,     0,     0,     0,     0,    31,     0,     0,     0,     0,
       0,    32,    33,     0,     0,    34,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     8,    36,     0,
       0,     0,     0,     0,    37,     0,     0,     0,     0,     0,
       0,    38,     0,     0,    36,     0,     0,     0,     0,     0,
      37,     0,     0,     0,     0,    40,    41,    38,     0,     0,
      42,    43,    44,    45,     0,     0,     9,     0,     0,    46,
       0,    47,    48,     0,     0,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,     4,     0,     0,
       0,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,     4,    29,     0,     0,     0,     0,    30,
       0,     0,     0,     0,     0,     0,     0,    31,     0,     0,
       0,     0,     0,    32,    33,    29,     0,    34,    35,     0,
      30,     0,     0,     0,     0,     0,     0,     0,    31,     0,
       0,     0,     0,     0,    32,    33,     0,     0,    34,    35,
       0,     0,     0,     0,     0,     0,    36,     0,     0,     0,
       0,     0,    37,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,     0,    36,     0,     0,
       0,     0,     0,    37,     0,     0,     0,     0,     0,     0,
      38,     0,     0,     0,     0,     0,     0,     0,   228,     0,
       0,   229,     0,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,     4,     0,     0,     0,   254,
       0,     0,   255,     0,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,     4,    29,     0,     0,
       0,     0,    30,     0,     0,     0,     0,     0,     0,     0,
      31,     0,     0,     0,    29,     0,    32,    33,     0,    30,
      34,    35,     0,     0,     0,     0,     0,    31,     0,     0,
       0,     0,     0,    32,    33,     0,     0,    34,    35,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    36,
       0,     0,     0,     0,     0,    37,     0,     0,     0,     0,
       0,     0,    38,     0,     0,     0,    36,     0,     0,     0,
       0,    93,    37,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,     4,     0,
       0,   259,     0,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,     4,    29,     0,     0,     0,
       0,    30,     0,     0,     0,     0,     0,     0,     0,    31,
       0,     0,    29,     0,     0,    32,    33,    30,     0,    34,
      35,     0,     0,     0,     0,    31,     0,     0,     0,     0,
       0,    32,    33,     0,     0,    34,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    36,     0,
       0,     0,     0,     0,    37,     0,     0,     0,     0,     0,
       0,    38,     0,     0,    36,     0,     0,     0,     0,     0,
      37,     0,     0,     0,     0,     0,     0,    38,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     261,     0,     0,     0,     0,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,     4,     0,   274,
       0,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,     4,    29,     0,     0,     0,     0,    30,
       0,     0,     0,     0,     0,     0,     0,    31,     0,     0,
      29,     0,     0,    32,    33,    30,     0,    34,    35,     0,
       0,     0,     0,    31,     0,     0,     0,     0,     0,    32,
      33,     0,     0,    34,    35,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    36,     0,     0,     0,
       0,     0,    37,     0,     0,     0,     0,     0,     0,    38,
       0,     0,    36,     0,     0,     0,     0,     0,    37,     0,
       0,     0,     0,     0,     0,    38,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   276,     0,
       0,     0,     0,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,     4,     0,     0,     0,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,     4,   147,     0,     0,   148,   149,     0,   150,     0,
       0,     0,   151,   152,     0,   153,   154,     0,     0,   155,
     156,     0,   157,     0,     0,     0,   158,   159,   160,   161,
       0,     0,     0,   162,     0,   163,     0,     0,     0,     0,
       0,     0,   164,     0,   165,     0,     0,   166,     0,     0,
       0,   167,     0,     0,     0,   168,     0,     0,   169
};

static const yytype_int16 yycheck[] =
{
       1,    25,    42,    17,   217,    25,    27,     4,    20,    38,
      11,    16,    38,    78,    26,    36,    37,    18,   108,    41,
      42,    29,    77,   114,    32,    33,    34,    35,    40,    30,
      38,    93,    16,    95,   299,   300,    43,    44,    62,   327,
      47,    48,    32,    33,    45,    46,   334,    44,    77,    40,
      55,    77,   265,    55,   319,     0,    63,    64,    49,   114,
      51,   147,   148,   149,    77,   151,   152,    91,   154,    79,
     156,    91,   158,   159,    94,    77,   162,   163,   164,   165,
      17,   167,   168,   169,    77,   125,   110,    31,    77,    29,
      83,    92,    32,    33,    34,    35,    80,     9,    38,    57,
     114,    41,    42,   125,    48,   110,    18,   108,    67,   114,
     112,   113,   114,   120,   121,    39,   131,   132,    42,    16,
      32,    33,    25,    47,    48,    81,    23,    81,    12,   150,
      27,    85,    86,    30,   142,   143,   144,   145,    65,    36,
      37,    83,   228,   229,   140,   141,    62,    22,    58,    11,
     146,    26,    96,    97,    19,   176,   157,    17,    55,   160,
     161,    81,   106,   170,    81,    85,    86,    81,    85,    86,
      95,   183,   184,   259,    43,   261,    84,   178,   133,   134,
     135,   136,    17,    81,   185,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,    17,    57,   299,
     300,   137,   138,   139,    25,    57,    67,    36,    36,    86,
     241,    57,   166,    81,    57,   249,   250,    95,    94,   319,
      17,   238,    36,    92,    25,   257,    25,    81,    95,    25,
      81,    84,   186,   187,   188,    84,   267,   268,    95,   289,
      81,    81,    81,    81,    15,    92,   126,   128,   130,    -1,
      -1,   273,   302,   284,   127,   286,    -1,   289,   129,    -1,
      -1,   295,    -1,   217,    -1,    -1,    -1,   298,   290,   303,
     302,    -1,    -1,    -1,    -1,    -1,    -1,   308,    -1,    -1,
      -1,   315,   304,   317,   306,    -1,   320,    -1,   299,   300,
     312,    -1,   246,   247,   328,    -1,   330,    -1,    -1,   321,
     254,   255,   324,    -1,    -1,    -1,    -1,   257,   319,    -1,
      -1,   265,    -1,    -1,     3,    -1,    -1,   271,   272,     8,
     274,    -1,   276,    -1,    -1,    -1,    -1,    16,    -1,   283,
      -1,    -1,    -1,    22,    23,    -1,    -1,    26,    27,   289,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   305,   302,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,
      -1,    -1,    -1,    82,    83,    -1,    -1,    -1,    87,    88,
      89,    90,    -1,    -1,    -1,    -1,    -1,    96,    -1,    98,
      99,    -1,    -1,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,     3,    -1,    -1,    -1,
      -1,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,
      -1,    -1,     3,    -1,    -1,    22,    23,     8,    -1,    26,
      27,    -1,    -1,    -1,    -1,    16,    -1,    -1,    -1,    -1,
      -1,    22,    23,    -1,    -1,    26,    27,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    55,    -1,
      -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,
      61,    -1,    -1,    -1,    -1,    82,    83,    68,    -1,    -1,
      87,    88,    89,    90,    -1,    -1,    77,    -1,    -1,    96,
      -1,    98,    99,    -1,    -1,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,    -1,    -1,
      -1,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,     3,    -1,    -1,    -1,    -1,     8,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,    -1,    -1,
      -1,    -1,    -1,    22,    23,     3,    -1,    26,    27,    -1,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,    -1,
      -1,    -1,    -1,    -1,    22,    23,    -1,    -1,    26,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    97,    -1,
      -1,   100,    -1,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,    -1,    -1,    -1,    97,
      -1,    -1,   100,    -1,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,     3,    -1,    -1,
      -1,    -1,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      16,    -1,    -1,    -1,     3,    -1,    22,    23,    -1,     8,
      26,    27,    -1,    -1,    -1,    -1,    -1,    16,    -1,    -1,
      -1,    -1,    -1,    22,    23,    -1,    -1,    26,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    77,    61,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,    -1,
      -1,   100,    -1,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,     3,    -1,    -1,    -1,
      -1,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,
      -1,    -1,     3,    -1,    -1,    22,    23,     8,    -1,    26,
      27,    -1,    -1,    -1,    -1,    16,    -1,    -1,    -1,    -1,
      -1,    22,    23,    -1,    -1,    26,    27,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,
      61,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      97,    -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,    -1,   100,
      -1,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,     3,    -1,    -1,    -1,    -1,     8,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,    -1,    -1,
       3,    -1,    -1,    22,    23,     8,    -1,    26,    27,    -1,
      -1,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,    22,
      23,    -1,    -1,    26,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    97,    -1,
      -1,    -1,    -1,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,    -1,    -1,    -1,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,    10,    -1,    -1,    13,    14,    -1,    16,    -1,
      -1,    -1,    20,    21,    -1,    23,    24,    -1,    -1,    27,
      28,    -1,    30,    -1,    -1,    -1,    34,    35,    36,    37,
      -1,    -1,    -1,    41,    -1,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    52,    -1,    -1,    55,    -1,    -1,
      -1,    59,    -1,    -1,    -1,    63,    -1,    -1,    66
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    78,   119,   120,   114,   157,     0,   122,    38,    77,
     118,    79,   123,    38,    77,   121,   157,   122,    16,    80,
      17,   124,   157,    77,   117,   117,    17,    25,   116,     3,
       8,    16,    22,    23,    26,    27,    55,    61,    68,    77,
      82,    83,    87,    88,    89,    90,    96,    98,    99,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   125,   126,   127,   128,   129,   131,   132,   133,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   153,   154,   155,   156,   157,
     125,   117,   116,    77,   148,   149,    16,    55,   110,   157,
     135,   148,   148,   148,   148,    57,   116,    67,   116,   148,
     117,   134,   137,   134,   118,   118,   157,   157,   118,   118,
     135,    81,   125,   118,   118,    83,    65,    12,    62,    58,
      11,     4,    44,    39,    42,    47,    48,    40,    49,    51,
      22,    26,     9,    18,    32,    33,    19,    10,    13,    14,
      16,    20,    21,    23,    24,    27,    28,    30,    34,    35,
      36,    37,    41,    43,    50,    52,    55,    59,    63,    66,
      81,   125,   124,   135,   135,    17,   135,   151,    55,   152,
     154,   157,   125,    84,    95,    25,    91,    94,    43,   118,
     118,   134,   139,   140,   141,   142,   143,   144,   144,   145,
     145,   145,   145,   146,   146,   146,   147,   147,   148,   148,
     148,   148,   147,   136,   136,   136,    17,   116,   136,   136,
     136,   136,   157,   136,   136,   157,   157,   136,    97,   100,
     136,   136,   136,   135,   136,   136,   136,   118,    81,    17,
      57,    25,   116,    57,   157,    67,    36,    36,    81,   117,
     117,   157,   135,   135,    97,   100,   135,    86,   151,   100,
     136,    97,   136,    57,   118,   116,    57,   135,   135,   125,
     125,    94,    92,    95,   100,   135,    97,   135,   137,    17,
     136,   136,   151,    36,    25,   116,    25,   116,    81,    85,
      86,   130,    81,   135,   135,   117,   135,   135,   135,   116,
     116,   134,    83,   117,    95,    93,    95,   125,    25,   116,
     152,   152,    84,   134,   125,   117,   135,   117,    81,   116,
     117,    84,    81,   125,    95,   125,   152,   125,   117,    81,
     117,    81,    81,   130,   125,   125,    81,   130,    81
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   115,   116,   116,   117,   117,   118,   118,   118,   118,
     120,   119,   121,   119,   122,   122,   123,   123,   123,   124,
     124,   124,   125,   125,   126,   126,   126,   126,   126,   126,
     126,   127,   127,   127,   127,   127,   127,   128,   128,   128,
     128,   129,   129,   130,   130,   130,   130,   130,   131,   132,
     132,   132,   132,   133,   134,   135,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   137,   137,   138,
     138,   139,   139,   140,   140,   141,   141,   142,   142,   143,
     143,   143,   144,   144,   144,   144,   144,   145,   145,   145,
     145,   146,   146,   146,   147,   147,   147,   147,   147,   147,
     148,   148,   148,   148,   148,   148,   148,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     150,   150,   150,   151,   151,   151,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   154,   154,
     155,   155,   156,   156,   157
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     2,     2,     1,     2,     1,
       0,     2,     0,     5,     0,     2,     7,     8,     9,     2,
       3,     4,     0,     2,     2,     2,     2,     3,     2,     2,
       2,     4,     5,     5,     6,     6,     1,     1,     1,     1,
       1,     6,     6,     4,     7,     7,     6,     6,     6,    10,
      12,     8,    10,     4,     1,     1,     1,     3,     4,     4,
       5,     5,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     5,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     3,
       1,     2,     2,     2,     2,     2,     2,     1,     3,     5,
       4,     4,     4,     2,     2,     2,     2,     3,     3,     3,
       1,     1,     3,     2,     3,     4,     4,     5,     6,     4,
       5,     6,     6,     7,     8,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     4,     2,     4,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= TOKEN_EOF)
    {
      yychar = TOKEN_EOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* nws: %empty  */
#line 241 "src/parser.y"
               { (yyval.line_count) = 0; }
#line 1643 "src/parser.yy.c"
    break;

  case 3: /* nws: nws "\n"  */
#line 242 "src/parser.y"
               { (yyval.line_count) = (yyvsp[-1].line_count) + 1; }
#line 1649 "src/parser.yy.c"
    break;

  case 4: /* nwp: "\n"  */
#line 247 "src/parser.y"
               { (yyval.line_count) = 1; }
#line 1655 "src/parser.yy.c"
    break;

  case 5: /* nwp: nwp "\n"  */
#line 248 "src/parser.y"
               { (yyval.line_count) = (yyvsp[-1].line_count) + 1; }
#line 1661 "src/parser.yy.c"
    break;

  case 6: /* trm: trm ";"  */
#line 253 "src/parser.y"
               { (yyval.line_count) = (yyvsp[-1].line_count); }
#line 1667 "src/parser.yy.c"
    break;

  case 7: /* trm: ";"  */
#line 254 "src/parser.y"
               { (yyval.line_count) = 0; }
#line 1673 "src/parser.yy.c"
    break;

  case 8: /* trm: trm "\n"  */
#line 255 "src/parser.y"
               { (yyval.line_count) = (yyvsp[-1].line_count) + 1; }
#line 1679 "src/parser.yy.c"
    break;

  case 9: /* trm: "\n"  */
#line 256 "src/parser.y"
               { (yyval.line_count) = 1; }
#line 1685 "src/parser.yy.c"
    break;

  case 10: /* $@1: %empty  */
#line 261 "src/parser.y"
    { ast_ModuleStack_push(ast_Identifier(strdup("main"))); }
#line 1691 "src/parser.yy.c"
    break;

  case 11: /* module: $@1 program  */
#line 261 "src/parser.y"
                                                                      { ast_ModuleStack_pop(); }
#line 1697 "src/parser.yy.c"
    break;

  case 12: /* $@2: %empty  */
#line 262 "src/parser.y"
                              { ast_ModuleStack_push((yyvsp[-1].astnode_identifier)); }
#line 1703 "src/parser.yy.c"
    break;

  case 13: /* module: "module" identifier trm $@2 program  */
#line 262 "src/parser.y"
                                                                    { ast_ModuleStack_pop(); }
#line 1709 "src/parser.yy.c"
    break;

  case 16: /* procedure: "proc" identifier "start" nwp statements "end" trm  */
#line 273 "src/parser.y"
                                                                                                   { ast_util_ModuleAndProcTable_add(ast_ModuleStack_top(), (yyvsp[-5].astnode_identifier), NULL, (yyvsp[-2].astnode_statements));
                                                                                                       ast_Identifier_destroy(&(yyvsp[-5].astnode_identifier));
                                                                                                   }
#line 1717 "src/parser.yy.c"
    break;

  case 17: /* procedure: "proc" identifier "(" ")" nwp statements "end" trm  */
#line 276 "src/parser.y"
                                                                                                   { ast_util_ModuleAndProcTable_add(ast_ModuleStack_top(), (yyvsp[-6].astnode_identifier), NULL, (yyvsp[-2].astnode_statements));
                                                                                                       ast_Identifier_destroy(&(yyvsp[-6].astnode_identifier));
                                                                                                   }
#line 1725 "src/parser.yy.c"
    break;

  case 18: /* procedure: "proc" identifier "(" fnargs_list ")" nwp statements "end" trm  */
#line 279 "src/parser.y"
                                                                                                   { ast_util_ModuleAndProcTable_add(ast_ModuleStack_top(), (yyvsp[-7].astnode_identifier), (yyvsp[-5].astnode_fnargs_list), (yyvsp[-2].astnode_statements));
                                                                                                       ast_Identifier_destroy(&(yyvsp[-7].astnode_identifier));
                                                                                                   }
#line 1733 "src/parser.yy.c"
    break;

  case 19: /* fnargs_list: identifier nws  */
#line 285 "src/parser.y"
                                                                                                   { (yyval.astnode_fnargs_list) = ast_FnArgsList(NULL, (yyvsp[-1].astnode_identifier)); }
#line 1739 "src/parser.yy.c"
    break;

  case 20: /* fnargs_list: identifier "," nws  */
#line 286 "src/parser.y"
                                                                                                   { (yyval.astnode_fnargs_list) = ast_FnArgsList(NULL, (yyvsp[-2].astnode_identifier)); }
#line 1745 "src/parser.yy.c"
    break;

  case 21: /* fnargs_list: identifier "," nws fnargs_list  */
#line 287 "src/parser.y"
                                                                                                   { (yyval.astnode_fnargs_list) = ast_FnArgsList((yyvsp[0].astnode_fnargs_list), (yyvsp[-3].astnode_identifier)); }
#line 1751 "src/parser.yy.c"
    break;

  case 22: /* statements: %empty  */
#line 291 "src/parser.y"
                                                                                                   { (yyval.astnode_statements) = NULL; }
#line 1757 "src/parser.yy.c"
    break;

  case 23: /* statements: statement statements  */
#line 292 "src/parser.y"
                                                                                                   { (yyval.astnode_statements) = ast_Statements((yyvsp[0].astnode_statements), (yyvsp[-1].astnode_statement)); }
#line 1763 "src/parser.yy.c"
    break;

  case 24: /* statement: "pass" trm  */
#line 296 "src/parser.y"
                                                                                                   { (yyval.astnode_statement) = ast_Statement_empty(lex_line_no - (yyvsp[0].line_count)); }
#line 1769 "src/parser.yy.c"
    break;

  case 25: /* statement: "break" trm  */
#line 297 "src/parser.y"
                                                                                                   { (yyval.astnode_statement) = ast_Statement_break(lex_line_no - (yyvsp[0].line_count)); }
#line 1775 "src/parser.yy.c"
    break;

  case 26: /* statement: "continue" trm  */
#line 298 "src/parser.y"
                                                                                                   { (yyval.astnode_statement) = ast_Statement_continue(lex_line_no - (yyvsp[0].line_count)); }
#line 1781 "src/parser.yy.c"
    break;

  case 27: /* statement: "return" expression trm  */
#line 299 "src/parser.y"
                                                                                                   { (yyval.astnode_statement) = ast_Statement_return((yyvsp[-1].astnode_expression), lex_line_no - (yyvsp[0].line_count)); }
#line 1787 "src/parser.yy.c"
    break;

  case 28: /* statement: "return" trm  */
#line 300 "src/parser.y"
                                                                                                   { (yyval.astnode_statement) = ast_Statement_return(NULL, lex_line_no - (yyvsp[0].line_count)); }
#line 1793 "src/parser.yy.c"
    break;

  case 29: /* statement: assignment trm  */
#line 301 "src/parser.y"
                                                                                                   { (yyval.astnode_statement) = ast_Statement_Assignment((yyvsp[-1].astnode_assignment), lex_line_no - (yyvsp[0].line_count)); }
#line 1799 "src/parser.yy.c"
    break;

  case 30: /* statement: compound_statement trm  */
#line 302 "src/parser.y"
                                                                                                   { (yyval.astnode_statement) = ast_Statement_CompoundSt((yyvsp[-1].astnode_compound_statement), lex_line_no - (yyvsp[0].line_count)); }
#line 1805 "src/parser.yy.c"
    break;

  case 31: /* assignment: "var" identifier "=" expression  */
#line 306 "src/parser.y"
                                                                                                   { (yyval.astnode_assignment) = ast_Assignment_create((yyvsp[-2].astnode_identifier), (yyvsp[0].astnode_expression), false, false); }
#line 1811 "src/parser.yy.c"
    break;

  case 32: /* assignment: "var" identifier "=" "const" expression  */
#line 307 "src/parser.y"
                                                                                                   { (yyval.astnode_assignment) = ast_Assignment_create((yyvsp[-3].astnode_identifier), (yyvsp[0].astnode_expression), true, false); }
#line 1817 "src/parser.yy.c"
    break;

  case 33: /* assignment: "var" identifier "=" "weak" expression  */
#line 308 "src/parser.y"
                                                                                                   { (yyval.astnode_assignment) = ast_Assignment_create((yyvsp[-3].astnode_identifier), (yyvsp[0].astnode_expression), false, true); }
#line 1823 "src/parser.yy.c"
    break;

  case 34: /* assignment: "var" identifier "=" "const" "weak" expression  */
#line 309 "src/parser.y"
                                                                                                   { (yyval.astnode_assignment) = ast_Assignment_create((yyvsp[-4].astnode_identifier), (yyvsp[0].astnode_expression), true, true); }
#line 1829 "src/parser.yy.c"
    break;

  case 35: /* assignment: "var" identifier "=" "weak" "const" expression  */
#line 310 "src/parser.y"
                                                                                                   { (yyval.astnode_assignment) = ast_Assignment_create((yyvsp[-4].astnode_identifier), (yyvsp[0].astnode_expression), true, true); }
#line 1835 "src/parser.yy.c"
    break;

  case 36: /* assignment: expression  */
#line 311 "src/parser.y"
                                                                                                   { (yyval.astnode_assignment) = ast_Assignment_tovoid((yyvsp[0].astnode_expression)); }
#line 1841 "src/parser.yy.c"
    break;

  case 37: /* compound_statement: if_block  */
#line 315 "src/parser.y"
                                                                                                   { (yyval.astnode_compound_statement) = ast_CompoundSt_IfBlock((yyvsp[0].astnode_if_block)); }
#line 1847 "src/parser.yy.c"
    break;

  case 38: /* compound_statement: while_block  */
#line 316 "src/parser.y"
                                                                                                   { (yyval.astnode_compound_statement) = ast_CompoundSt_WhileBlock((yyvsp[0].astnode_while_block)); }
#line 1853 "src/parser.yy.c"
    break;

  case 39: /* compound_statement: for_block  */
#line 317 "src/parser.y"
                                                                                                   { (yyval.astnode_compound_statement) = ast_CompoundSt_ForBlock((yyvsp[0].astnode_for_block)); }
#line 1859 "src/parser.yy.c"
    break;

  case 40: /* compound_statement: block  */
#line 318 "src/parser.y"
                                                                                                   { (yyval.astnode_compound_statement) = ast_CompoundSt_Block((yyvsp[0].astnode_block)); }
#line 1865 "src/parser.yy.c"
    break;

  case 41: /* if_block: "if" condition "then" nwp statements "end"  */
#line 322 "src/parser.y"
                                                                                                   { (yyval.astnode_if_block) = ast_IfBlock((yyvsp[-4].astnode_expression), (yyvsp[-1].astnode_statements), NULL); }
#line 1871 "src/parser.yy.c"
    break;

  case 42: /* if_block: "if" condition "then" nwp statements else_block  */
#line 323 "src/parser.y"
                                                                                                   { (yyval.astnode_if_block) = ast_IfBlock((yyvsp[-4].astnode_expression), (yyvsp[-1].astnode_statements), (yyvsp[0].astnode_else_block)); }
#line 1877 "src/parser.yy.c"
    break;

  case 43: /* else_block: "else" nwp statements "end"  */
#line 327 "src/parser.y"
                                                                                                   { (yyval.astnode_else_block) = ast_ElseBlock(NULL, (yyvsp[-1].astnode_statements), NULL); }
#line 1883 "src/parser.yy.c"
    break;

  case 44: /* else_block: "else" "if" condition "then" nwp statements "end"  */
#line 328 "src/parser.y"
                                                                                                   { (yyval.astnode_else_block) = ast_ElseBlock((yyvsp[-4].astnode_expression), (yyvsp[-1].astnode_statements), NULL); }
#line 1889 "src/parser.yy.c"
    break;

  case 45: /* else_block: "else" "if" condition "then" nwp statements else_block  */
#line 329 "src/parser.y"
                                                                                                   { (yyval.astnode_else_block) = ast_ElseBlock((yyvsp[-4].astnode_expression), (yyvsp[-1].astnode_statements), (yyvsp[0].astnode_else_block)); }
#line 1895 "src/parser.yy.c"
    break;

  case 46: /* else_block: "elif" condition "then" nwp statements "end"  */
#line 330 "src/parser.y"
                                                                                                   { (yyval.astnode_else_block) = ast_ElseBlock((yyvsp[-4].astnode_expression), (yyvsp[-1].astnode_statements), NULL); }
#line 1901 "src/parser.yy.c"
    break;

  case 47: /* else_block: "elif" condition "then" nwp statements else_block  */
#line 331 "src/parser.y"
                                                                                                   { (yyval.astnode_else_block) = ast_ElseBlock((yyvsp[-4].astnode_expression), (yyvsp[-1].astnode_statements), (yyvsp[0].astnode_else_block)); }
#line 1907 "src/parser.yy.c"
    break;

  case 48: /* while_block: "while" condition "do" nwp statements "end"  */
#line 335 "src/parser.y"
                                                                                                   { (yyval.astnode_while_block) = ast_WhileBlock((yyvsp[-4].astnode_expression), (yyvsp[-1].astnode_statements)); }
#line 1913 "src/parser.yy.c"
    break;

  case 49: /* for_block: "for" identifier "from" expression "to" expression "do" nwp statements "end"  */
#line 339 "src/parser.y"
                                                                                                   { (yyval.astnode_for_block) = ast_ForBlock((yyvsp[-8].astnode_identifier), (yyvsp[-6].astnode_expression), (yyvsp[-4].astnode_expression), NULL, (yyvsp[-1].astnode_statements)); }
#line 1919 "src/parser.yy.c"
    break;

  case 50: /* for_block: "for" identifier "from" expression "to" expression "by" expression "do" nwp statements "end"  */
#line 340 "src/parser.y"
                                                                                                   { (yyval.astnode_for_block) = ast_ForBlock((yyvsp[-10].astnode_identifier), (yyvsp[-8].astnode_expression), (yyvsp[-6].astnode_expression), (yyvsp[-4].astnode_expression), (yyvsp[-1].astnode_statements)); }
#line 1925 "src/parser.yy.c"
    break;

  case 51: /* for_block: "for" identifier "in" expression "do" nwp statements "end"  */
#line 341 "src/parser.y"
                                                                                                   { (yyval.astnode_for_block) = ast_ForBlock_iterate(NULL, (yyvsp[-6].astnode_identifier), (yyvsp[-4].astnode_expression), (yyvsp[-1].astnode_statements)); }
#line 1931 "src/parser.yy.c"
    break;

  case 52: /* for_block: "for" identifier "," identifier "in" expression "do" nwp statements "end"  */
#line 342 "src/parser.y"
                                                                                                   { (yyval.astnode_for_block) = ast_ForBlock_iterate((yyvsp[-8].astnode_identifier), (yyvsp[-6].astnode_identifier), (yyvsp[-4].astnode_expression), (yyvsp[-1].astnode_statements)); }
#line 1937 "src/parser.yy.c"
    break;

  case 53: /* block: "block" nwp statements "end"  */
#line 346 "src/parser.y"
                                                                                                   { (yyval.astnode_block) = ast_Block((yyvsp[-1].astnode_statements)); }
#line 1943 "src/parser.yy.c"
    break;

  case 54: /* condition: conditional_expression  */
#line 350 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 1949 "src/parser.yy.c"
    break;

  case 55: /* expression: assignment_expression  */
#line 354 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 1955 "src/parser.yy.c"
    break;

  case 56: /* assignment_expression: conditional_expression  */
#line 358 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 1961 "src/parser.yy.c"
    break;

  case 57: /* assignment_expression: postfix_expression "=" assignment_expression  */
#line 359 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1967 "src/parser.yy.c"
    break;

  case 58: /* assignment_expression: postfix_expression "=" "const" assignment_expression  */
#line 360 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression(TOKOP_ASSIGN_CONST, (yyvsp[-3].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1973 "src/parser.yy.c"
    break;

  case 59: /* assignment_expression: postfix_expression "=" "weak" assignment_expression  */
#line 361 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression(TOKOP_ASSIGN_WEAK, (yyvsp[-3].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1979 "src/parser.yy.c"
    break;

  case 60: /* assignment_expression: postfix_expression "=" "const" "weak" assignment_expression  */
#line 362 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression(TOKOP_ASSIGN_CONST_WEAK, (yyvsp[-4].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1985 "src/parser.yy.c"
    break;

  case 61: /* assignment_expression: postfix_expression "=" "weak" "const" assignment_expression  */
#line 363 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression(TOKOP_ASSIGN_CONST_WEAK, (yyvsp[-4].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1991 "src/parser.yy.c"
    break;

  case 62: /* assignment_expression: postfix_expression "||=" assignment_expression  */
#line 364 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1997 "src/parser.yy.c"
    break;

  case 63: /* assignment_expression: postfix_expression "&&=" assignment_expression  */
#line 365 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2003 "src/parser.yy.c"
    break;

  case 64: /* assignment_expression: postfix_expression "|=" assignment_expression  */
#line 366 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2009 "src/parser.yy.c"
    break;

  case 65: /* assignment_expression: postfix_expression "^=" assignment_expression  */
#line 367 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2015 "src/parser.yy.c"
    break;

  case 66: /* assignment_expression: postfix_expression "&=" assignment_expression  */
#line 368 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2021 "src/parser.yy.c"
    break;

  case 67: /* assignment_expression: postfix_expression ">>>=" assignment_expression  */
#line 369 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2027 "src/parser.yy.c"
    break;

  case 68: /* assignment_expression: postfix_expression "<<=" assignment_expression  */
#line 370 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2033 "src/parser.yy.c"
    break;

  case 69: /* assignment_expression: postfix_expression ">>=" assignment_expression  */
#line 371 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2039 "src/parser.yy.c"
    break;

  case 70: /* assignment_expression: postfix_expression "+=" assignment_expression  */
#line 372 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2045 "src/parser.yy.c"
    break;

  case 71: /* assignment_expression: postfix_expression "-=" assignment_expression  */
#line 373 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2051 "src/parser.yy.c"
    break;

  case 72: /* assignment_expression: postfix_expression "*=" assignment_expression  */
#line 374 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2057 "src/parser.yy.c"
    break;

  case 73: /* assignment_expression: postfix_expression "/=" assignment_expression  */
#line 375 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2063 "src/parser.yy.c"
    break;

  case 74: /* assignment_expression: postfix_expression "%=" assignment_expression  */
#line 376 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2069 "src/parser.yy.c"
    break;

  case 75: /* assignment_expression: postfix_expression "**=" assignment_expression  */
#line 377 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2075 "src/parser.yy.c"
    break;

  case 76: /* assignment_expression: postfix_expression "//=" assignment_expression  */
#line 378 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2081 "src/parser.yy.c"
    break;

  case 77: /* conditional_expression: logical_or_expression  */
#line 382 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 2087 "src/parser.yy.c"
    break;

  case 78: /* conditional_expression: conditional_expression "if" condition "else" conditional_expression  */
#line 383 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression(TOKOP_TERNARY_COND, (yyvsp[-4].astnode_expression), (yyvsp[0].astnode_expression), (yyvsp[-2].astnode_expression)); }
#line 2093 "src/parser.yy.c"
    break;

  case 79: /* logical_or_expression: logical_and_expression  */
#line 387 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 2099 "src/parser.yy.c"
    break;

  case 80: /* logical_or_expression: logical_or_expression "||" logical_and_expression  */
#line 388 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2105 "src/parser.yy.c"
    break;

  case 81: /* logical_and_expression: bitwise_or_expression  */
#line 392 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 2111 "src/parser.yy.c"
    break;

  case 82: /* logical_and_expression: logical_and_expression "&&" bitwise_or_expression  */
#line 393 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2117 "src/parser.yy.c"
    break;

  case 83: /* bitwise_or_expression: bitwise_xor_expression  */
#line 397 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 2123 "src/parser.yy.c"
    break;

  case 84: /* bitwise_or_expression: bitwise_or_expression "|" bitwise_xor_expression  */
#line 398 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2129 "src/parser.yy.c"
    break;

  case 85: /* bitwise_xor_expression: bitwise_and_expression  */
#line 402 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 2135 "src/parser.yy.c"
    break;

  case 86: /* bitwise_xor_expression: bitwise_xor_expression "^" bitwise_and_expression  */
#line 403 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2141 "src/parser.yy.c"
    break;

  case 87: /* bitwise_and_expression: equality_expression  */
#line 407 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 2147 "src/parser.yy.c"
    break;

  case 88: /* bitwise_and_expression: bitwise_and_expression "&" equality_expression  */
#line 408 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2153 "src/parser.yy.c"
    break;

  case 89: /* equality_expression: relational_expression  */
#line 412 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 2159 "src/parser.yy.c"
    break;

  case 90: /* equality_expression: equality_expression "==" relational_expression  */
#line 413 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2165 "src/parser.yy.c"
    break;

  case 91: /* equality_expression: equality_expression "!=" relational_expression  */
#line 414 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2171 "src/parser.yy.c"
    break;

  case 92: /* relational_expression: shift_expression  */
#line 418 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 2177 "src/parser.yy.c"
    break;

  case 93: /* relational_expression: relational_expression "<" shift_expression  */
#line 419 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2183 "src/parser.yy.c"
    break;

  case 94: /* relational_expression: relational_expression ">" shift_expression  */
#line 420 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2189 "src/parser.yy.c"
    break;

  case 95: /* relational_expression: relational_expression "<=" shift_expression  */
#line 421 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2195 "src/parser.yy.c"
    break;

  case 96: /* relational_expression: relational_expression ">=" shift_expression  */
#line 422 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2201 "src/parser.yy.c"
    break;

  case 97: /* shift_expression: additive_expression  */
#line 426 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 2207 "src/parser.yy.c"
    break;

  case 98: /* shift_expression: shift_expression ">>>" additive_expression  */
#line 427 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2213 "src/parser.yy.c"
    break;

  case 99: /* shift_expression: shift_expression "<<" additive_expression  */
#line 428 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2219 "src/parser.yy.c"
    break;

  case 100: /* shift_expression: shift_expression ">>" additive_expression  */
#line 429 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2225 "src/parser.yy.c"
    break;

  case 101: /* additive_expression: multiplicative_expression  */
#line 433 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 2231 "src/parser.yy.c"
    break;

  case 102: /* additive_expression: additive_expression "+" multiplicative_expression  */
#line 434 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2237 "src/parser.yy.c"
    break;

  case 103: /* additive_expression: additive_expression "-" multiplicative_expression  */
#line 435 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2243 "src/parser.yy.c"
    break;

  case 104: /* multiplicative_expression: unary_expression  */
#line 439 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 2249 "src/parser.yy.c"
    break;

  case 105: /* multiplicative_expression: multiplicative_expression "*" unary_expression  */
#line 440 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2255 "src/parser.yy.c"
    break;

  case 106: /* multiplicative_expression: multiplicative_expression "/" unary_expression  */
#line 441 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2261 "src/parser.yy.c"
    break;

  case 107: /* multiplicative_expression: multiplicative_expression "%" unary_expression  */
#line 442 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2267 "src/parser.yy.c"
    break;

  case 108: /* multiplicative_expression: unary_expression "**" multiplicative_expression  */
#line 443 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2273 "src/parser.yy.c"
    break;

  case 109: /* multiplicative_expression: multiplicative_expression "//" unary_expression  */
#line 444 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2279 "src/parser.yy.c"
    break;

  case 110: /* unary_expression: postfix_expression  */
#line 448 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 2285 "src/parser.yy.c"
    break;

  case 111: /* unary_expression: "+" unary_expression  */
#line 449 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), NULL, (yyvsp[0].astnode_expression), NULL); }
#line 2291 "src/parser.yy.c"
    break;

  case 112: /* unary_expression: "-" unary_expression  */
#line 450 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), NULL, (yyvsp[0].astnode_expression), NULL); }
#line 2297 "src/parser.yy.c"
    break;

  case 113: /* unary_expression: "!" unary_expression  */
#line 451 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), NULL, (yyvsp[0].astnode_expression), NULL); }
#line 2303 "src/parser.yy.c"
    break;

  case 114: /* unary_expression: "~" unary_expression  */
#line 452 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), NULL, (yyvsp[0].astnode_expression), NULL); }
#line 2309 "src/parser.yy.c"
    break;

  case 115: /* unary_expression: "++" unary_expression  */
#line 453 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), NULL, (yyvsp[0].astnode_expression), NULL); }
#line 2315 "src/parser.yy.c"
    break;

  case 116: /* unary_expression: "--" unary_expression  */
#line 454 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), NULL, (yyvsp[0].astnode_expression), NULL); }
#line 2321 "src/parser.yy.c"
    break;

  case 117: /* postfix_expression: primary_expression  */
#line 458 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 2327 "src/parser.yy.c"
    break;

  case 118: /* postfix_expression: postfix_expression "(" ")"  */
#line 459 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression(TOKOP_FNCALL, (yyvsp[-2].astnode_expression), NULL, NULL); }
#line 2333 "src/parser.yy.c"
    break;

  case 119: /* postfix_expression: postfix_expression "(" nws comma_list ")"  */
#line 460 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression(TOKOP_FNCALL, (yyvsp[-4].astnode_expression),
                                                                                                       ast_Expression_CommaSepList((yyvsp[-1].astnode_comma_list)), NULL);
                                                                                                   }
#line 2341 "src/parser.yy.c"
    break;

  case 120: /* postfix_expression: postfix_expression "[" expression "]"  */
#line 463 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression(TOKOP_INDEXING, (yyvsp[-3].astnode_expression), (yyvsp[-1].astnode_expression), NULL); }
#line 2347 "src/parser.yy.c"
    break;

  case 121: /* postfix_expression: "$" "[" expression "]"  */
#line 464 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression(TOKOP_FNARGS_INDEXING, NULL, (yyvsp[-1].astnode_expression), NULL); }
#line 2353 "src/parser.yy.c"
    break;

  case 122: /* postfix_expression: "$" "(" expression ")"  */
#line 465 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression(TOKOP_FNARGS_INDEXING, NULL, (yyvsp[-1].astnode_expression), NULL); }
#line 2359 "src/parser.yy.c"
    break;

  case 123: /* postfix_expression: "$" "<decintlit>"  */
#line 466 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression(TOKOP_FNARGS_INDEXING, NULL,
                                                                                                       ast_Expression_Literal(
                                                                                                           ast_Literal_i64((yyvsp[0].literal_i64))), NULL);
                                                                                                   }
#line 2368 "src/parser.yy.c"
    break;

  case 124: /* postfix_expression: "$" identifier  */
#line 470 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression(TOKOP_FNARGS_INDEXING, NULL,
                                                                                                       ast_Expression_Identifier((yyvsp[0].astnode_identifier)), NULL);
                                                                                                   }
#line 2376 "src/parser.yy.c"
    break;

  case 125: /* postfix_expression: postfix_expression "++"  */
#line 473 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[0].tok), (yyvsp[-1].astnode_expression), NULL, NULL); }
#line 2382 "src/parser.yy.c"
    break;

  case 126: /* postfix_expression: postfix_expression "--"  */
#line 474 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[0].tok), (yyvsp[-1].astnode_expression), NULL, NULL); }
#line 2388 "src/parser.yy.c"
    break;

  case 127: /* postfix_expression: postfix_expression "." identifier  */
#line 475 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), ast_Expression_Literal(
                                                                                                           ast_Literal_str(strdup((yyvsp[0].astnode_identifier)))), NULL);
                                                                                                       ast_Identifier_destroy(&(yyvsp[0].astnode_identifier));
                                                                                                   }
#line 2397 "src/parser.yy.c"
    break;

  case 128: /* postfix_expression: postfix_expression "::" identifier  */
#line 479 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression),
                                                                                                       ast_Expression_Identifier((yyvsp[0].astnode_identifier)), NULL);
                                                                                                   }
#line 2405 "src/parser.yy.c"
    break;

  case 129: /* postfix_expression: postfix_expression ":" identifier  */
#line 482 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression(TOKEN_DCOLON, (yyvsp[-2].astnode_expression),
                                                                                                       ast_Expression_Identifier((yyvsp[0].astnode_identifier)), NULL);
                                                                                                   }
#line 2413 "src/parser.yy.c"
    break;

  case 130: /* primary_expression: literal  */
#line 488 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression_Literal((yyvsp[0].astnode_literal)); }
#line 2419 "src/parser.yy.c"
    break;

  case 131: /* primary_expression: identifier  */
#line 489 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = ast_Expression_Identifier((yyvsp[0].astnode_identifier)); }
#line 2425 "src/parser.yy.c"
    break;

  case 132: /* primary_expression: "(" expression ")"  */
#line 490 "src/parser.y"
                                                                                                   { (yyval.astnode_expression) = (yyvsp[-1].astnode_expression); }
#line 2431 "src/parser.yy.c"
    break;

  case 133: /* comma_list: expression nws  */
#line 494 "src/parser.y"
                                                                                                   { (yyval.astnode_comma_list) = ast_CommaSepList(NULL, (yyvsp[-1].astnode_expression)); }
#line 2437 "src/parser.yy.c"
    break;

  case 134: /* comma_list: expression "," nws  */
#line 495 "src/parser.y"
                                                                                                   { (yyval.astnode_comma_list) = ast_CommaSepList(NULL, (yyvsp[-2].astnode_expression)); }
#line 2443 "src/parser.yy.c"
    break;

  case 135: /* comma_list: expression "," nws comma_list  */
#line 496 "src/parser.y"
                                                                                                   { (yyval.astnode_comma_list) = ast_CommaSepList((yyvsp[0].astnode_comma_list), (yyvsp[-3].astnode_expression)); }
#line 2449 "src/parser.yy.c"
    break;

  case 136: /* assoc_list: string_literal ":" expression nws  */
#line 500 "src/parser.y"
                                                                                                   { (yyval.astnode_assoc_list) = ast_AssociativeList(NULL, (yyvsp[-3].astnode_literal), (yyvsp[-1].astnode_expression)); }
#line 2455 "src/parser.yy.c"
    break;

  case 137: /* assoc_list: string_literal ":" expression "," nws  */
#line 501 "src/parser.y"
                                                                                                   { (yyval.astnode_assoc_list) = ast_AssociativeList(NULL, (yyvsp[-4].astnode_literal), (yyvsp[-2].astnode_expression)); }
#line 2461 "src/parser.yy.c"
    break;

  case 138: /* assoc_list: string_literal ":" expression "," nws assoc_list  */
#line 502 "src/parser.y"
                                                                                                   { (yyval.astnode_assoc_list) = ast_AssociativeList((yyvsp[0].astnode_assoc_list), (yyvsp[-5].astnode_literal), (yyvsp[-3].astnode_expression)); }
#line 2467 "src/parser.yy.c"
    break;

  case 139: /* assoc_list: identifier ":" expression nws  */
#line 503 "src/parser.y"
                                                                                                   { (yyval.astnode_assoc_list) = ast_AssociativeList(NULL,
                                                                                                           ast_Literal_str(strdup((yyvsp[-3].astnode_identifier))), (yyvsp[-1].astnode_expression));
                                                                                                       ast_Identifier_destroy(&(yyvsp[-3].astnode_identifier));
                                                                                                   }
#line 2476 "src/parser.yy.c"
    break;

  case 140: /* assoc_list: identifier ":" expression "," nws  */
#line 507 "src/parser.y"
                                                                                                   { (yyval.astnode_assoc_list) = ast_AssociativeList(NULL,
                                                                                                           ast_Literal_str(strdup((yyvsp[-4].astnode_identifier))), (yyvsp[-2].astnode_expression));
                                                                                                       ast_Identifier_destroy(&(yyvsp[-4].astnode_identifier));
                                                                                                   }
#line 2485 "src/parser.yy.c"
    break;

  case 141: /* assoc_list: identifier ":" expression "," nws assoc_list  */
#line 511 "src/parser.y"
                                                                                                   { (yyval.astnode_assoc_list) = ast_AssociativeList((yyvsp[0].astnode_assoc_list),
                                                                                                           ast_Literal_str(strdup((yyvsp[-5].astnode_identifier))), (yyvsp[-3].astnode_expression));
                                                                                                       ast_Identifier_destroy(&(yyvsp[-5].astnode_identifier));
                                                                                                   }
#line 2494 "src/parser.yy.c"
    break;

  case 142: /* assoc_list: "[" identifier "]" ":" expression nws  */
#line 515 "src/parser.y"
                                                                                                   {
                                                                                                       /* allocate memory for the template string
                                                                                                          ast_Literal_interp_str takes ownership so it
                                                                                                          needs not be freed */
                                                                                                       char *key = malloc(strlen((yyvsp[-4].astnode_identifier)) + 3);
                                                                                                       /* create the template string */
                                                                                                       sprintf(key, "{%s}", (yyvsp[-4].astnode_identifier));
                                                                                                       /* pretend that the map key is a template
                                                                                                          string literal */
                                                                                                       (yyval.astnode_assoc_list) = ast_AssociativeList(NULL,
                                                                                                           ast_Literal_interp_str(key), (yyvsp[-1].astnode_expression));
                                                                                                       /* destroy the identifier */
                                                                                                       ast_Identifier_destroy(&(yyvsp[-4].astnode_identifier));
                                                                                                   }
#line 2513 "src/parser.yy.c"
    break;

  case 143: /* assoc_list: "[" identifier "]" ":" expression "," nws  */
#line 529 "src/parser.y"
                                                                                                   {
                                                                                                       /* allocate memory for the template string
                                                                                                          ast_Literal_interp_str takes ownership so it
                                                                                                          needs not be freed */
                                                                                                       char *key = malloc(strlen((yyvsp[-5].astnode_identifier)) + 3);
                                                                                                       /* create the template string */
                                                                                                       sprintf(key, "{%s}", (yyvsp[-5].astnode_identifier));
                                                                                                       /* pretend that the map key is a template
                                                                                                          string literal */
                                                                                                       (yyval.astnode_assoc_list) = ast_AssociativeList(NULL,
                                                                                                           ast_Literal_interp_str(key), (yyvsp[-2].astnode_expression));
                                                                                                       /* destroy the identifier */
                                                                                                       ast_Identifier_destroy(&(yyvsp[-5].astnode_identifier));
                                                                                                   }
#line 2532 "src/parser.yy.c"
    break;

  case 144: /* assoc_list: "[" identifier "]" ":" expression "," nws assoc_list  */
#line 543 "src/parser.y"
                                                                                                   {
                                                                                                       /* allocate memory for the template string
                                                                                                          ast_Literal_interp_str takes ownership so it
                                                                                                          needs not be freed */
                                                                                                       char *key = malloc(strlen((yyvsp[-6].astnode_identifier)) + 3);
                                                                                                       /* create the template string */
                                                                                                       sprintf(key, "{%s}", (yyvsp[-6].astnode_identifier));
                                                                                                       /* pretend that the map key is a template
                                                                                                          string literal */
                                                                                                       (yyval.astnode_assoc_list) = ast_AssociativeList((yyvsp[0].astnode_assoc_list),
                                                                                                           ast_Literal_interp_str(key), (yyvsp[-3].astnode_expression));
                                                                                                       /* destroy the identifier */
                                                                                                       ast_Identifier_destroy(&(yyvsp[-6].astnode_identifier));
                                                                                                   }
#line 2551 "src/parser.yy.c"
    break;

  case 145: /* literal: "<boollit>"  */
#line 560 "src/parser.y"
                                                                                                   { (yyval.astnode_literal) = ast_Literal_bul((yyvsp[0].literal_bool)); }
#line 2557 "src/parser.yy.c"
    break;

  case 146: /* literal: "<charlit>"  */
#line 561 "src/parser.y"
                                                                                                   { (yyval.astnode_literal) = ast_Literal_chr((yyvsp[0].literal_char)); }
#line 2563 "src/parser.yy.c"
    break;

  case 147: /* literal: "<binfloattlit>"  */
#line 562 "src/parser.y"
                                                                                                   { (yyval.astnode_literal) = ast_Literal_f64((yyvsp[0].literal_f64)); }
#line 2569 "src/parser.yy.c"
    break;

  case 148: /* literal: "<octfloattlit>"  */
#line 563 "src/parser.y"
                                                                                                   { (yyval.astnode_literal) = ast_Literal_f64((yyvsp[0].literal_f64)); }
#line 2575 "src/parser.yy.c"
    break;

  case 149: /* literal: "<decfloattlit>"  */
#line 564 "src/parser.y"
                                                                                                   { (yyval.astnode_literal) = ast_Literal_f64((yyvsp[0].literal_f64)); }
#line 2581 "src/parser.yy.c"
    break;

  case 150: /* literal: "<hexfloattlit>"  */
#line 565 "src/parser.y"
                                                                                                   { (yyval.astnode_literal) = ast_Literal_f64((yyvsp[0].literal_f64)); }
#line 2587 "src/parser.yy.c"
    break;

  case 151: /* literal: "<binintlit>"  */
#line 566 "src/parser.y"
                                                                                                   { (yyval.astnode_literal) = ast_Literal_i64((yyvsp[0].literal_i64)); }
#line 2593 "src/parser.yy.c"
    break;

  case 152: /* literal: "<octintlit>"  */
#line 567 "src/parser.y"
                                                                                                   { (yyval.astnode_literal) = ast_Literal_i64((yyvsp[0].literal_i64)); }
#line 2599 "src/parser.yy.c"
    break;

  case 153: /* literal: "<decintlit>"  */
#line 568 "src/parser.y"
                                                                                                   { (yyval.astnode_literal) = ast_Literal_i64((yyvsp[0].literal_i64)); }
#line 2605 "src/parser.yy.c"
    break;

  case 154: /* literal: "<hexintlit>"  */
#line 569 "src/parser.y"
                                                                                                   { (yyval.astnode_literal) = ast_Literal_i64((yyvsp[0].literal_i64)); }
#line 2611 "src/parser.yy.c"
    break;

  case 155: /* literal: string_literal  */
#line 570 "src/parser.y"
                                                                                                   { (yyval.astnode_literal) = (yyvsp[0].astnode_literal); }
#line 2617 "src/parser.yy.c"
    break;

  case 156: /* literal: list_literal  */
#line 571 "src/parser.y"
                                                                                                   { (yyval.astnode_literal) = (yyvsp[0].astnode_literal); }
#line 2623 "src/parser.yy.c"
    break;

  case 157: /* literal: map_literal  */
#line 572 "src/parser.y"
                                                                                                   { (yyval.astnode_literal) = (yyvsp[0].astnode_literal); }
#line 2629 "src/parser.yy.c"
    break;

  case 158: /* string_literal: "<strlit>"  */
#line 576 "src/parser.y"
                                                                                                   { (yyval.astnode_literal) = ast_Literal_str((yyvsp[0].literal_str)); }
#line 2635 "src/parser.yy.c"
    break;

  case 159: /* string_literal: "<interpstrlit>"  */
#line 577 "src/parser.y"
                                                                                                   { (yyval.astnode_literal) = ast_Literal_interp_str((yyvsp[0].literal_str)); }
#line 2641 "src/parser.yy.c"
    break;

  case 160: /* list_literal: "[" "]"  */
#line 581 "src/parser.y"
                                                                                                   { (yyval.astnode_literal) = ast_Literal_lst(NULL); }
#line 2647 "src/parser.yy.c"
    break;

  case 161: /* list_literal: "[" nws comma_list "]"  */
#line 582 "src/parser.y"
                                                                                                   { (yyval.astnode_literal) = ast_Literal_lst((yyvsp[-1].astnode_comma_list)); }
#line 2653 "src/parser.yy.c"
    break;

  case 162: /* map_literal: "{" "}"  */
#line 586 "src/parser.y"
                                                                                                   { (yyval.astnode_literal) = ast_Literal_map(NULL); }
#line 2659 "src/parser.yy.c"
    break;

  case 163: /* map_literal: "{" nws assoc_list "}"  */
#line 587 "src/parser.y"
                                                                                                   { (yyval.astnode_literal) = ast_Literal_map((yyvsp[-1].astnode_assoc_list)); }
#line 2665 "src/parser.yy.c"
    break;

  case 164: /* identifier: "<identifier>"  */
#line 591 "src/parser.y"
                                                                                                   { (yyval.astnode_identifier) = ast_Identifier((yyvsp[0].identifier_name)); }
#line 2671 "src/parser.yy.c"
    break;


#line 2675 "src/parser.yy.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= TOKEN_EOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == TOKEN_EOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 594 "src/parser.y"


#include "parser/parse_bool.c.h"
#include "parser/parse_chr.c.h"
#include "parser/parse_f64.c.h"
#include "parser/parse_i64.c.h"
#include "parser/parse_str.c.h"

int yyerror(const char* msg)
{
    parse_throw(msg, true);
    return ERR_PARSER;
}

void parse_interpret(FILE *f)
{
    yyin = f;
    if (yyin == stdin) printf(
        "Welcome to Shsc Version %s\n"
        "Enter your code and when done, press CTRL+D\n"
        "%s", VERSION, ">> "
    );
    if (global_lex_dbg) {
        lex_Token_t tok = lex_Token_getnext(yyin);
        while (tok != TOKEN_EOF) {
            printf("%s: %s\n", lex_Token_getcode(tok), lex_Token_getsymbol(tok));
            tok = lex_Token_getnext(f);
        }
        printf("%s\n", lex_Token_getcode(tok));
    }
    else yyparse();
    lex_Buffer_free();
}

void parse_throw(const char *msg, bool on)
{
    if (!msg) abort();
    int line = lex_line_no;
    if (lex_currtok == TOKEN_NEWLINE) --line;
    if (on) io_print_srcerr(line, lex_char_no, "parsing error: %s on '%s'", msg, lex_Token_getsymbol(lex_currtok));
    else io_print_srcerr(line, lex_char_no, "parsing error: %s", msg);
#ifdef DEBUG
    abort();
#else
    exit(ERR_PARSER);
#endif
}
