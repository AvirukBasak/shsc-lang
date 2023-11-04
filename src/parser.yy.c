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
  YYSYMBOL_TOKEN_NEWLINE = 74,             /* "\n"  */
  YYSYMBOL_TOKEN_KWD_MODULE = 75,          /* "module"  */
  YYSYMBOL_TOKEN_KWD_PROC = 76,            /* "proc"  */
  YYSYMBOL_TOKEN_KWD_START = 77,           /* "start"  */
  YYSYMBOL_TOKEN_KWD_END = 78,             /* "end"  */
  YYSYMBOL_TOKEN_KWD_BLOCK = 79,           /* "block"  */
  YYSYMBOL_TOKEN_KWD_IF = 80,              /* "if"  */
  YYSYMBOL_TOKEN_KWD_THEN = 81,            /* "then"  */
  YYSYMBOL_TOKEN_KWD_ELIF = 82,            /* "elif"  */
  YYSYMBOL_TOKEN_KWD_ELSE = 83,            /* "else"  */
  YYSYMBOL_TOKEN_KWD_WHILE = 84,           /* "while"  */
  YYSYMBOL_TOKEN_KWD_BREAK = 85,           /* "break"  */
  YYSYMBOL_TOKEN_KWD_CONTINUE = 86,        /* "continue"  */
  YYSYMBOL_TOKEN_KWD_FOR = 87,             /* "for"  */
  YYSYMBOL_TOKEN_KWD_FROM = 88,            /* "from"  */
  YYSYMBOL_TOKEN_KWD_TO = 89,              /* "to"  */
  YYSYMBOL_TOKEN_KWD_BY = 90,              /* "by"  */
  YYSYMBOL_TOKEN_KWD_IN = 91,              /* "in"  */
  YYSYMBOL_TOKEN_KWD_DO = 92,              /* "do"  */
  YYSYMBOL_TOKEN_KWD_VAR = 93,             /* "var"  */
  YYSYMBOL_TOKEN_KWD_CONST = 94,           /* "const"  */
  YYSYMBOL_TOKEN_KWD_PASS = 95,            /* "pass"  */
  YYSYMBOL_TOKEN_KWD_RETURN = 96,          /* "return"  */
  YYSYMBOL_TOKEN_KWD_WEAK = 97,            /* "weak"  */
  YYSYMBOL_TOKEN_INVALID = 98,             /* "<invalid>"  */
  YYSYMBOL_TOKEN_BOOL_LITERAL = 99,        /* "<boollit>"  */
  YYSYMBOL_TOKEN_CHAR_LITERAL = 100,       /* "<charlit>"  */
  YYSYMBOL_TOKEN_BINFLOAT_LITERAL = 101,   /* "<binfloattlit>"  */
  YYSYMBOL_TOKEN_OCTFLOAT_LITERAL = 102,   /* "<octfloattlit>"  */
  YYSYMBOL_TOKEN_DECFLOAT_LITERAL = 103,   /* "<decfloattlit>"  */
  YYSYMBOL_TOKEN_HEXFLOAT_LITERAL = 104,   /* "<hexfloattlit>"  */
  YYSYMBOL_TOKEN_BININT_LITERAL = 105,     /* "<binintlit>"  */
  YYSYMBOL_TOKEN_OCTINT_LITERAL = 106,     /* "<octintlit>"  */
  YYSYMBOL_TOKEN_DECINT_LITERAL = 107,     /* "<decintlit>"  */
  YYSYMBOL_TOKEN_HEXINT_LITERAL = 108,     /* "<hexintlit>"  */
  YYSYMBOL_TOKEN_STR_LITERAL = 109,        /* "<strlit>"  */
  YYSYMBOL_TOKEN_INTERP_STR_LITERAL = 110, /* "<interpstrlit>"  */
  YYSYMBOL_TOKEN_IDENTIFIER = 111,         /* "<identifier>"  */
  YYSYMBOL_YYACCEPT = 112,                 /* $accept  */
  YYSYMBOL_nws = 113,                      /* nws  */
  YYSYMBOL_nwp = 114,                      /* nwp  */
  YYSYMBOL_trm = 115,                      /* trm  */
  YYSYMBOL_module = 116,                   /* module  */
  YYSYMBOL_117_1 = 117,                    /* $@1  */
  YYSYMBOL_118_2 = 118,                    /* $@2  */
  YYSYMBOL_program = 119,                  /* program  */
  YYSYMBOL_procedure = 120,                /* procedure  */
  YYSYMBOL_statements = 121,               /* statements  */
  YYSYMBOL_statement = 122,                /* statement  */
  YYSYMBOL_assignment = 123,               /* assignment  */
  YYSYMBOL_compound_statement = 124,       /* compound_statement  */
  YYSYMBOL_if_block = 125,                 /* if_block  */
  YYSYMBOL_else_block = 126,               /* else_block  */
  YYSYMBOL_while_block = 127,              /* while_block  */
  YYSYMBOL_for_block = 128,                /* for_block  */
  YYSYMBOL_block = 129,                    /* block  */
  YYSYMBOL_condition = 130,                /* condition  */
  YYSYMBOL_expression = 131,               /* expression  */
  YYSYMBOL_assignment_expression = 132,    /* assignment_expression  */
  YYSYMBOL_conditional_expression = 133,   /* conditional_expression  */
  YYSYMBOL_logical_or_expression = 134,    /* logical_or_expression  */
  YYSYMBOL_logical_and_expression = 135,   /* logical_and_expression  */
  YYSYMBOL_bitwise_or_expression = 136,    /* bitwise_or_expression  */
  YYSYMBOL_bitwise_xor_expression = 137,   /* bitwise_xor_expression  */
  YYSYMBOL_bitwise_and_expression = 138,   /* bitwise_and_expression  */
  YYSYMBOL_equality_expression = 139,      /* equality_expression  */
  YYSYMBOL_relational_expression = 140,    /* relational_expression  */
  YYSYMBOL_shift_expression = 141,         /* shift_expression  */
  YYSYMBOL_additive_expression = 142,      /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 143, /* multiplicative_expression  */
  YYSYMBOL_unary_expression = 144,         /* unary_expression  */
  YYSYMBOL_postfix_expression = 145,       /* postfix_expression  */
  YYSYMBOL_primary_expression = 146,       /* primary_expression  */
  YYSYMBOL_comma_list = 147,               /* comma_list  */
  YYSYMBOL_assoc_list = 148,               /* assoc_list  */
  YYSYMBOL_literal = 149,                  /* literal  */
  YYSYMBOL_string_literal = 150,           /* string_literal  */
  YYSYMBOL_list_literal = 151,             /* list_literal  */
  YYSYMBOL_map_literal = 152,              /* map_literal  */
  YYSYMBOL_identifier = 153                /* identifier  */
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
#define YYLAST   777

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  112
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  149
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  301

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   365


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
     106,   107,   108,   109,   110,   111
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   236,   236,   237,   242,   243,   248,   249,   250,   251,
     256,   256,   257,   257,   262,   263,   268,   274,   275,   279,
     280,   281,   282,   283,   284,   285,   289,   290,   291,   295,
     296,   297,   298,   302,   303,   307,   308,   309,   310,   311,
     315,   319,   320,   321,   322,   326,   330,   334,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   358,   359,   363,   364,   368,
     369,   373,   374,   378,   379,   383,   384,   388,   389,   390,
     394,   395,   396,   397,   398,   402,   403,   404,   405,   409,
     410,   411,   415,   416,   417,   418,   419,   420,   424,   425,
     426,   427,   428,   429,   430,   434,   435,   436,   439,   440,
     441,   442,   446,   449,   450,   451,   455,   458,   464,   465,
     466,   470,   471,   472,   476,   477,   478,   479,   483,   487,
     494,   495,   496,   497,   498,   499,   500,   501,   502,   503,
     504,   505,   506,   510,   511,   515,   516,   520,   521,   525
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
  "TOKOP_FNARGS_INDEXING", "\"\\n\"", "\"module\"", "\"proc\"",
  "\"start\"", "\"end\"", "\"block\"", "\"if\"", "\"then\"", "\"elif\"",
  "\"else\"", "\"while\"", "\"break\"", "\"continue\"", "\"for\"",
  "\"from\"", "\"to\"", "\"by\"", "\"in\"", "\"do\"", "\"var\"",
  "\"const\"", "\"pass\"", "\"return\"", "\"weak\"", "\"<invalid>\"",
  "\"<boollit>\"", "\"<charlit>\"", "\"<binfloattlit>\"",
  "\"<octfloattlit>\"", "\"<decfloattlit>\"", "\"<hexfloattlit>\"",
  "\"<binintlit>\"", "\"<octintlit>\"", "\"<decintlit>\"",
  "\"<hexintlit>\"", "\"<strlit>\"", "\"<interpstrlit>\"",
  "\"<identifier>\"", "$accept", "nws", "nwp", "trm", "module", "$@1",
  "$@2", "program", "procedure", "statements", "statement", "assignment",
  "compound_statement", "if_block", "else_block", "while_block",
  "for_block", "block", "condition", "expression", "assignment_expression",
  "conditional_expression", "logical_or_expression",
  "logical_and_expression", "bitwise_or_expression",
  "bitwise_xor_expression", "bitwise_and_expression",
  "equality_expression", "relational_expression", "shift_expression",
  "additive_expression", "multiplicative_expression", "unary_expression",
  "postfix_expression", "primary_expression", "comma_list", "assoc_list",
  "literal", "string_literal", "list_literal", "map_literal", "identifier", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-263)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -64,   -97,    28,  -263,  -263,   -14,  -263,   -43,  -263,  -263,
      -6,   -97,  -263,  -263,  -263,  -263,   -36,   -43,     1,  -263,
     322,   666,   -12,   666,   666,   666,   666,   666,    22,    35,
     666,  -263,     1,   666,   666,   -14,   -14,   -97,   -97,   -97,
     -14,   540,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,
    -263,  -263,  -263,  -263,    29,   431,   -14,   -14,  -263,  -263,
    -263,  -263,  -263,  -263,    36,    46,   105,    57,    60,   109,
       4,    44,    31,    50,    52,   102,   446,  -263,  -263,  -263,
    -263,  -263,  -263,  -263,    26,   666,   666,  -263,  -263,   106,
    -263,  -263,  -263,  -263,  -263,   557,  -263,   -59,  -263,   322,
      41,    36,    37,    -6,    -6,   -22,    85,    87,    -6,    -6,
     -14,   -14,  -263,    -6,    -6,   666,   666,   666,   666,   666,
     666,   666,   666,   666,   666,   666,   666,   666,   666,   666,
     666,   666,   666,   666,   666,   666,   666,   666,   666,   666,
     114,   666,   666,  -263,   666,  -263,   666,   -97,   666,   666,
     -97,   -97,   666,   666,   666,   666,   666,   666,   666,   666,
     115,    76,  -263,  -263,   111,    77,    70,   107,   108,    63,
       1,     1,   -97,   666,   666,   666,   666,    -6,    -6,    55,
     105,    57,    60,   109,     4,    44,    44,    31,    31,    31,
      31,    50,    50,    50,    52,    52,  -263,  -263,  -263,  -263,
      56,  -263,  -263,  -263,  -263,   557,  -263,  -263,  -263,  -263,
    -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,  -263,    88,
    -263,  -263,  -263,  -263,  -263,  -263,    68,  -263,  -263,   666,
     666,  -263,   322,   322,    66,    58,    59,  -263,  -263,   666,
     131,  -263,   557,   133,   134,   -24,    78,   666,   666,     1,
    -263,  -263,  -263,  -263,    68,  -263,    68,  -263,   666,   -45,
    -263,  -263,    69,   -35,   322,   -59,   -59,    79,   666,   322,
       1,   666,     1,    84,  -263,  -263,     1,    82,    86,   322,
      73,   322,  -263,   322,     1,  -263,    89,     1,    90,    -5,
     322,  -263,   322,  -263,  -263,  -263,    15,    91,  -263,  -263,
    -263
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      10,     0,     0,    14,   149,     0,     1,    11,     7,     9,
      12,     0,    15,     6,     8,    14,     0,    13,     0,     4,
      17,     0,     0,     0,     0,     0,     0,     0,     2,     2,
       0,     5,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   143,   144,     0,    17,     0,     0,    29,    30,
      31,    32,    28,    47,    48,    65,    67,    69,    71,    73,
      75,    77,    80,    85,    89,    92,    98,   105,   118,   140,
     141,   142,   119,   101,    98,     0,     0,   111,   112,     0,
      99,   103,   100,   104,   145,     0,   147,     0,   102,    17,
       0,    46,     0,    20,    21,     0,     0,     0,    19,    23,
       0,     0,    18,    24,    25,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     0,     0,   113,     0,   114,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   120,     3,     2,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    22,    16,     0,
      68,    70,    72,    74,    76,    79,    78,    81,    83,    82,
      84,    87,    88,    86,    90,    91,    95,    93,    94,    97,
      96,    62,    51,    54,   106,     0,    63,    60,    58,    59,
     115,    64,    61,   117,   116,    56,    49,    57,    55,     0,
      53,    52,    50,   110,   109,     2,   121,   146,   148,     0,
       0,    45,    17,    17,     0,     0,     0,    26,    27,     0,
       0,   108,   122,     2,     2,     0,     0,     0,     0,     0,
      66,   107,   123,     2,   124,     2,   127,    33,     0,     0,
      34,    40,     0,     0,    17,   125,   128,     0,     0,    17,
       0,     0,     0,     0,   126,   129,     0,     0,     0,    17,
       0,    17,    43,    17,     0,    35,     0,     0,     0,     0,
      17,    44,    17,    41,    38,    39,     0,     0,    36,    37,
      42
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -263,    65,   -31,   -10,  -263,  -263,  -263,   151,  -263,   -32,
    -263,  -263,  -263,  -263,  -262,  -263,  -263,  -263,   -25,   -21,
     158,   -28,  -263,    54,    71,    72,    53,    67,    -9,   -20,
     -19,   -91,    -8,   152,  -263,  -198,  -151,  -263,   -85,  -263,
    -263,    -1
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    95,    20,    10,     2,     3,    15,     7,    12,    54,
      55,    56,    57,    58,   260,    59,    60,    61,   100,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,   165,   166,    78,    79,    80,
      81,    82
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       5,    99,    89,   172,    85,   101,   101,   240,   121,   102,
      16,     1,   167,    83,     4,   163,    90,    91,    92,    93,
     110,    88,    98,   112,     8,   103,   104,   295,     6,    19,
     108,   109,    13,    11,   299,   268,   105,   106,   107,   194,
     195,    18,   140,    86,   252,   200,   113,   114,   122,   143,
      52,    53,     4,   145,   257,   271,   147,   272,   258,   259,
       9,   132,   150,   151,   160,   161,   173,   169,    14,   174,
     133,   127,   130,   294,   164,    19,   131,   258,   259,    94,
     128,   156,   129,   123,   134,   135,   124,   101,   134,   135,
     179,   125,   126,   298,    97,    87,   168,   258,   259,     4,
     177,   178,    96,   187,   188,   189,   190,   111,   191,   192,
     193,   116,   185,   186,   274,   275,   115,   117,   119,   118,
     120,   136,   170,   162,   196,   197,   198,   199,   175,   171,
     176,   204,   223,   224,   227,   219,   225,   228,   239,   232,
     233,   231,   163,   229,   230,   241,   210,   248,   251,   213,
     214,   249,   235,   236,   237,   238,   261,   247,   253,   255,
     276,   270,   282,   284,   285,   287,    17,   291,   293,   300,
     180,   234,   183,    84,     0,     0,    84,    84,    84,    84,
     167,   167,    84,     0,   164,    84,    84,   184,   181,     0,
     182,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     245,   246,     0,     0,     0,   205,     0,     0,   243,   244,
       0,   250,     0,     0,     0,     0,     0,     0,   264,     0,
       0,   164,     0,     0,     0,     0,   262,   263,   269,   226,
     101,     0,   273,   267,     0,     0,     0,   278,     0,   279,
     101,   281,     0,   277,     0,   283,     0,   286,     0,   288,
     280,   289,     0,   290,     0,     0,   292,     0,   296,     0,
     297,     0,     0,     0,   168,   168,     0,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,     0,
     242,     0,     0,     0,     0,   201,   202,   203,     0,   206,
     207,     0,   208,     0,   209,     0,   211,   212,   254,   256,
     215,   216,   217,   218,     0,   220,   221,   222,   265,     0,
     266,     0,     0,     0,     0,    21,     0,     0,     0,     0,
      22,     0,     0,     0,     0,     0,     0,     0,    23,     0,
       0,     0,     0,     0,    24,    25,     0,     0,    26,    27,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    28,     0,     0,
       0,     0,     0,    29,     0,     0,     0,     0,     0,     0,
      30,    84,     0,     0,     0,     0,    31,     0,     0,     0,
       0,    32,    33,     0,     0,     0,    34,    35,    36,    37,
      84,     0,     0,     0,     0,    38,    39,    40,    41,     0,
      84,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,     4,    21,     0,     0,     0,     0,    22,
       0,     0,     0,     0,     0,     0,     0,    23,     0,     0,
       0,     0,     0,    24,    25,     0,   137,    26,    27,   138,
     139,     0,   140,     0,     0,     0,   141,   142,     0,   143,
     144,     0,     0,   145,   146,     0,   147,     0,     0,     0,
     148,   149,   150,   151,     0,     0,    28,   152,     0,   153,
       0,     0,    29,     0,     0,     0,   154,     0,   155,    30,
       0,   156,     0,     0,     0,   157,     0,     0,     0,   158,
      32,    33,   159,     0,     0,    34,    35,    36,    37,     0,
       0,     0,     0,     0,    38,    39,    40,    41,     0,     0,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,     4,    21,     0,     0,     0,     0,    22,     0,
       0,     0,     0,     0,     0,     0,    23,     0,     0,     0,
      21,     0,    24,    25,     0,    22,    26,    27,     0,     0,
       0,     0,     0,    23,     0,     0,     0,     0,     8,    24,
      25,     0,     0,    26,    27,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    28,     0,     0,     0,     0,
       0,    29,     0,     0,     0,     0,     0,     0,    30,     0,
       0,     0,    28,     0,     9,     0,     0,     0,    29,     0,
       0,     0,     0,     0,     0,    30,     0,     0,     0,     0,
       0,   163,     0,     0,     0,     0,     0,     0,     0,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,     4,     0,     0,     0,     0,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,     4,    21,
       0,     0,     0,     0,    22,     0,     0,     0,     0,     0,
       0,     0,    23,     0,     0,     0,     0,     0,    24,    25,
       0,     0,    26,    27,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    28,     0,     0,     0,     0,     0,    29,     0,     0,
       0,     0,     0,     0,    30,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,     4
};

