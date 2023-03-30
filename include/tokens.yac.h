/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_INCLUDE_TOKENS_YAC_H_INCLUDED
# define YY_YY_INCLUDE_TOKENS_YAC_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    LEXTOK_BANG = 258,             /* "!"  */
    LEXTOK_LOGICAL_UNEQUAL = 259,  /* "!="  */
    LEXTOK_LOGICAL_UNIDENTICAL = 260, /* "!=="  */
    LEXTOK_DQUOTE = 261,           /* "\""  */
    LEXTOK_DOLLAR = 262,           /* "$"  */
    LEXTOK_PERCENT = 263,          /* "%"  */
    LEXTOK_MODULO_ASSIGN = 264,    /* "%="  */
    LEXTOK_AMPERSAND = 265,        /* "&"  */
    LEXTOK_LOGICAL_AND = 266,      /* "&&"  */
    LEXTOK_LOGICAL_AND_ASSIGN = 267, /* "&&="  */
    LEXTOK_BITWISE_AND_ASSIGN = 268, /* "&="  */
    LEXTOK_SQUOTE = 269,           /* "'"  */
    LEXTOK_LBRACE_PAREN = 270,     /* "("  */
    LEXTOK_RBRACE_PAREN = 271,     /* ")"  */
    LEXTOK_ASTERIX = 272,          /* "*"  */
    LEXTOK_EXPONENT = 273,         /* "**"  */
    LEXTOK_EXPONENT_ASSIGN = 274,  /* "**="  */
    LEXTOK_MULTIPLY_ASSIGN = 275,  /* "*="  */
    LEXTOK_PLUS = 276,             /* "+"  */
    LEXTOK_INCREMENT = 277,        /* "++"  */
    LEXTOK_ADD_ASSIGN = 278,       /* "+="  */
    LEXTOK_COMMA = 279,            /* ""  */
    LEXTOK_MINUS = 280,            /* "-"  */
    LEXTOK_DECREMENT = 281,        /* "--"  */
    LEXTOK_SUBSTRACT_ASSIGN = 282, /* "-="  */
    LEXTOK_SARROW = 283,           /* "->"  */
    LEXTOK_DOT = 284,              /* "."  */
    LEXTOK_ELIPSIS = 285,          /* "..."  */
    LEXTOK_FSLASH = 286,           /* "/"  */
    LEXTOK_FLOOR_DIVIDE = 287,     /* "//"  */
    LEXTOK_FLOOR_DIVIDE_ASSIGN = 288, /* "//="  */
    LEXTOK_DIVIDE_ASSIGN = 289,    /* "/="  */
    LEXTOK_COLON = 290,            /* ":"  */
    LEXTOK_DCOLON = 291,           /* "::"  */
    LEXTOK_SEMICOLON = 292,        /* ";"  */
    LEXTOK_LBRACE_ANGULAR = 293,   /* "<"  */
    LEXTOK_BITWISE_LSHIFT = 294,   /* "<<"  */
    LEXTOK_BITWISE_LSHIFT_ASSIGN = 295, /* "<<="  */
    LEXTOK_LOGICAL_LESSER_EQUAL = 296, /* "<="  */
    LEXTOK_ASSIGN = 297,           /* "="  */
    LEXTOK_LOGICAL_EQUAL = 298,    /* "=="  */
    LEXTOK_LOGICAL_IDENTICAL = 299, /* "==="  */
    LEXTOK_DARROW = 300,           /* "=>"  */
    LEXTOK_RBRACE_ANGULAR = 301,   /* ">"  */
    LEXTOK_LOGICAL_GREATER_EQUAL = 302, /* ">="  */
    LEXTOK_BITWISE_RSHIFT = 303,   /* ">>"  */
    LEXTOK_BITWISE_RSHIFT_ASSIGN = 304, /* ">>="  */
    LEXTOK_ARITH_RSHIFT = 305,     /* ">>>"  */
    LEXTOK_ARITH_RSHIFT_ASSIGN = 306, /* ">>>="  */
    LEXTOK_QUESTION = 307,         /* "?"  */
    LEXTOK_AT = 308,               /* "@"  */
    LEXTOK_LBRACE_SQUARE = 309,    /* "["  */
    LEXTOK_BSLASH = 310,           /* "\\"  */
    LEXTOK_RBRACE_SQUARE = 311,    /* "]"  */
    LEXTOK_CARET = 312,            /* "^"  */
    LEXTOK_BITWISE_XOR_ASSIGN = 313, /* "^="  */
    LEXTOK_BACKTICK = 314,         /* "`"  */
    LEXTOK_LBRACE_CURLY = 315,     /* "{"  */
    LEXTOK_PIPE = 316,             /* "|"  */
    LEXTOK_BITWISE_OR_ASSIGN = 317, /* "|="  */
    LEXTOK_PIPEOUT = 318,          /* "|>"  */
    LEXTOK_LOGICAL_OR = 319,       /* "||"  */
    LEXTOK_LOGICAL_OR_ASSIGN = 320, /* "||="  */
    LEXTOK_RBRACE_CURLY = 321,     /* "}"  */
    LEXTOK_TILDE = 322,            /* "~"  */
    LEXTOK_KWD_CALC = 323,         /* "calc"  */
    LEXTOK_KWD_END = 324,          /* "end"  */
    LEXTOK_KWD_IF = 325,           /* "if"  */
    LEXTOK_KWD_START = 326,        /* "start"  */
    LEXTOK_KWD_WHILE = 327,        /* "while"  */
    LEXTOK_IDENTIFIER = 328,       /* "<identifier>"  */
    LEXTOK_CHAR_LITERAL = 329,     /* "<charlit>"  */
    LEXTOK_BINFLOAT_LITERAL = 330, /* "<binfloattlit>"  */
    LEXTOK_OCTFLOAT_LITERAL = 331, /* "<octfloattlit>"  */
    LEXTOK_DECFLOAT_LITERAL = 332, /* "<decfloattlit>"  */
    LEXTOK_HEXFLOAT_LITERAL = 333, /* "<hexfloattlit>"  */
    LEXTOK_BININT_LITERAL = 334,   /* "<binintlit>"  */
    LEXTOK_OCTINT_LITERAL = 335,   /* "<octintlit>"  */
    LEXTOK_DECINT_LITERAL = 336,   /* "<decintlit>"  */
    LEXTOK_HEXINT_LITERAL = 337,   /* "<hexintlit>"  */
    LEXTOK_STR_LITERAL = 338,      /* "<strlit>"  */
    LEXTOK_INTERP_STR_LITERAL = 339, /* "<interpstrlit>"  */
    LEXTOK_EOF = 340,              /* "<eof>"  */
    LEXTOK_INVALID = 341           /* "<invalid>"  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 108 "src/parser.yacc"

    char chr;
    int64_t i64;
    double f64;
    char *str;
    void *any;
    char *idf;

#line 159 "include/tokens.yac.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_INCLUDE_TOKENS_YAC_H_INCLUDED  */
