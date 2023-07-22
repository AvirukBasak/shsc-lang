### Test Results 1

Tested on `tests/test.txt`.
`LEXTOK_NEWLINE: NULL` has NOT been cleared from the O/P.

```
LEXTOK_KWD_MODULE: module
LEXTOK_IDENTIFIER: main
LEXTOK_NEWLINE: NULL
LEXTOK_NEWLINE: NULL
LEXTOK_KWD_PROC: proc
LEXTOK_IDENTIFIER: main
LEXTOK_KWD_START: start
LEXTOK_NEWLINE: NULL
LEXTOK_IDENTIFIER: print
LEXTOK_LBRACE_PAREN: (
LEXTOK_STR_LITERAL: Hello world!
LEXTOK_COMMA: ,
LEXTOK_IDENTIFIER: lf
LEXTOK_RBRACE_PAREN: )
LEXTOK_NEWLINE: NULL
LEXTOK_NEWLINE: NULL
LEXTOK_KWD_VAR: var
LEXTOK_IDENTIFIER: x
LEXTOK_ASSIGN: =
LEXTOK_IDENTIFIER: input
LEXTOK_LBRACE_PAREN: (
LEXTOK_IDENTIFIER: int
LEXTOK_RBRACE_PAREN: )
LEXTOK_NEWLINE: NULL
LEXTOK_KWD_IF: if
LEXTOK_IDENTIFIER: x
LEXTOK_LOGICAL_EQUAL: ==
LEXTOK_DECINT_LITERAL: 1
LEXTOK_KWD_THEN: then
LEXTOK_NEWLINE: NULL
LEXTOK_IDENTIFIER: print
LEXTOK_LBRACE_PAREN: (
LEXTOK_STR_LITERAL: entered 1
LEXTOK_COMMA: ,
LEXTOK_IDENTIFIER: lf
LEXTOK_RBRACE_PAREN: )
LEXTOK_NEWLINE: NULL
LEXTOK_KWD_ELIF: elif
LEXTOK_IDENTIFIER: x
LEXTOK_LOGICAL_EQUAL: ==
LEXTOK_DECINT_LITERAL: 2
LEXTOK_KWD_THEN: then
LEXTOK_NEWLINE: NULL
LEXTOK_IDENTIFIER: print
LEXTOK_LBRACE_PAREN: (
LEXTOK_STR_LITERAL: entered 2
LEXTOK_COMMA: ,
LEXTOK_IDENTIFIER: lf
LEXTOK_RBRACE_PAREN: )
LEXTOK_NEWLINE: NULL
LEXTOK_KWD_ELSE: else
LEXTOK_NEWLINE: NULL
LEXTOK_IDENTIFIER: print
LEXTOK_LBRACE_PAREN: (
LEXTOK_INTERP_STR_LITERAL: entered {x}
LEXTOK_COMMA: ,
LEXTOK_IDENTIFIER: lf
LEXTOK_RBRACE_PAREN: )
LEXTOK_NEWLINE: NULL
LEXTOK_KWD_END: end
LEXTOK_NEWLINE: NULL
LEXTOK_NEWLINE: NULL
LEXTOK_KWD_WHILE: while
LEXTOK_IDENTIFIER: x
LEXTOK_LOGICAL_GREATER_EQUAL: >=
LEXTOK_DECINT_LITERAL: 0
LEXTOK_KWD_DO: do
LEXTOK_NEWLINE: NULL
LEXTOK_IDENTIFIER: print
LEXTOK_LBRACE_PAREN: (
LEXTOK_INTERP_STR_LITERAL: x = {x}
LEXTOK_RBRACE_PAREN: )
LEXTOK_NEWLINE: NULL
LEXTOK_IDENTIFIER: x
LEXTOK_ASSIGN: =
LEXTOK_IDENTIFIER: x
LEXTOK_MINUS: -
LEXTOK_DECINT_LITERAL: 1
LEXTOK_NEWLINE: NULL
LEXTOK_KWD_END: end
LEXTOK_NEWLINE: NULL
LEXTOK_NEWLINE: NULL
LEXTOK_IDENTIFIER: x
LEXTOK_ASSIGN: =
LEXTOK_IDENTIFIER: input
LEXTOK_LBRACE_PAREN: (
LEXTOK_STR_LITERAL: prompt: 
LEXTOK_COMMA: ,
LEXTOK_IDENTIFIER: str
LEXTOK_RBRACE_PAREN: )
LEXTOK_NEWLINE: NULL
LEXTOK_IDENTIFIER: print
LEXTOK_LBRACE_PAREN: (
LEXTOK_INTERP_STR_LITERAL: entered {x}
LEXTOK_COMMA: ,
LEXTOK_IDENTIFIER: lf
LEXTOK_RBRACE_PAREN: )
LEXTOK_NEWLINE: NULL
LEXTOK_NEWLINE: NULL
LEXTOK_KWD_VAR: var
LEXTOK_IDENTIFIER: x
LEXTOK_ASSIGN: =
LEXTOK_BOOL_LITERAL: true
LEXTOK_SEMICOLON: ;
LEXTOK_NEWLINE: NULL
LEXTOK_IDENTIFIER: print
LEXTOK_LBRACE_PAREN: (
LEXTOK_INTERP_STR_LITERAL: bool value = {x}
LEXTOK_COMMA: ,
LEXTOK_IDENTIFIER: lf
LEXTOK_RBRACE_PAREN: )
LEXTOK_NEWLINE: NULL
LEXTOK_KWD_VAR: var
LEXTOK_IDENTIFIER: y
LEXTOK_ASSIGN: =
LEXTOK_DECINT_LITERAL: 5
LEXTOK_KWD_IF: if
LEXTOK_IDENTIFIER: x
LEXTOK_LOGICAL_EQUAL: ==
LEXTOK_BOOL_LITERAL: false
LEXTOK_KWD_ELSE: else
LEXTOK_DECINT_LITERAL: 7
LEXTOK_NEWLINE: NULL
LEXTOK_KWD_IF: if
LEXTOK_IDENTIFIER: y
LEXTOK_LOGICAL_EQUAL: ==
LEXTOK_DECINT_LITERAL: 5
LEXTOK_KWD_THEN: then
LEXTOK_NEWLINE: NULL
LEXTOK_IDENTIFIER: print
LEXTOK_LBRACE_PAREN: (
LEXTOK_STR_LITERAL: x was false
LEXTOK_COMMA: ,
LEXTOK_IDENTIFIER: lf
LEXTOK_RBRACE_PAREN: )
LEXTOK_NEWLINE: NULL
LEXTOK_KWD_END: end
LEXTOK_NEWLINE: NULL
LEXTOK_KWD_END: end
LEXTOK_NEWLINE: NULL
LEXTOK_EOF
```

