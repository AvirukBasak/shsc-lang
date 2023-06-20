/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

#ifndef YY_YY_INCLUDE_PARSER_YAC_H_INCLUDED
# define YY_YY_INCLUDE_PARSER_YAC_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    LEXTOK_BANG = 258,
    LEXTOK_LOGICAL_UNEQUAL = 259,
    LEXTOK_LOGICAL_UNIDENTICAL = 260,
    LEXTOK_DQUOTE = 261,
    LEXTOK_DOLLAR = 262,
    LEXTOK_PERCENT = 263,
    LEXTOK_MODULO_ASSIGN = 264,
    LEXTOK_AMPERSAND = 265,
    LEXTOK_LOGICAL_AND = 266,
    LEXTOK_LOGICAL_AND_ASSIGN = 267,
    LEXTOK_BITWISE_AND_ASSIGN = 268,
    LEXTOK_SQUOTE = 269,
    LEXTOK_LBRACE_PAREN = 270,
    LEXTOK_RBRACE_PAREN = 271,
    LEXTOK_ASTERIX = 272,
    LEXTOK_EXPONENT = 273,
    LEXTOK_EXPONENT_ASSIGN = 274,
    LEXTOK_MULTIPLY_ASSIGN = 275,
    LEXTOK_PLUS = 276,
    LEXTOK_INCREMENT = 277,
    LEXTOK_ADD_ASSIGN = 278,
    LEXTOK_COMMA = 279,
    LEXTOK_MINUS = 280,
    LEXTOK_DECREMENT = 281,
    LEXTOK_SUBSTRACT_ASSIGN = 282,
    LEXTOK_SARROW = 283,
    LEXTOK_DOT = 284,
    LEXTOK_ELIPSIS = 285,
    LEXTOK_FSLASH = 286,
    LEXTOK_FLOOR_DIVIDE = 287,
    LEXTOK_FLOOR_DIVIDE_ASSIGN = 288,
    LEXTOK_DIVIDE_ASSIGN = 289,
    LEXTOK_COLON = 290,
    LEXTOK_DCOLON = 291,
    LEXTOK_SEMICOLON = 292,
    LEXTOK_LBRACE_ANGULAR = 293,
    LEXTOK_BITWISE_LSHIFT = 294,
    LEXTOK_BITWISE_LSHIFT_ASSIGN = 295,
    LEXTOK_LOGICAL_LESSER_EQUAL = 296,
    LEXTOK_ASSIGN = 297,
    LEXTOK_LOGICAL_EQUAL = 298,
    LEXTOK_LOGICAL_IDENTICAL = 299,
    LEXTOK_DARROW = 300,
    LEXTOK_RBRACE_ANGULAR = 301,
    LEXTOK_LOGICAL_GREATER_EQUAL = 302,
    LEXTOK_BITWISE_RSHIFT = 303,
    LEXTOK_BITWISE_RSHIFT_ASSIGN = 304,
    LEXTOK_ARITH_RSHIFT = 305,
    LEXTOK_ARITH_RSHIFT_ASSIGN = 306,
    LEXTOK_QUESTION = 307,
    LEXTOK_AT = 308,
    LEXTOK_LBRACE_SQUARE = 309,
    LEXTOK_BSLASH = 310,
    LEXTOK_RBRACE_SQUARE = 311,
    LEXTOK_CARET = 312,
    LEXTOK_BITWISE_XOR_ASSIGN = 313,
    LEXTOK_BACKTICK = 314,
    LEXTOK_LBRACE_CURLY = 315,
    LEXTOK_PIPE = 316,
    LEXTOK_BITWISE_OR_ASSIGN = 317,
    LEXTOK_PIPEOUT = 318,
    LEXTOK_LOGICAL_OR = 319,
    LEXTOK_LOGICAL_OR_ASSIGN = 320,
    LEXTOK_RBRACE_CURLY = 321,
    LEXTOK_TILDE = 322,
    LEXTOK_NEWLINE = 323,
    LEXTOK_KWD_PROC = 324,
    LEXTOK_KWD_START = 325,
    LEXTOK_KWD_END = 326,
    LEXTOK_KWD_BLOCK = 327,
    LEXTOK_KWD_IF = 328,
    LEXTOK_KWD_THEN = 329,
    LEXTOK_KWD_ELIF = 330,
    LEXTOK_KWD_ELSE = 331,
    LEXTOK_KWD_WHILE = 332,
    LEXTOK_KWD_FOR = 333,
    LEXTOK_KWD_FROM = 334,
    LEXTOK_KWD_TO = 335,
    LEXTOK_KWD_DO = 336,
    LEXTOK_KWD_VAR = 337,
    LEXTOK_KWD_PASS = 338,
    LEXTOK_IDENTIFIER = 339,
    LEXTOK_BOOL_LITERAL = 340,
    LEXTOK_CHAR_LITERAL = 341,
    LEXTOK_BINFLOAT_LITERAL = 342,
    LEXTOK_OCTFLOAT_LITERAL = 343,
    LEXTOK_DECFLOAT_LITERAL = 344,
    LEXTOK_HEXFLOAT_LITERAL = 345,
    LEXTOK_BININT_LITERAL = 346,
    LEXTOK_OCTINT_LITERAL = 347,
    LEXTOK_DECINT_LITERAL = 348,
    LEXTOK_HEXINT_LITERAL = 349,
    LEXTOK_STR_LITERAL = 350,
    LEXTOK_INTERP_STR_LITERAL = 351,
    LEXTOK_EOF = 352,
    LEXTOK_INVALID = 353
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

typedef union {
    bool bul;
    char chr;
    int64_t i64;
    double f64;
    char *str;
    void *any;
    char *idf;
} DataType;

typedef enum {
    VT_BUL,
    VT_CHR,
    VT_I64,
    VT_F64,
    VT_STR,
    VT_ANY,
} VarType;

typedef struct {
    DataType var;
    VarType type;
} VarData;

union YYSTYPE
{
#line 127 "src/parser.yy" /* yacc.c:1909  */

    bool bul;
    char chr;
    int64_t i64;
    double f64;
    char *str;
    void *any;
    char *idf;
    VarData var_data;

#line 164 "include/parser.yac.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_INCLUDE_PARSER_YAC_H_INCLUDED  */