static const yytype_int16 yycheck[] =
{
       1,    32,    23,    25,    16,    33,    34,   205,     4,    34,
      11,    75,    97,    21,   111,    74,    24,    25,    26,    27,
      41,    22,    30,    55,    38,    35,    36,   289,     0,    74,
      40,    41,    38,    76,   296,    80,    37,    38,    39,   130,
     131,    77,    16,    55,   242,   136,    56,    57,    44,    23,
     109,   110,   111,    27,    78,    90,    30,    92,    82,    83,
      74,     9,    36,    37,    85,    86,    88,    99,    74,    91,
      18,    40,    22,    78,    95,    74,    26,    82,    83,    57,
      49,    55,    51,    39,    32,    33,    42,   115,    32,    33,
     115,    47,    48,    78,    29,   107,    97,    82,    83,   111,
     110,   111,    67,   123,   124,   125,   126,    78,   127,   128,
     129,    65,   121,   122,   265,   266,    80,    12,    58,    62,
      11,    19,    81,    17,   132,   133,   134,   135,    43,    92,
      43,    17,    17,    57,    57,   156,    25,    67,    83,   170,
     171,    78,    74,    36,    36,    57,   147,    89,    17,   150,
     151,    92,   173,   174,   175,   176,    78,    91,    25,    25,
      81,    92,    78,    81,    78,    92,    15,    78,    78,    78,
     116,   172,   119,    21,    -1,    -1,    24,    25,    26,    27,
     265,   266,    30,    -1,   205,    33,    34,   120,   117,    -1,
     118,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     232,   233,    -1,    -1,    -1,   140,    -1,    -1,   229,   230,
      -1,   239,    -1,    -1,    -1,    -1,    -1,    -1,   249,    -1,
      -1,   242,    -1,    -1,    -1,    -1,   247,   248,   259,   164,
     258,    -1,   264,   258,    -1,    -1,    -1,   269,    -1,   270,
     268,   272,    -1,   268,    -1,   276,    -1,   279,    -1,   281,
     271,   283,    -1,   284,    -1,    -1,   287,    -1,   290,    -1,
     292,    -1,    -1,    -1,   265,   266,    -1,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,    -1,
     225,    -1,    -1,    -1,    -1,   137,   138,   139,    -1,   141,
     142,    -1,   144,    -1,   146,    -1,   148,   149,   243,   244,
     152,   153,   154,   155,    -1,   157,   158,   159,   253,    -1,
     255,    -1,    -1,    -1,    -1,     3,    -1,    -1,    -1,    -1,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,    -1,
      -1,    -1,    -1,    -1,    22,    23,    -1,    -1,    26,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      68,   239,    -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,
      -1,    79,    80,    -1,    -1,    -1,    84,    85,    86,    87,
     258,    -1,    -1,    -1,    -1,    93,    94,    95,    96,    -1,
     268,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,     3,    -1,    -1,    -1,    -1,     8,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,    -1,    -1,
      -1,    -1,    -1,    22,    23,    -1,    10,    26,    27,    13,
      14,    -1,    16,    -1,    -1,    -1,    20,    21,    -1,    23,
      24,    -1,    -1,    27,    28,    -1,    30,    -1,    -1,    -1,
      34,    35,    36,    37,    -1,    -1,    55,    41,    -1,    43,
      -1,    -1,    61,    -1,    -1,    -1,    50,    -1,    52,    68,
      -1,    55,    -1,    -1,    -1,    59,    -1,    -1,    -1,    63,
      79,    80,    66,    -1,    -1,    84,    85,    86,    87,    -1,
      -1,    -1,    -1,    -1,    93,    94,    95,    96,    -1,    -1,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,     3,    -1,    -1,    -1,    -1,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    16,    -1,    -1,    -1,
       3,    -1,    22,    23,    -1,     8,    26,    27,    -1,    -1,
      -1,    -1,    -1,    16,    -1,    -1,    -1,    -1,    38,    22,
      23,    -1,    -1,    26,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,
      -1,    -1,    55,    -1,    74,    -1,    -1,    -1,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,
      -1,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,    -1,    -1,    -1,    -1,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,     3,
      -1,    -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,    22,    23,
      -1,    -1,    26,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    75,   116,   117,   111,   153,     0,   119,    38,    74,
     115,    76,   120,    38,    74,   118,   153,   119,    77,    74,
     114,     3,     8,    16,    22,    23,    26,    27,    55,    61,
      68,    74,    79,    80,    84,    85,    86,    87,    93,    94,
      95,    96,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   121,   122,   123,   124,   125,   127,
     128,   129,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   149,   150,
     151,   152,   153,   144,   145,    16,    55,   107,   153,   131,
     144,   144,   144,   144,    57,   113,    67,   113,   144,   114,
     130,   133,   130,   115,   115,   153,   153,   153,   115,   115,
     131,    78,   121,   115,   115,    80,    65,    12,    62,    58,
      11,     4,    44,    39,    42,    47,    48,    40,    49,    51,
      22,    26,     9,    18,    32,    33,    19,    10,    13,    14,
      16,    20,    21,    23,    24,    27,    28,    30,    34,    35,
      36,    37,    41,    43,    50,    52,    55,    59,    63,    66,
     131,   131,    17,    74,   131,   147,   148,   150,   153,   121,
      81,    92,    25,    88,    91,    43,    43,   115,   115,   130,
     135,   136,   137,   138,   139,   140,   140,   141,   141,   141,
     141,   142,   142,   142,   143,   143,   144,   144,   144,   144,
     143,   132,   132,   132,    17,   113,   132,   132,   132,   132,
     153,   132,   132,   153,   153,   132,   132,   132,   132,   131,
     132,   132,   132,    17,    57,    25,   113,    57,    67,    36,
      36,    78,   114,   114,   153,   131,   131,   131,   131,    83,
     147,    57,   113,   131,   131,   121,   121,    91,    89,    92,
     133,    17,   147,    25,   113,    25,   113,    78,    82,    83,
     126,    78,   131,   131,   114,   113,   113,   130,    80,   114,
      92,    90,    92,   121,   148,   148,    81,   130,   121,   114,
     131,   114,    78,   114,    81,    78,   121,    92,   121,   121,
     114,    78,   114,    78,    78,   126,   121,   121,    78,   126,
      78
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   112,   113,   113,   114,   114,   115,   115,   115,   115,
     117,   116,   118,   116,   119,   119,   120,   121,   121,   122,
     122,   122,   122,   122,   122,   122,   123,   123,   123,   124,
     124,   124,   124,   125,   125,   126,   126,   126,   126,   126,
     127,   128,   128,   128,   128,   129,   130,   131,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   133,   133,   134,   134,   135,
     135,   136,   136,   137,   137,   138,   138,   139,   139,   139,
     140,   140,   140,   140,   140,   141,   141,   141,   141,   142,
     142,   142,   143,   143,   143,   143,   143,   143,   144,   144,
     144,   144,   144,   144,   144,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   146,   146,
     146,   147,   147,   147,   148,   148,   148,   148,   148,   148,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   150,   150,   151,   151,   152,   152,   153
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     2,     2,     1,     2,     1,
       0,     2,     0,     5,     0,     2,     7,     0,     2,     2,
       2,     2,     3,     2,     2,     2,     4,     4,     1,     1,
       1,     1,     1,     6,     6,     4,     7,     7,     6,     6,
       6,    10,    12,     8,    10,     4,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     5,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     3,     1,     2,
       2,     2,     2,     2,     2,     1,     3,     5,     4,     4,
       4,     2,     2,     2,     2,     3,     3,     3,     1,     1,
       3,     2,     3,     4,     4,     5,     6,     4,     5,     6,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     4,     2,     4,     1
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
#line 236 "src/parser.y"
               { (yyval.line_count) = 0; }
#line 1550 "src/parser.yy.c"
    break;

  case 3: /* nws: nws "\n"  */
#line 237 "src/parser.y"
               { (yyval.line_count) = (yyvsp[-1].line_count) + 1; }
#line 1556 "src/parser.yy.c"
    break;

  case 4: /* nwp: "\n"  */
#line 242 "src/parser.y"
               { (yyval.line_count) = 1; }
#line 1562 "src/parser.yy.c"
    break;

  case 5: /* nwp: nwp "\n"  */
#line 243 "src/parser.y"
               { (yyval.line_count) = (yyvsp[-1].line_count) + 1; }
#line 1568 "src/parser.yy.c"
    break;

  case 6: /* trm: trm ";"  */
#line 248 "src/parser.y"
               { (yyval.line_count) = (yyvsp[-1].line_count); }
#line 1574 "src/parser.yy.c"
    break;

  case 7: /* trm: ";"  */
#line 249 "src/parser.y"
               { (yyval.line_count) = 0; }
#line 1580 "src/parser.yy.c"
    break;

  case 8: /* trm: trm "\n"  */
#line 250 "src/parser.y"
               { (yyval.line_count) = (yyvsp[-1].line_count) + 1; }
#line 1586 "src/parser.yy.c"
    break;

  case 9: /* trm: "\n"  */
#line 251 "src/parser.y"
               { (yyval.line_count) = 1; }
#line 1592 "src/parser.yy.c"
    break;

  case 10: /* $@1: %empty  */
#line 256 "src/parser.y"
    { ast_ModuleStack_push(ast_Identifier(strdup("main"))); }
#line 1598 "src/parser.yy.c"
    break;

  case 11: /* module: $@1 program  */
#line 256 "src/parser.y"
                                                                      { ast_ModuleStack_pop(); }
#line 1604 "src/parser.yy.c"
    break;

  case 12: /* $@2: %empty  */
#line 257 "src/parser.y"
                              { ast_ModuleStack_push((yyvsp[-1].astnode_identifier)); }
#line 1610 "src/parser.yy.c"
    break;

  case 13: /* module: "module" identifier trm $@2 program  */
#line 257 "src/parser.y"
                                                                    { ast_ModuleStack_pop(); }
#line 1616 "src/parser.yy.c"
    break;

  case 16: /* procedure: "proc" identifier "start" nwp statements "end" trm  */
#line 268 "src/parser.y"
                                                             { ast_util_ModuleAndProcTable_add(ast_ModuleStack_top(), (yyvsp[-5].astnode_identifier), (yyvsp[-2].astnode_statements));
                                                                 ast_Identifier_destroy(&(yyvsp[-5].astnode_identifier));
                                                             }
#line 1624 "src/parser.yy.c"
    break;

  case 17: /* statements: %empty  */
#line 274 "src/parser.y"
                                                             { (yyval.astnode_statements) = NULL; }
#line 1630 "src/parser.yy.c"
    break;

  case 18: /* statements: statement statements  */
#line 275 "src/parser.y"
                                                             { (yyval.astnode_statements) = ast_Statements((yyvsp[0].astnode_statements), (yyvsp[-1].astnode_statement)); }
#line 1636 "src/parser.yy.c"
    break;

  case 19: /* statement: "pass" trm  */
#line 279 "src/parser.y"
                                                             { (yyval.astnode_statement) = ast_Statement_empty(lex_line_no - (yyvsp[0].line_count)); }
#line 1642 "src/parser.yy.c"
    break;

  case 20: /* statement: "break" trm  */
#line 280 "src/parser.y"
                                                             { (yyval.astnode_statement) = ast_Statement_break(lex_line_no - (yyvsp[0].line_count)); }
#line 1648 "src/parser.yy.c"
    break;

  case 21: /* statement: "continue" trm  */
#line 281 "src/parser.y"
                                                             { (yyval.astnode_statement) = ast_Statement_continue(lex_line_no - (yyvsp[0].line_count)); }
#line 1654 "src/parser.yy.c"
    break;

  case 22: /* statement: "return" expression trm  */
#line 282 "src/parser.y"
                                                             { (yyval.astnode_statement) = ast_Statement_return((yyvsp[-1].astnode_expression), lex_line_no - (yyvsp[0].line_count)); }
#line 1660 "src/parser.yy.c"
    break;

  case 23: /* statement: "return" trm  */
#line 283 "src/parser.y"
                                                             { (yyval.astnode_statement) = ast_Statement_return(NULL, lex_line_no - (yyvsp[0].line_count)); }
#line 1666 "src/parser.yy.c"
    break;

  case 24: /* statement: assignment trm  */
#line 284 "src/parser.y"
                                                             { (yyval.astnode_statement) = ast_Statement_Assignment((yyvsp[-1].astnode_assignment), lex_line_no - (yyvsp[0].line_count)); }
#line 1672 "src/parser.yy.c"
    break;

  case 25: /* statement: compound_statement trm  */
#line 285 "src/parser.y"
                                                             { (yyval.astnode_statement) = ast_Statement_CompoundSt((yyvsp[-1].astnode_compound_statement), lex_line_no - (yyvsp[0].line_count)); }
#line 1678 "src/parser.yy.c"
    break;

  case 26: /* assignment: "var" identifier "=" expression  */
#line 289 "src/parser.y"
                                                             { (yyval.astnode_assignment) = ast_Assignment_create((yyvsp[-2].astnode_identifier), (yyvsp[0].astnode_expression)); }
#line 1684 "src/parser.yy.c"
    break;

  case 27: /* assignment: "const" identifier "=" expression  */
#line 290 "src/parser.y"
                                                             { (yyval.astnode_assignment) = ast_Assignment_mkconst((yyvsp[-2].astnode_identifier), (yyvsp[0].astnode_expression)); }
#line 1690 "src/parser.yy.c"
    break;

  case 28: /* assignment: expression  */
#line 291 "src/parser.y"
                                                             { (yyval.astnode_assignment) = ast_Assignment_tovoid((yyvsp[0].astnode_expression)); }
#line 1696 "src/parser.yy.c"
    break;

  case 29: /* compound_statement: if_block  */
#line 295 "src/parser.y"
                                                             { (yyval.astnode_compound_statement) = ast_CompoundSt_IfBlock((yyvsp[0].astnode_if_block)); }
#line 1702 "src/parser.yy.c"
    break;

  case 30: /* compound_statement: while_block  */
#line 296 "src/parser.y"
                                                             { (yyval.astnode_compound_statement) = ast_CompoundSt_WhileBlock((yyvsp[0].astnode_while_block)); }
#line 1708 "src/parser.yy.c"
    break;

  case 31: /* compound_statement: for_block  */
#line 297 "src/parser.y"
                                                             { (yyval.astnode_compound_statement) = ast_CompoundSt_ForBlock((yyvsp[0].astnode_for_block)); }
#line 1714 "src/parser.yy.c"
    break;

  case 32: /* compound_statement: block  */
#line 298 "src/parser.y"
                                                             { (yyval.astnode_compound_statement) = ast_CompoundSt_Block((yyvsp[0].astnode_block)); }
#line 1720 "src/parser.yy.c"
    break;

  case 33: /* if_block: "if" condition "then" nwp statements "end"  */
#line 302 "src/parser.y"
                                                             { (yyval.astnode_if_block) = ast_IfBlock((yyvsp[-4].astnode_expression), (yyvsp[-1].astnode_statements), NULL); }
#line 1726 "src/parser.yy.c"
    break;

  case 34: /* if_block: "if" condition "then" nwp statements else_block  */
#line 303 "src/parser.y"
                                                             { (yyval.astnode_if_block) = ast_IfBlock((yyvsp[-4].astnode_expression), (yyvsp[-1].astnode_statements), (yyvsp[0].astnode_else_block)); }
#line 1732 "src/parser.yy.c"
    break;

  case 35: /* else_block: "else" nwp statements "end"  */
#line 307 "src/parser.y"
                                                             { (yyval.astnode_else_block) = ast_ElseBlock(NULL, (yyvsp[-1].astnode_statements), NULL); }
#line 1738 "src/parser.yy.c"
    break;

  case 36: /* else_block: "else" "if" condition "then" nwp statements "end"  */
#line 308 "src/parser.y"
                                                             { (yyval.astnode_else_block) = ast_ElseBlock((yyvsp[-4].astnode_expression), (yyvsp[-1].astnode_statements), NULL); }
#line 1744 "src/parser.yy.c"
    break;

  case 37: /* else_block: "else" "if" condition "then" nwp statements else_block  */
#line 309 "src/parser.y"
                                                             { (yyval.astnode_else_block) = ast_ElseBlock((yyvsp[-4].astnode_expression), (yyvsp[-1].astnode_statements), (yyvsp[0].astnode_else_block)); }
#line 1750 "src/parser.yy.c"
    break;

  case 38: /* else_block: "elif" condition "then" nwp statements "end"  */
#line 310 "src/parser.y"
                                                             { (yyval.astnode_else_block) = ast_ElseBlock((yyvsp[-4].astnode_expression), (yyvsp[-1].astnode_statements), NULL); }
#line 1756 "src/parser.yy.c"
    break;

  case 39: /* else_block: "elif" condition "then" nwp statements else_block  */
#line 311 "src/parser.y"
                                                             { (yyval.astnode_else_block) = ast_ElseBlock((yyvsp[-4].astnode_expression), (yyvsp[-1].astnode_statements), (yyvsp[0].astnode_else_block)); }
#line 1762 "src/parser.yy.c"
    break;

  case 40: /* while_block: "while" condition "do" nwp statements "end"  */
#line 315 "src/parser.y"
                                                             { (yyval.astnode_while_block) = ast_WhileBlock((yyvsp[-4].astnode_expression), (yyvsp[-1].astnode_statements)); }
#line 1768 "src/parser.yy.c"
    break;

  case 41: /* for_block: "for" identifier "from" expression "to" expression "do" nwp statements "end"  */
#line 319 "src/parser.y"
                                                                                                   { (yyval.astnode_for_block) = ast_ForBlock((yyvsp[-8].astnode_identifier), (yyvsp[-6].astnode_expression), (yyvsp[-4].astnode_expression), NULL, (yyvsp[-1].astnode_statements)); }
#line 1774 "src/parser.yy.c"
    break;

  case 42: /* for_block: "for" identifier "from" expression "to" expression "by" expression "do" nwp statements "end"  */
#line 320 "src/parser.y"
                                                                                                   { (yyval.astnode_for_block) = ast_ForBlock((yyvsp[-10].astnode_identifier), (yyvsp[-8].astnode_expression), (yyvsp[-6].astnode_expression), (yyvsp[-4].astnode_expression), (yyvsp[-1].astnode_statements)); }
#line 1780 "src/parser.yy.c"
    break;

  case 43: /* for_block: "for" identifier "in" expression "do" nwp statements "end"  */
#line 321 "src/parser.y"
                                                                                                   { (yyval.astnode_for_block) = ast_ForBlock_iterate(NULL, (yyvsp[-6].astnode_identifier), (yyvsp[-4].astnode_expression), (yyvsp[-1].astnode_statements)); }
#line 1786 "src/parser.yy.c"
    break;

  case 44: /* for_block: "for" identifier "," identifier "in" expression "do" nwp statements "end"  */
#line 322 "src/parser.y"
                                                                                                   { (yyval.astnode_for_block) = ast_ForBlock_iterate((yyvsp[-8].astnode_identifier), (yyvsp[-6].astnode_identifier), (yyvsp[-4].astnode_expression), (yyvsp[-1].astnode_statements)); }
#line 1792 "src/parser.yy.c"
    break;

  case 45: /* block: "block" nwp statements "end"  */
#line 326 "src/parser.y"
                                                             { (yyval.astnode_block) = ast_Block((yyvsp[-1].astnode_statements)); }
#line 1798 "src/parser.yy.c"
    break;

  case 46: /* condition: conditional_expression  */
#line 330 "src/parser.y"
                                                             { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 1804 "src/parser.yy.c"
    break;

  case 47: /* expression: assignment_expression  */
#line 334 "src/parser.y"
                                                             { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 1810 "src/parser.yy.c"
    break;

  case 48: /* assignment_expression: conditional_expression  */
#line 338 "src/parser.y"
                                                             { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 1816 "src/parser.yy.c"
    break;

  case 49: /* assignment_expression: postfix_expression "=" assignment_expression  */
#line 339 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1822 "src/parser.yy.c"
    break;

  case 50: /* assignment_expression: postfix_expression "||=" assignment_expression  */
#line 340 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1828 "src/parser.yy.c"
    break;

  case 51: /* assignment_expression: postfix_expression "&&=" assignment_expression  */
#line 341 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1834 "src/parser.yy.c"
    break;

  case 52: /* assignment_expression: postfix_expression "|=" assignment_expression  */
#line 342 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1840 "src/parser.yy.c"
    break;

  case 53: /* assignment_expression: postfix_expression "^=" assignment_expression  */
#line 343 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1846 "src/parser.yy.c"
    break;

  case 54: /* assignment_expression: postfix_expression "&=" assignment_expression  */
#line 344 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1852 "src/parser.yy.c"
    break;

  case 55: /* assignment_expression: postfix_expression ">>>=" assignment_expression  */
#line 345 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1858 "src/parser.yy.c"
    break;

  case 56: /* assignment_expression: postfix_expression "<<=" assignment_expression  */
#line 346 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1864 "src/parser.yy.c"
    break;

  case 57: /* assignment_expression: postfix_expression ">>=" assignment_expression  */
#line 347 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1870 "src/parser.yy.c"
    break;

  case 58: /* assignment_expression: postfix_expression "+=" assignment_expression  */
#line 348 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1876 "src/parser.yy.c"
    break;

  case 59: /* assignment_expression: postfix_expression "-=" assignment_expression  */
#line 349 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1882 "src/parser.yy.c"
    break;

  case 60: /* assignment_expression: postfix_expression "*=" assignment_expression  */
#line 350 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1888 "src/parser.yy.c"
    break;

  case 61: /* assignment_expression: postfix_expression "/=" assignment_expression  */
#line 351 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1894 "src/parser.yy.c"
    break;

  case 62: /* assignment_expression: postfix_expression "%=" assignment_expression  */
#line 352 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1900 "src/parser.yy.c"
    break;

  case 63: /* assignment_expression: postfix_expression "**=" assignment_expression  */
#line 353 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1906 "src/parser.yy.c"
    break;

  case 64: /* assignment_expression: postfix_expression "//=" assignment_expression  */
#line 354 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1912 "src/parser.yy.c"
    break;

  case 65: /* conditional_expression: logical_or_expression  */
#line 358 "src/parser.y"
                                                             { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 1918 "src/parser.yy.c"
    break;

  case 66: /* conditional_expression: conditional_expression "if" condition "else" conditional_expression  */
#line 359 "src/parser.y"
                                                                          { (yyval.astnode_expression) = ast_Expression(TOKOP_TERNARY_COND, (yyvsp[-4].astnode_expression), (yyvsp[0].astnode_expression), (yyvsp[-2].astnode_expression)); }
#line 1924 "src/parser.yy.c"
    break;

  case 67: /* logical_or_expression: logical_and_expression  */
#line 363 "src/parser.y"
                                                             { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 1930 "src/parser.yy.c"
    break;

  case 68: /* logical_or_expression: logical_or_expression "||" logical_and_expression  */
#line 364 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1936 "src/parser.yy.c"
    break;

  case 69: /* logical_and_expression: bitwise_or_expression  */
#line 368 "src/parser.y"
                                                             { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 1942 "src/parser.yy.c"
    break;

  case 70: /* logical_and_expression: logical_and_expression "&&" bitwise_or_expression  */
#line 369 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1948 "src/parser.yy.c"
    break;

  case 71: /* bitwise_or_expression: bitwise_xor_expression  */
#line 373 "src/parser.y"
                                                             { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 1954 "src/parser.yy.c"
    break;

  case 72: /* bitwise_or_expression: bitwise_or_expression "|" bitwise_xor_expression  */
#line 374 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1960 "src/parser.yy.c"
    break;

  case 73: /* bitwise_xor_expression: bitwise_and_expression  */
#line 378 "src/parser.y"
                                                             { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 1966 "src/parser.yy.c"
    break;

  case 74: /* bitwise_xor_expression: bitwise_xor_expression "^" bitwise_and_expression  */
#line 379 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1972 "src/parser.yy.c"
    break;

  case 75: /* bitwise_and_expression: equality_expression  */
#line 383 "src/parser.y"
                                                             { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 1978 "src/parser.yy.c"
    break;

  case 76: /* bitwise_and_expression: bitwise_and_expression "&" equality_expression  */
#line 384 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1984 "src/parser.yy.c"
    break;

  case 77: /* equality_expression: relational_expression  */
#line 388 "src/parser.y"
                                                             { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 1990 "src/parser.yy.c"
    break;

  case 78: /* equality_expression: equality_expression "==" relational_expression  */
#line 389 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 1996 "src/parser.yy.c"
    break;

  case 79: /* equality_expression: equality_expression "!=" relational_expression  */
#line 390 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2002 "src/parser.yy.c"
    break;

  case 80: /* relational_expression: shift_expression  */
#line 394 "src/parser.y"
                                                             { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 2008 "src/parser.yy.c"
    break;

  case 81: /* relational_expression: relational_expression "<" shift_expression  */
#line 395 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2014 "src/parser.yy.c"
    break;

  case 82: /* relational_expression: relational_expression ">" shift_expression  */
#line 396 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2020 "src/parser.yy.c"
    break;

  case 83: /* relational_expression: relational_expression "<=" shift_expression  */
#line 397 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2026 "src/parser.yy.c"
    break;

  case 84: /* relational_expression: relational_expression ">=" shift_expression  */
#line 398 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2032 "src/parser.yy.c"
    break;

  case 85: /* shift_expression: additive_expression  */
#line 402 "src/parser.y"
                                                             { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 2038 "src/parser.yy.c"
    break;

  case 86: /* shift_expression: shift_expression ">>>" additive_expression  */
#line 403 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2044 "src/parser.yy.c"
    break;

  case 87: /* shift_expression: shift_expression "<<" additive_expression  */
#line 404 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2050 "src/parser.yy.c"
    break;

  case 88: /* shift_expression: shift_expression ">>" additive_expression  */
#line 405 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2056 "src/parser.yy.c"
    break;

  case 89: /* additive_expression: multiplicative_expression  */
#line 409 "src/parser.y"
                                                             { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 2062 "src/parser.yy.c"
    break;

  case 90: /* additive_expression: additive_expression "+" multiplicative_expression  */
#line 410 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2068 "src/parser.yy.c"
    break;

  case 91: /* additive_expression: additive_expression "-" multiplicative_expression  */
#line 411 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2074 "src/parser.yy.c"
    break;

  case 92: /* multiplicative_expression: unary_expression  */
#line 415 "src/parser.y"
                                                             { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 2080 "src/parser.yy.c"
    break;

  case 93: /* multiplicative_expression: multiplicative_expression "*" unary_expression  */
#line 416 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2086 "src/parser.yy.c"
    break;

  case 94: /* multiplicative_expression: multiplicative_expression "/" unary_expression  */
#line 417 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2092 "src/parser.yy.c"
    break;

  case 95: /* multiplicative_expression: multiplicative_expression "%" unary_expression  */
#line 418 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2098 "src/parser.yy.c"
    break;

  case 96: /* multiplicative_expression: unary_expression "**" multiplicative_expression  */
#line 419 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2104 "src/parser.yy.c"
    break;

  case 97: /* multiplicative_expression: multiplicative_expression "//" unary_expression  */
#line 420 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), (yyvsp[0].astnode_expression), NULL); }
#line 2110 "src/parser.yy.c"
    break;

  case 98: /* unary_expression: postfix_expression  */
#line 424 "src/parser.y"
                                                             { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 2116 "src/parser.yy.c"
    break;

  case 99: /* unary_expression: "+" unary_expression  */
#line 425 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), NULL, (yyvsp[0].astnode_expression), NULL); }
#line 2122 "src/parser.yy.c"
    break;

  case 100: /* unary_expression: "-" unary_expression  */
#line 426 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), NULL, (yyvsp[0].astnode_expression), NULL); }
#line 2128 "src/parser.yy.c"
    break;

  case 101: /* unary_expression: "!" unary_expression  */
#line 427 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), NULL, (yyvsp[0].astnode_expression), NULL); }
#line 2134 "src/parser.yy.c"
    break;

  case 102: /* unary_expression: "~" unary_expression  */
#line 428 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), NULL, (yyvsp[0].astnode_expression), NULL); }
#line 2140 "src/parser.yy.c"
    break;

  case 103: /* unary_expression: "++" unary_expression  */
#line 429 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), NULL, (yyvsp[0].astnode_expression), NULL); }
#line 2146 "src/parser.yy.c"
    break;

  case 104: /* unary_expression: "--" unary_expression  */
#line 430 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), NULL, (yyvsp[0].astnode_expression), NULL); }
#line 2152 "src/parser.yy.c"
    break;

  case 105: /* postfix_expression: primary_expression  */
#line 434 "src/parser.y"
                                                             { (yyval.astnode_expression) = (yyvsp[0].astnode_expression); }
#line 2158 "src/parser.yy.c"
    break;

  case 106: /* postfix_expression: postfix_expression "(" ")"  */
#line 435 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression(TOKOP_FNCALL, (yyvsp[-2].astnode_expression), NULL, NULL); }
#line 2164 "src/parser.yy.c"
    break;

  case 107: /* postfix_expression: postfix_expression "(" nws comma_list ")"  */
#line 436 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression(TOKOP_FNCALL, (yyvsp[-4].astnode_expression),
                                                                 ast_Expression_CommaSepList((yyvsp[-1].astnode_comma_list)), NULL);
                                                             }
#line 2172 "src/parser.yy.c"
    break;

  case 108: /* postfix_expression: postfix_expression "[" expression "]"  */
#line 439 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression(TOKOP_INDEXING, (yyvsp[-3].astnode_expression), (yyvsp[-1].astnode_expression), NULL); }
#line 2178 "src/parser.yy.c"
    break;

  case 109: /* postfix_expression: "$" "[" expression "]"  */
#line 440 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression(TOKOP_FNARGS_INDEXING, NULL, (yyvsp[-1].astnode_expression), NULL); }
#line 2184 "src/parser.yy.c"
    break;

  case 110: /* postfix_expression: "$" "(" expression ")"  */
#line 441 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression(TOKOP_FNARGS_INDEXING, NULL, (yyvsp[-1].astnode_expression), NULL); }
#line 2190 "src/parser.yy.c"
    break;

  case 111: /* postfix_expression: "$" "<decintlit>"  */
#line 442 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression(TOKOP_FNARGS_INDEXING, NULL,
                                                                 ast_Expression_Literal(
                                                                     ast_Literal_i64((yyvsp[0].literal_i64))), NULL);
                                                             }
#line 2199 "src/parser.yy.c"
    break;

  case 112: /* postfix_expression: "$" identifier  */
#line 446 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression(TOKOP_FNARGS_INDEXING, NULL,
                                                                 ast_Expression_Identifier((yyvsp[0].astnode_identifier)), NULL);
                                                             }
#line 2207 "src/parser.yy.c"
    break;

  case 113: /* postfix_expression: postfix_expression "++"  */
#line 449 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[0].tok), (yyvsp[-1].astnode_expression), NULL, NULL); }
#line 2213 "src/parser.yy.c"
    break;

  case 114: /* postfix_expression: postfix_expression "--"  */
#line 450 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[0].tok), (yyvsp[-1].astnode_expression), NULL, NULL); }
#line 2219 "src/parser.yy.c"
    break;

  case 115: /* postfix_expression: postfix_expression "." identifier  */
#line 451 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression), ast_Expression_Literal(
                                                                     ast_Literal_str(strdup((yyvsp[0].astnode_identifier)->identifier_name))), NULL);
                                                                 ast_Identifier_destroy(&(yyvsp[0].astnode_identifier));
                                                             }
#line 2228 "src/parser.yy.c"
    break;

  case 116: /* postfix_expression: postfix_expression "::" identifier  */
#line 455 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression((yyvsp[-1].tok), (yyvsp[-2].astnode_expression),
                                                                 ast_Expression_Identifier((yyvsp[0].astnode_identifier)), NULL);
                                                             }
#line 2236 "src/parser.yy.c"
    break;

  case 117: /* postfix_expression: postfix_expression ":" identifier  */
#line 458 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression(TOKEN_DCOLON, (yyvsp[-2].astnode_expression),
                                                                 ast_Expression_Identifier((yyvsp[0].astnode_identifier)), NULL);
                                                             }
#line 2244 "src/parser.yy.c"
    break;

  case 118: /* primary_expression: literal  */
#line 464 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression_Literal((yyvsp[0].astnode_literal)); }
#line 2250 "src/parser.yy.c"
    break;

  case 119: /* primary_expression: identifier  */
#line 465 "src/parser.y"
                                                             { (yyval.astnode_expression) = ast_Expression_Identifier((yyvsp[0].astnode_identifier)); }
#line 2256 "src/parser.yy.c"
    break;

  case 120: /* primary_expression: "(" expression ")"  */
#line 466 "src/parser.y"
                                                             { (yyval.astnode_expression) = (yyvsp[-1].astnode_expression); }
#line 2262 "src/parser.yy.c"
    break;

  case 121: /* comma_list: expression nws  */
#line 470 "src/parser.y"
                                                             { (yyval.astnode_comma_list) = ast_CommaSepList(NULL, (yyvsp[-1].astnode_expression)); }
#line 2268 "src/parser.yy.c"
    break;

  case 122: /* comma_list: expression "," nws  */
#line 471 "src/parser.y"
                                                             { (yyval.astnode_comma_list) = ast_CommaSepList(NULL, (yyvsp[-2].astnode_expression)); }
#line 2274 "src/parser.yy.c"
    break;

  case 123: /* comma_list: expression "," nws comma_list  */
#line 472 "src/parser.y"
                                                             { (yyval.astnode_comma_list) = ast_CommaSepList((yyvsp[0].astnode_comma_list), (yyvsp[-3].astnode_expression)); }
#line 2280 "src/parser.yy.c"
    break;

  case 124: /* assoc_list: string_literal ":" expression nws  */
#line 476 "src/parser.y"
                                                             { (yyval.astnode_assoc_list) = ast_AssociativeList(NULL, (yyvsp[-3].astnode_literal), (yyvsp[-1].astnode_expression)); }
#line 2286 "src/parser.yy.c"
    break;

  case 125: /* assoc_list: string_literal ":" expression "," nws  */
#line 477 "src/parser.y"
                                                             { (yyval.astnode_assoc_list) = ast_AssociativeList(NULL, (yyvsp[-4].astnode_literal), (yyvsp[-2].astnode_expression)); }
#line 2292 "src/parser.yy.c"
    break;

  case 126: /* assoc_list: string_literal ":" expression "," nws assoc_list  */
#line 478 "src/parser.y"
                                                             { (yyval.astnode_assoc_list) = ast_AssociativeList((yyvsp[0].astnode_assoc_list), (yyvsp[-5].astnode_literal), (yyvsp[-3].astnode_expression)); }
#line 2298 "src/parser.yy.c"
    break;

  case 127: /* assoc_list: identifier ":" expression nws  */
#line 479 "src/parser.y"
                                                             { (yyval.astnode_assoc_list) = ast_AssociativeList(NULL,
                                                                     ast_Literal_str(strdup((yyvsp[-3].astnode_identifier)->identifier_name)), (yyvsp[-1].astnode_expression));
                                                                 ast_Identifier_destroy(&(yyvsp[-3].astnode_identifier));
                                                             }
#line 2307 "src/parser.yy.c"
    break;

  case 128: /* assoc_list: identifier ":" expression "," nws  */
#line 483 "src/parser.y"
                                                             { (yyval.astnode_assoc_list) = ast_AssociativeList(NULL,
                                                                     ast_Literal_str(strdup((yyvsp[-4].astnode_identifier)->identifier_name)), (yyvsp[-2].astnode_expression));
                                                                 ast_Identifier_destroy(&(yyvsp[-4].astnode_identifier));
                                                             }
#line 2316 "src/parser.yy.c"
    break;

  case 129: /* assoc_list: identifier ":" expression "," nws assoc_list  */
#line 487 "src/parser.y"
                                                             { (yyval.astnode_assoc_list) = ast_AssociativeList((yyvsp[0].astnode_assoc_list),
                                                                     ast_Literal_str(strdup((yyvsp[-5].astnode_identifier)->identifier_name)), (yyvsp[-3].astnode_expression));
                                                                 ast_Identifier_destroy(&(yyvsp[-5].astnode_identifier));
                                                             }
#line 2325 "src/parser.yy.c"
    break;

  case 130: /* literal: "<boollit>"  */
#line 494 "src/parser.y"
                                                             { (yyval.astnode_literal) = ast_Literal_bul((yyvsp[0].literal_bool)); }
#line 2331 "src/parser.yy.c"
    break;

  case 131: /* literal: "<charlit>"  */
#line 495 "src/parser.y"
                                                             { (yyval.astnode_literal) = ast_Literal_chr((yyvsp[0].literal_char)); }
#line 2337 "src/parser.yy.c"
    break;

  case 132: /* literal: "<binfloattlit>"  */
#line 496 "src/parser.y"
                                                             { (yyval.astnode_literal) = ast_Literal_f64((yyvsp[0].literal_f64)); }
#line 2343 "src/parser.yy.c"
    break;

  case 133: /* literal: "<octfloattlit>"  */
#line 497 "src/parser.y"
                                                             { (yyval.astnode_literal) = ast_Literal_f64((yyvsp[0].literal_f64)); }
#line 2349 "src/parser.yy.c"
    break;

  case 134: /* literal: "<decfloattlit>"  */
#line 498 "src/parser.y"
                                                             { (yyval.astnode_literal) = ast_Literal_f64((yyvsp[0].literal_f64)); }
#line 2355 "src/parser.yy.c"
    break;

  case 135: /* literal: "<hexfloattlit>"  */
#line 499 "src/parser.y"
                                                             { (yyval.astnode_literal) = ast_Literal_f64((yyvsp[0].literal_f64)); }
#line 2361 "src/parser.yy.c"
    break;

  case 136: /* literal: "<binintlit>"  */
#line 500 "src/parser.y"
                                                             { (yyval.astnode_literal) = ast_Literal_i64((yyvsp[0].literal_i64)); }
#line 2367 "src/parser.yy.c"
    break;

  case 137: /* literal: "<octintlit>"  */
#line 501 "src/parser.y"
                                                             { (yyval.astnode_literal) = ast_Literal_i64((yyvsp[0].literal_i64)); }
#line 2373 "src/parser.yy.c"
    break;

  case 138: /* literal: "<decintlit>"  */
#line 502 "src/parser.y"
                                                             { (yyval.astnode_literal) = ast_Literal_i64((yyvsp[0].literal_i64)); }
#line 2379 "src/parser.yy.c"
    break;

  case 139: /* literal: "<hexintlit>"  */
#line 503 "src/parser.y"
                                                             { (yyval.astnode_literal) = ast_Literal_i64((yyvsp[0].literal_i64)); }
#line 2385 "src/parser.yy.c"
    break;

  case 140: /* literal: string_literal  */
#line 504 "src/parser.y"
                                                             { (yyval.astnode_literal) = (yyvsp[0].astnode_literal); }
#line 2391 "src/parser.yy.c"
    break;

  case 141: /* literal: list_literal  */
#line 505 "src/parser.y"
                                                             { (yyval.astnode_literal) = (yyvsp[0].astnode_literal); }
#line 2397 "src/parser.yy.c"
    break;

  case 142: /* literal: map_literal  */
#line 506 "src/parser.y"
                                                             { (yyval.astnode_literal) = (yyvsp[0].astnode_literal); }
#line 2403 "src/parser.yy.c"
    break;

  case 143: /* string_literal: "<strlit>"  */
#line 510 "src/parser.y"
                                                             { (yyval.astnode_literal) = ast_Literal_str((yyvsp[0].literal_str)); }
#line 2409 "src/parser.yy.c"
    break;

  case 144: /* string_literal: "<interpstrlit>"  */
#line 511 "src/parser.y"
                                                             { (yyval.astnode_literal) = ast_Literal_interp_str((yyvsp[0].literal_str)); }
#line 2415 "src/parser.yy.c"
    break;

  case 145: /* list_literal: "[" "]"  */
#line 515 "src/parser.y"
                                                             { (yyval.astnode_literal) = ast_Literal_lst(NULL); }
#line 2421 "src/parser.yy.c"
    break;

  case 146: /* list_literal: "[" nws comma_list "]"  */
#line 516 "src/parser.y"
                                                             { (yyval.astnode_literal) = ast_Literal_lst((yyvsp[-1].astnode_comma_list)); }
#line 2427 "src/parser.yy.c"
    break;

  case 147: /* map_literal: "{" "}"  */
#line 520 "src/parser.y"
                                                             { (yyval.astnode_literal) = ast_Literal_map(NULL); }
#line 2433 "src/parser.yy.c"
    break;

  case 148: /* map_literal: "{" nws assoc_list "}"  */
#line 521 "src/parser.y"
                                                             { (yyval.astnode_literal) = ast_Literal_map((yyvsp[-1].astnode_assoc_list)); }
#line 2439 "src/parser.yy.c"
    break;

  case 149: /* identifier: "<identifier>"  */
#line 525 "src/parser.y"
                                                             { (yyval.astnode_identifier) = ast_Identifier((yyvsp[0].identifier_name)); }
#line 2445 "src/parser.yy.c"
    break;


#line 2449 "src/parser.yy.c"

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

#line 528 "src/parser.y"


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