### Test Results 2
Tested on `tests/dump.txt`.
`LEXTOK_NEWLINE: NULL` has been cleared from the O/P.

```
LEXTOK_BANG: !
LEXTOK_LOGICAL_UNEQUAL: !=
LEXTOK_LOGICAL_UNIDENTICAL: !==
LEXTOK_STR_LITERAL: Hello world
LEXTOK_DOLLAR: $
LEXTOK_PERCENT: %
LEXTOK_MODULO_ASSIGN: %=
LEXTOK_AMPERSAND: &
LEXTOK_LOGICAL_AND: &&
LEXTOK_LOGICAL_AND_ASSIGN: &&=
LEXTOK_BITWISE_AND_ASSIGN: &=
LEXTOK_CHAR_LITERAL: xhar
LEXTOK_LBRACE_PAREN: (
LEXTOK_RBRACE_PAREN: )
LEXTOK_ASTERIX: *
LEXTOK_EXPONENT: **
LEXTOK_EXPONENT_ASSIGN: **=
LEXTOK_MULTIPLY_ASSIGN: *=
LEXTOK_PLUS: +
LEXTOK_INCREMENT: ++
LEXTOK_ADD_ASSIGN: +=
LEXTOK_COMMA: ,
LEXTOK_MINUS: -
LEXTOK_DECREMENT: --
LEXTOK_SUBSTRACT_ASSIGN: -=
LEXTOK_SARROW: ->
LEXTOK_DOT: .
LEXTOK_ELIPSIS: ...
LEXTOK_DOT: .
LEXTOK_DOT: .
LEXTOK_DOT: .
LEXTOK_FSLASH: /
LEXTOK_FLOOR_DIVIDE: //
LEXTOK_FLOOR_DIVIDE_ASSIGN: //=
LEXTOK_DIVIDE_ASSIGN: /=
LEXTOK_COLON: :
LEXTOK_DCOLON: ::
LEXTOK_SEMICOLON: ;
LEXTOK_LBRACE_ANGULAR: <
LEXTOK_BITWISE_LSHIFT: <<
LEXTOK_BITWISE_LSHIFT_ASSIGN: <<=
LEXTOK_LOGICAL_LESSER_EQUAL: <=
LEXTOK_ASSIGN: =
LEXTOK_LOGICAL_EQUAL: ==
LEXTOK_LOGICAL_IDENTICAL: ===
LEXTOK_DARROW: =>
LEXTOK_RBRACE_ANGULAR: >
LEXTOK_LOGICAL_GREATER_EQUAL: >=
LEXTOK_BITWISE_RSHIFT: >>
LEXTOK_BITWISE_RSHIFT_ASSIGN: >>=
LEXTOK_ARITH_RSHIFT: >>>
LEXTOK_ARITH_RSHIFT_ASSIGN: >>>=
LEXTOK_QUESTION: ?
LEXTOK_AT: @
LEXTOK_LBRACE_SQUARE: [
LEXTOK_BSLASH: \
LEXTOK_RBRACE_SQUARE: ]
LEXTOK_CARET: ^
LEXTOK_BITWISE_XOR_ASSIGN: ^=
LEXTOK_INTERP_STR_LITERAL: interp {data} string
LEXTOK_LBRACE_CURLY: {
LEXTOK_PIPE: |
LEXTOK_BITWISE_OR_ASSIGN: |=
LEXTOK_PIPEOUT: |>
LEXTOK_LOGICAL_OR: ||
LEXTOK_LOGICAL_OR_ASSIGN: ||=
LEXTOK_RBRACE_CURLY: }
LEXTOK_TILDE: ~
LEXTOK_IDENTIFIER: calc
LEXTOK_KWD_IF: if
LEXTOK_KWD_END: end
LEXTOK_KWD_START: start
LEXTOK_KWD_WHILE: while
LEXTOK_KWD_ELSE: else
LEXTOK_KWD_IF: if
LEXTOK_KWD_ELIF: elif
LEXTOK_KWD_MODULE: module
LEXTOK_KWD_FROM: from
LEXTOK_KWD_TO: to
LEXTOK_KWD_BY: by
LEXTOK_KWD_FOR: for
LEXTOK_KWD_BREAK: break
LEXTOK_KWD_CONTINUE: continue
LEXTOK_KWD_PASS: pass
LEXTOK_KWD_PROC: proc
LEXTOK_KWD_DO: do
LEXTOK_IDENTIFIER: a
LEXTOK_INCREMENT: ++
LEXTOK_INCREMENT: ++
LEXTOK_PLUS: +
LEXTOK_IDENTIFIER: b
LEXTOK_IDENTIFIER: a
LEXTOK_INCREMENT: ++
LEXTOK_PLUS: +
LEXTOK_INCREMENT: ++
LEXTOK_IDENTIFIER: b
LEXTOK_IDENTIFIER: a
LEXTOK_DECREMENT: --
LEXTOK_DECREMENT: --
LEXTOK_MINUS: -
LEXTOK_IDENTIFIER: b
LEXTOK_IDENTIFIER: a
LEXTOK_DECREMENT: --
LEXTOK_MINUS: -
LEXTOK_DECREMENT: --
LEXTOK_MINUS: -
LEXTOK_IDENTIFIER: b
LEXTOK_IDENTIFIER: a
LEXTOK_DECREMENT: --
LEXTOK_MINUS: -
LEXTOK_IDENTIFIER: b
LEXTOK_IDENTIFIER: a
LEXTOK_IDENTIFIER: b
LEXTOK_IDENTIFIER: alpha
LEXTOK_IDENTIFIER: hello
LEXTOK_IDENTIFIER: ox_11
LEXTOK_DECINT_LITERAL: 0
LEXTOK_DECFLOAT_LITERAL: 0.0
LEXTOK_DECINT_LITERAL: 00
LEXTOK_DECINT_LITERAL: 10
LEXTOK_DECINT_LITERAL: 13
LEXTOK_DECINT_LITERAL: 12000000000
LEXTOK_MINUS: -
LEXTOK_DECINT_LITERAL: 12000000
LEXTOK_DECFLOAT_LITERAL: 0.12000000
LEXTOK_DECFLOAT_LITERAL: 0.4e5
LEXTOK_DECFLOAT_LITERAL: 12.34e-6
LEXTOK_DECINT_LITERAL: 3e8
LEXTOK_DECFLOAT_LITERAL: 31.4e-1
LEXTOK_DECFLOAT_LITERAL: 6.023e23
LEXTOK_DECFLOAT_LITERAL: 6.626e-34
LEXTOK_MINUS: -
LEXTOK_DECFLOAT_LITERAL: 1.602e-19
LEXTOK_DECINT_LITERAL: 12
LEXTOK_IDENTIFIER: e
LEXTOK_DECINT_LITERAL: 0
LEXTOK_DOT: .
LEXTOK_DECFLOAT_LITERAL: 0.2e4
LEXTOK_DECFLOAT_LITERAL: 0.5
LEXTOK_DECINT_LITERAL: 2e4
LEXTOK_DECFLOAT_LITERAL: 0.5
LEXTOK_PLUS: +
LEXTOK_DECINT_LITERAL: 0
LEXTOK_DOT: .
LEXTOK_OCTINT_LITERAL: 23
LEXTOK_OCTINT_LITERAL: 0
LEXTOK_OCTINT_LITERAL: 00
LEXTOK_OCTFLOAT_LITERAL: 0.0
LEXTOK_OCTINT_LITERAL: 34e+7
LEXTOK_OCTINT_LITERAL: 2e07
LEXTOK_PLUS: +
LEXTOK_OCTFLOAT_LITERAL: 0.0
LEXTOK_MINUS: -
LEXTOK_OCTINT_LITERAL: 34e+7
LEXTOK_PLUS: +
LEXTOK_OCTINT_LITERAL: 12e-5
LEXTOK_MINUS: -
LEXTOK_OCTINT_LITERAL: 2e07
LEXTOK_PLUS: +
LEXTOK_OCTINT_LITERAL: 12
LEXTOK_IDENTIFIER: e
LEXTOK_MINUS: -
LEXTOK_DECINT_LITERAL: 9
LEXTOK_HEXINT_LITERAL: 0A5
LEXTOK_HEXINT_LITERAL: 0000FFFF
LEXTOK_HEXINT_LITERAL: 00EEBBe-0A
LEXTOK_PLUS: +
LEXTOK_HEXINT_LITERAL: 0A5
LEXTOK_MINUS: -
LEXTOK_HEXINT_LITERAL: 0000FFFF
LEXTOK_PLUS: +
LEXTOK_HEXINT_LITERAL: 00EEBBe-0A
LEXTOK_EOF
```