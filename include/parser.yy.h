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

#ifndef YY_YY_INCLUDE_PARSER_YY_H_INCLUDED
# define YY_YY_INCLUDE_PARSER_YY_H_INCLUDED
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
    TOKEN_EOF = 0,                 /* "<eof>"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN_BANG = 258,              /* "!"  */
    TOKEN_LOGICAL_UNEQUAL = 259,   /* "!="  */
    TOKEN_LOGICAL_UNIDENTICAL = 260, /* "!=="  */
    TOKEN_DQUOTE = 261,            /* TOKEN_DQUOTE  */
    TOKEN_DOLLAR = 262,            /* "$"  */
    TOKEN_PERCENT = 263,           /* "%"  */
    TOKEN_MODULO_ASSIGN = 264,     /* "%="  */
    TOKEN_AMPERSAND = 265,         /* "&"  */
    TOKEN_LOGICAL_AND = 266,       /* "&&"  */
    TOKEN_LOGICAL_AND_ASSIGN = 267, /* "&&="  */
    TOKEN_BITWISE_AND_ASSIGN = 268, /* "&="  */
    TOKEN_SQUOTE = 269,            /* "'"  */
    TOKEN_LBRACE_PAREN = 270,      /* "("  */
    TOKEN_RBRACE_PAREN = 271,      /* ")"  */
    TOKEN_ASTERIX = 272,           /* "*"  */
    TOKEN_EXPONENT = 273,          /* "**"  */
    TOKEN_EXPONENT_ASSIGN = 274,   /* "**="  */
    TOKEN_MULTIPLY_ASSIGN = 275,   /* "*="  */
    TOKEN_PLUS = 276,              /* "+"  */
    TOKEN_INCREMENT = 277,         /* "++"  */
    TOKEN_ADD_ASSIGN = 278,        /* "+="  */
    TOKEN_COMMA = 279,             /* ","  */
    TOKEN_MINUS = 280,             /* "-"  */
    TOKEN_DECREMENT = 281,         /* "--"  */
    TOKEN_SUBSTRACT_ASSIGN = 282,  /* "-="  */
    TOKEN_SARROW = 283,            /* "->"  */
    TOKEN_DOT = 284,               /* "."  */
    TOKEN_ELIPSIS = 285,           /* "..."  */
    TOKEN_FSLASH = 286,            /* "/"  */
    TOKEN_FLOOR_DIVIDE = 287,      /* "//"  */
    TOKEN_FLOOR_DIVIDE_ASSIGN = 288, /* "//="  */
    TOKEN_DIVIDE_ASSIGN = 289,     /* "/="  */
    TOKEN_COLON = 290,             /* ":"  */
    TOKEN_DCOLON = 291,            /* "::"  */
    TOKEN_SEMICOLON = 292,         /* ";"  */
    TOKEN_LBRACE_ANGULAR = 293,    /* "<"  */
    TOKEN_BITWISE_LSHIFT = 294,    /* "<<"  */
    TOKEN_BITWISE_LSHIFT_ASSIGN = 295, /* "<<="  */
    TOKEN_LOGICAL_LESSER_EQUAL = 296, /* "<="  */
    TOKEN_ASSIGN = 297,            /* "="  */
    TOKEN_LOGICAL_EQUAL = 298,     /* "=="  */
    TOKEN_LOGICAL_IDENTICAL = 299, /* "==="  */
    TOKEN_DARROW = 300,            /* "=>"  */
    TOKEN_RBRACE_ANGULAR = 301,    /* ">"  */
    TOKEN_LOGICAL_GREATER_EQUAL = 302, /* ">="  */
    TOKEN_BITWISE_RSHIFT = 303,    /* ">>"  */
    TOKEN_BITWISE_RSHIFT_ASSIGN = 304, /* ">>="  */
    TOKEN_ARITH_RSHIFT = 305,      /* ">>>"  */
    TOKEN_ARITH_RSHIFT_ASSIGN = 306, /* ">>>="  */
    TOKEN_QUESTION = 307,          /* "?"  */
    TOKEN_AT = 308,                /* "@"  */
    TOKEN_LBRACE_SQUARE = 309,     /* "["  */
    TOKEN_BSLASH = 310,            /* "\\"  */
    TOKEN_RBRACE_SQUARE = 311,     /* "]"  */
    TOKEN_CARET = 312,             /* "^"  */
    TOKEN_BITWISE_XOR_ASSIGN = 313, /* "^="  */
    TOKEN_BACKTICK = 314,          /* "`"  */
    TOKEN_LBRACE_CURLY = 315,      /* "{"  */
    TOKEN_PIPE = 316,              /* "|"  */
    TOKEN_BITWISE_OR_ASSIGN = 317, /* "|="  */
    TOKEN_PIPEOUT = 318,           /* "|>"  */
    TOKEN_LOGICAL_OR = 319,        /* "||"  */
    TOKEN_LOGICAL_OR_ASSIGN = 320, /* "||="  */
    TOKEN_RBRACE_CURLY = 321,      /* "}"  */
    TOKEN_TILDE = 322,             /* "~"  */
    TOKOP_NOP = 323,               /* TOKOP_NOP  */
    TOKOP_FNCALL = 324,            /* TOKOP_FNCALL  */
    TOKOP_INDEXING = 325,          /* TOKOP_INDEXING  */
    TOKOP_TERNARY_COND = 326,      /* TOKOP_TERNARY_COND  */
    TOKOP_FNARGS_INDEXING = 327,   /* TOKOP_FNARGS_INDEXING  */
    TOKEN_NEWLINE = 328,           /* "\n"  */
    TOKEN_KWD_MODULE = 329,        /* "module"  */
    TOKEN_KWD_PROC = 330,          /* "proc"  */
    TOKEN_KWD_START = 331,         /* "start"  */
    TOKEN_KWD_END = 332,           /* "end"  */
    TOKEN_KWD_BLOCK = 333,         /* "block"  */
    TOKEN_KWD_IF = 334,            /* "if"  */
    TOKEN_KWD_THEN = 335,          /* "then"  */
    TOKEN_KWD_ELIF = 336,          /* "elif"  */
    TOKEN_KWD_ELSE = 337,          /* "else"  */
    TOKEN_KWD_WHILE = 338,         /* "while"  */
    TOKEN_KWD_BREAK = 339,         /* "break"  */
    TOKEN_KWD_CONTINUE = 340,      /* "continue"  */
    TOKEN_KWD_FOR = 341,           /* "for"  */
    TOKEN_KWD_FROM = 342,          /* "from"  */
    TOKEN_KWD_TO = 343,            /* "to"  */
    TOKEN_KWD_BY = 344,            /* "by"  */
    TOKEN_KWD_IN = 345,            /* "in"  */
    TOKEN_KWD_DO = 346,            /* "do"  */
    TOKEN_KWD_VAR = 347,           /* "var"  */
    TOKEN_KWD_CONST = 348,         /* "const"  */
    TOKEN_KWD_PASS = 349,          /* "pass"  */
    TOKEN_KWD_RETURN = 350,        /* "return"  */
    TOKEN_INVALID = 351,           /* "<invalid>"  */
    TOKEN_BOOL_LITERAL = 352,      /* "<boollit>"  */
    TOKEN_CHAR_LITERAL = 353,      /* "<charlit>"  */
    TOKEN_BINFLOAT_LITERAL = 354,  /* "<binfloattlit>"  */
    TOKEN_OCTFLOAT_LITERAL = 355,  /* "<octfloattlit>"  */
    TOKEN_DECFLOAT_LITERAL = 356,  /* "<decfloattlit>"  */
    TOKEN_HEXFLOAT_LITERAL = 357,  /* "<hexfloattlit>"  */
    TOKEN_BININT_LITERAL = 358,    /* "<binintlit>"  */
    TOKEN_OCTINT_LITERAL = 359,    /* "<octintlit>"  */
    TOKEN_DECINT_LITERAL = 360,    /* "<decintlit>"  */
    TOKEN_HEXINT_LITERAL = 361,    /* "<hexintlit>"  */
    TOKEN_STR_LITERAL = 362,       /* "<strlit>"  */
    TOKEN_INTERP_STR_LITERAL = 363, /* "<interpstrlit>"  */
    TOKEN_IDENTIFIER = 364         /* "<identifier>"  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 21 "src/parser.y"

    /* line count */
    int line_count;

    /* just the token id */
    enum yytokentype tok;

    /* base literals */
    bool     literal_bool;
    char     literal_char;
    double   literal_f64;
    int64_t  literal_i64;
    char    *literal_str;
    void    *literal_any;

    /* identifier name */
    char    *identifier_name;

    /* ast nodes */
    ast_Statements_t       *astnode_statements;           /* statements */
    ast_Statement_t        *astnode_statement;            /* statement */
    ast_Assignment_t       *astnode_assignment;           /* assignment */
    ast_CompoundSt_t       *astnode_compound_statement;   /* compound_statement */
    ast_IfBlock_t          *astnode_if_block;             /* if_block */
    ast_ElseBlock_t        *astnode_else_block;           /* else_block */
    ast_WhileBlock_t       *astnode_while_block;          /* while_block */
    ast_ForBlock_t         *astnode_for_block;            /* for_block */
    ast_Block_t            *astnode_block;                /* block */
    ast_Expression_t       *astnode_expression;           /* expression */
    ast_CommaSepList_t     *astnode_comma_list;           /* comma_list */
    ast_AssociativeList_t  *astnode_assoc_list;           /* assoc_list */
    ast_Literal_t          *astnode_literal;              /* literal */
    ast_Identifier_t       *astnode_identifier;           /* identifier */

#line 208 "include/parser.yy.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_INCLUDE_PARSER_YY_H_INCLUDED  */
